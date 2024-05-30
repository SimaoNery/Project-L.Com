#include "mosquitto.h"

struct mosquitto *mosq = NULL;
int sockfd = *((int *) arg);

static const redirect_t redirect[] = {
    {LIGHT_MASK, LIGHT_TOPIC},
    {BUZZER_MASK, BUZZER_TOPIC}, 
    {LCD_DISPLAY_TEXT_MASK, LCD_DISPLAY_TEXT_TOPIC},
    {LCD_DISPLAY_ANIMATION_MASK, LCD_DISPLAY_ANIMATION_TOPIC},
    {MOTOR_MASK, MOTOR_TOPIC},
    {HUMIDITY_SENSOR_MASK, HUMIDITY_SENSOR_TOPIC},
    {DECIBEL_SENSOR_MASK, DECIBEL_SENSOR_TOPIC},
    {CAMERA_MASK, CAMERA_TOPIC}
};

void mosquitto_humidity_received(const struct mosquitto_message* msg) {
  uint8_t humidity[4];
  humidity[0] = msg->payload [0:7];
  humidity[1] = msg->payload [8:15];
  humidity[2] = msg->payload[16:23];
  humidity[3] = msg->payload[24:31];

  for (int i = 0; i < 4; i++) {
    int attempts = 5;
    while ((attempts--) && serial_port_send_message(sockfd, humidity[i]));
  }
}

void mosquitto_decibel_received(const struct mosquitto_message* msg){
  uint8_t decibel[2];
  decibel[0] = msg->payload [0:7];
  decibel[1] = msg->payload [8:15];

  for (int i = 0; i < 2; i++) {
    int attempts = 5;
    while ((attempts--) && serial_port_send_message(sockfd, decibel[i]));
  }
}


void mosquitto_camera_photo_received(const struct mosquitto_message* msg) {
  int j = 0;
  for (int i = 0; i < 153600; i++, j += 8) {
    char buffer[8];
    memcpy(buffer, &msg->payload[j], 8);
    serial_port_send_message(sockfd, buffer);
  }
}


static const MessageHandler_t messageHandler[] = {
    {HUMIDITY_TOPIC_RX, humidity_received},
    {DECIBEL_TOPIC_RX, decibel_received},
    {CAMERA_PHOTO_TOPIC_RX, camera_photo_received},
};

void mosquitto_commmand_byte_received(uint8_t command) {
    uint8_t device = (command >> 5);
    uint8_t param = command & 0x1F;

    size_t num_topics = sizeof(redirect) / sizeof(redirect[0]);

    mosquitto_publish(mosq, NULL, redirect[device].topic, 1, &param, 1, false);
}

void mosquitto_on_message_received(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    const char *topic = (const char *)message->topic;
    size_t num_topics = sizeof(messageHandler) / sizeof(messageHandler[0]);

    for (size_t i = 0; i < num_topics; i++)
    {
        if (strcmp(topic, messageHandler[i].topic) == 0)
        {
            messageHandler[i].handler(message);
        }
    }
}

void mosquitto_initial_connection(struct mosquitto *mosq, void *userdata, int rc)
{
    if (rc == 0)
    {
        const char* topics[] = {
            HUMIDITY_TOPIC_RX,
            DECIBEL_TOPIC_RX,
            CAMERA_PHOTO_TOPIC_RX
        };

        if (mosquitto_subscribe_multiple(mosq, NULL, sizeof(topics) / sizeof(char*), topics, 1, 0, NULL) != MOSQ_ERR_SUCCESS){
            printf("Error subscribing topics\n");
        } 
    }
    
    else {
        fprintf(stderr, "Failed to connect to MQTT broker: %s\n", mosquitto_connack_string(rc));
    }
}


int mosquitto_initial_config()
{
    
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    
    if (!mosq)
    {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, mosquitto_initial_connection);
    mosquitto_message_callback_set(mosq, mosquitto_on_message_received);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        return 1;
    }

    mosquitto_loop_start(mosq);
    return 0;
}


void mosquitto_destroy()
{
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}


int serial_port_send_message(int socketfd, const void *message) {
  if (send(socketfd, message, strlen(message), 0) != strlen(message)) {
    perror("Send failed");
    return 1;
  }

  return 0;
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

    uint8_t nak = NAK_MESSAGE;
    if (write(sockfd, &nak, sizeof(nak)) == -1) {
        perror("Failed to send NAK message");
    }
  }

  close(sockfd);
  return NULL;
}

int main() {
    /* Initial connection of the socket */
    int sockfd;
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

    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    /* Initial connection of the mosquitto server*/
    printf("Connecting to mosquitto broker.");
    int mosquitto_conf = mosquitto_initial_config();
    while ((attempts-- > 0) && (mosquitto_conf != 0)) {
        mosquitto_conf = mosquitto_initial_config();
        printf("..");
        sleep(1000);
    }

    if (mosquitto_conf) {
        printf("Unable to connect to mosquitto broker\n");
        return 1;
    }

    pthread_t socket_thread;
    if (pthread_create(&socket_thread, NULL, read_from_socket, &sockfd) != 0) {
      perror("Failed to create socket read thread");
      return 1;
    }

    pthread_join(socket_thread, NULL);


    close(sockfd);
    mosquitto_destroy();

    return 0;
}