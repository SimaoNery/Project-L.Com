#include "mosquitto.h"

struct mosquitto *mosq = NULL;
int sockfd;
static const redirect_t redirect[] = {
  {LIGHT_MASK, LIGHT_TOPIC},
  {BUZZER_MASK, BUZZER_TOPIC},
  {LCD_DISPLAY_TEXT_MASK, LCD_DISPLAY_TEXT_TOPIC},
  {LCD_DISPLAY_ANIMATION_MASK, LCD_DISPLAY_ANIMATION_TOPIC},
  {MOTOR_MASK, MOTOR_TOPIC},
  {HUMIDITY_SENSOR_MASK, HUMIDITY_SENSOR_TOPIC},
  {DECIBEL_SENSOR_MASK, DECIBEL_SENSOR_TOPIC},
  {CAMERA_MASK, CAMERA_TOPIC}};

int serial_port_send_message(int socketfd, const void *message) {
  if (send(socketfd, message, 1, 0) != 1) {
    perror("Send failed");
    return 1;
  }

  return 0;
}

void mosquitto_humidity_received(const struct mosquitto_message *msg) {
  uint8_t humidity[4];
  memcpy(humidity, msg->payload, sizeof(humidity));

  for (int i = 0; i < 4; i++) {
    int attempts = 5;
    while ((attempts--) && serial_port_send_message(sockfd, &humidity[i]));
  }
}

void mosquitto_decibel_received(const struct mosquitto_message *msg) {
  uint8_t decibel[2];
  memcpy(decibel, msg->payload, sizeof(decibel));

  for (int i = 0; i < 2; i++) {
    int attempts = 5;
    while ((attempts--) && serial_port_send_message(sockfd, &decibel[i]));
  }
}

void mosquitto_camera_photo_received(const struct mosquitto_message *msg) {
  for (int i = 0; i < 153600; i += 8) {
    char buffer[8];
    memcpy(buffer, (char *) msg->payload + i, 8);
    serial_port_send_message(sockfd, buffer);
  }
}


static const MessageHandler_t messageHandler[] = {
  {HUMIDITY_TOPIC_RX, mosquitto_humidity_received},
  {DECIBEL_TOPIC_RX, mosquitto_decibel_received},
  {CAMERA_PHOTO_TOPIC_RX, mosquitto_camera_photo_received},
};

void mosquitto_commmand_byte_received(uint8_t command) {
  uint8_t device = (command >> 5);
  uint8_t param = command & 0x1F;

  mosquitto_publish(mosq, NULL, redirect[device].topic, 1, &param, 1, false);
}

void mosquitto_on_message_received(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
  const char *topic = (const char *) message->topic;
  size_t num_topics = sizeof(messageHandler) / sizeof(messageHandler[0]);

  for (size_t i = 0; i < num_topics; i++) {
    if (strcmp(topic, messageHandler[i].topic) == 0) {
      messageHandler[i].handler(message);
    }
  }
}

void mosquitto_initial_connection(struct mosquitto *mosq, void *userdata, int rc) {
  if (rc == 0) {
    const char *topics[] = {
      HUMIDITY_TOPIC_RX,
      DECIBEL_TOPIC_RX,
      CAMERA_PHOTO_TOPIC_RX};

    if (mosquitto_subscribe_multiple(mosq, NULL, sizeof(topics) / sizeof(topics[0]), (char *const *const) topics, 1, 0, NULL) != MOSQ_ERR_SUCCESS) {
      printf("Error subscribing to topics\n");
    }
  }
  else {
    fprintf(stderr, "Failed to connect to MQTT broker: %s\n", mosquitto_connack_string(rc));
  }
}

int mosquitto_initial_config() {
  mosquitto_lib_init();
  mosq = mosquitto_new(NULL, true, NULL);

  if (!mosq) {
    fprintf(stderr, "Error: Out of memory.\n");
    return 1;
  }

  mosquitto_connect_callback_set(mosq, mosquitto_initial_connection);
  mosquitto_message_callback_set(mosq, mosquitto_on_message_received);

  if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS) {
    fprintf(stderr, "Unable to connect to MQTT broker.\n");
    return 1;
  }

  mosquitto_loop_start(mosq);
  return 0;
}

void mosquitto_clean() {
  mosquitto_disconnect(mosq);
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
}

void *read_from_socket(void *arg) {
  uint8_t buffer[1];
  ssize_t bytes_read;

  while ((bytes_read = read(sockfd, buffer, sizeof(buffer))) > 0) {
    if (bytes_read == 1) {
      uint8_t received_byte = buffer[0];
      printf("Received byte: 0x%02x\n", received_byte);

      mosquitto_commmand_byte_received(received_byte);
    }
  }

  if (bytes_read == -1) {
    perror("Read from socket failed");
  }

  close(sockfd);
  return NULL;
}

int main() {
  /* Initial connection of the socket */
  struct sockaddr_in server_addr;
  int attempts = 10;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket creation failed");
    return 1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address/ Address not supported");
    return 1;
  }

  printf("Connecting socket");
  fflush(stdout);
  int socket_connect = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  while ((attempts-- > 0) && (socket_connect < 0)) {
    sleep(1);
    socket_connect = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    printf(".");
    fflush(stdout);
  }
  printf("\n");

  if (socket_connect < 0) {
    printf("Unable to connect to socket\n");
    return 1;
  }

  attempts = 10;

  /* Initial connection of the mosquitto server */
  printf("Connecting to mosquitto broker.");
  fflush(stdout);
  int mosquitto_conf = mosquitto_initial_config();
  while ((attempts-- > 0) && (mosquitto_conf != 0)) {
    sleep(1);
    mosquitto_conf = mosquitto_initial_config();
    printf(".");
    fflush(stdout);
  }

  if (mosquitto_conf) {
    printf("Unable to connect to mosquitto broker\n");
    return 1;
  }

  pthread_t socket_thread;
  if (pthread_create(&socket_thread, NULL, read_from_socket, NULL) != 0) {
    perror("Failed to create socket read thread");
    return 1;
  }

  pthread_join(socket_thread, NULL);

  close(sockfd);
  mosquitto_clean();

  return 0;
}
