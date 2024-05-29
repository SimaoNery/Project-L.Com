#include <PubSubClient.h>
#include <WiFi.h>
#include "esp_headers.h"
#include <Arduino.h>
#include <esp_camera.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(PIN_LIGHT_1, OUTPUT);
  pinMode(PIN_LIGHT_2, OUTPUT);
  pinMode(PIN_LIGHT_3, OUTPUT);
  pinMode(PIN_LIGHT_4, OUTPUT);
  pinMode(PIN_LIGHT_5, OUTPUT);
  pinMode(PIN_BUZZER_1, OUTPUT);
  pinMode(PIN_BUZZER_2, OUTPUT);
  pinMode(PIN_Motor, OUTPUT);
  pinMode(PIN_DECIBEL, INPUT);
  pinMode(PIN_HUMIDITY_AND_TEMPERATURE, INPUT);

  Serial.begin(115200);

  // Configure Wifi
  setup_wifi();

  // Configure Mosquitto
  connect_mqtt();
}

typedef struct {
  char *topic;
  void (*redirect_message)(byte *payload, unsigned int length);
} on_message_t;

static const on_message_t on_message[] = {
  { LIGHT_TOPIC, turn_light },
  { BUZZER_TOPIC, turn_buzzer },
  { LCD_DISPLAY_TEXT_TOPIC, lcd_display_text },
  { LCD_DISPLAY_ANIMATION_TOPIC, lcd_display_animation },
  { MOTOR_TOPIC, turn_motor },
  { HUMIDITY_SENSOR_TOPIC, turn_humidity_sensor },
  { DECIBEL_SENSOR_TOPIC, turn_decibel_sensor },
  { PICTURE_TOPIC, take_picture },
  { STREAM_TOPIC, stream_video}
};

String mosquittoMessage(byte *bytes, unsigned int length) {
  String binary = "";
  for (unsigned int i = 0; i < length; i++) {
    for (int j = 7; j >= 0; j--) {
      binary += ((bytes[i] >> j) & 1) ? '1' : '0';
    }
  }
  return binary;
}



void lcd_display_text(byte *payload, unsigned int length) {}
void lcd_display_animation(byte *payload, unsigned int length) {}

void take_picture(byte *payload, unsigned int length) {
  camera_fb_t *fb = esp_camera_fb_get();
  if (fb) {
    // Send the picture over MQTT
    client.publish(PICTURE_TOPIC, fb->buf, fb->len);
    esp_camera_fb_return(fb);
  }
}

void stream_video(byte *payload, unsigned int length){

}

void turn_decibel_sensor(byte *payload, unsigned int length) {
  //Arduino Uno
}

void turn_humidity_sensor(byte *payload, unsigned int length) {
  //Arduino Uno

  /*
  if (isnan(humidity) || isnan(temperature)) {
    client.publish(HUMIDITY_SENSOR_TOPIC, "Failed to read humidity or temperature!");
    return;
  } else {
    char message[50];
    snprintf(message, sizeof(message), "Temperature = %.2f, Humidity = %.2f", temperature, humidity);
    client.publish(HUMIDITY_SENSOR_TOPIC, message);
  }
  */
}

void turn_motor(byte *payload, unsigned int length) {
  // Arduino UNO

  /*
  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryPayload.toInt();

  if ((binaryValue & 0x01) == 1) {
    digitalWrite(PIN_LIGHT_1, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_1, LOW);
  }

  if (((binaryValue & 0x10) >> 4) == 1) {
    digitalWrite(PIN_LIGHT_5, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_5, LOW);
  }
  */
}


void turn_buzzer(byte *payload, unsigned int length) {
  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryPayload.toInt();

  if ((binaryValue & 0x01) == 1) {
    digitalWrite(PIN_Motor, HIGH);
  } else {
    digitalWrite(PIN_Motor, LOW);
  }
}


void turn_light(byte *payload, unsigned int length) {

  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryPayload.toInt();

  if ((binaryValue & 0x01) == 1) {
    digitalWrite(PIN_LIGHT_1, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_1, LOW);
  }
  if (((binaryValue & 0x02) >> 1) == 1) {
    digitalWrite(PIN_LIGHT_2, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_2, LOW);
  }
  if (((binaryValue & 0x04) >> 2) == 1) {
    digitalWrite(PIN_LIGHT_3, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_3, LOW);
  }
  if (((binaryValue & 0x08) >> 3) == 1) {
    digitalWrite(PIN_LIGHT_4, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_4, LOW);
  }
  if (((binaryValue & 0x10) >> 4) == 1) {
    digitalWrite(PIN_LIGHT_5, HIGH);
  } else {
    digitalWrite(PIN_LIGHT_5, LOW);
  }
}

void connect_mqtt() {
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);

  while (!client.connected()) {
    // Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {  // Connect without username and password
      // Serial.println("Connected to MQTT");
    } else {
      // Serial.print("Failed to connect to MQTT, rc=");
      // Serial.println(client.state());
      delay(2000);
    }
  }

  for (size_t i = 0; i < sizeof(on_message) / sizeof(on_message[0]); i++) {
    client.subscribe(on_message[i].topic);
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");

  size_t num_topics = sizeof(on_message) / sizeof(on_message[0]);

  for (size_t i = 0; i < num_topics; i++) {
    if (strcmp(topic, on_message[i].topic) == 0) {
      on_message[i].redirect_message(payload, length);
    }
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (!client.connected()) {
    connect_mqtt();
  }

  client.loop();
}