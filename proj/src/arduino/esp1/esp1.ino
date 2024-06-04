#include "esp_headers.h"
#include "mosquitto_headers.hpp"
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_camera.h>
#include "soc/soc.h"  // Disable brownout problems
#include "soc/rtc_cntl_reg.h"

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
  pinMode(PIN_MOTOR, OUTPUT);

  Serial.begin(115200);

  // Configure Wifi
  setup_wifi();

  //dht.begin();
  //Serial.println("DHT sensor initialized.");

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
  { MOTOR_TOPIC, motor },
  { HUMIDITY_SENSOR_TOPIC, turn_humidity_sensor },
  { DECIBEL_SENSOR_TOPIC, turn_decibel_sensor},
};

int pow(int exp) {
  if (exp == 0) return 1;

  int res = 1;

  for (int i = 0; i < exp; i++) {
    res *= 2;
  }

  return res;
}

int binaryToInt(const String bin) {
  int res = 0;
  int length = bin.length();

  for (int i = 0; i < length; i++) {
    int bit = bin[length - 1 - i] - '0';
    res += bit * pow(i);
  }

  return res;
}

String mosquittoMessage(byte *bytes, unsigned int length) {
  String binary = "";
  for (unsigned int i = 0; i < length; i++) {
    binary += String(bytes[i], BIN);
  }
  return binary;
}

void motor(byte *payload, unsigned int length) {
  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryToInt(binaryPayload);

  if (binaryValue & 0x01) {
    digitalWrite(PIN_MOTOR, HIGH);
    Serial.println("Motor turned on");
  } else {
    digitalWrite(PIN_MOTOR, LOW);
    Serial.println("Motor turned off");
  }


  //String binaryPayload = mosquittoMessage(payload, length);
  //unsigned int binaryValue = binaryToInt(binaryPayload) & 0x1F;
  //Serial.print(binaryValue);
  //Serial.print("Motor Spinning!!");
}

void turn_decibel_sensor(byte *payload, unsigned int length) {
  float db = 10.50;

  if (isnan(db)) {
    client.publish(DECIBEL_TOPIC_RX, "failed");
    return;
  }
  char message[32];
  snprintf(message, sizeof(message), "%.2f", db);

  client.publish(DECIBEL_TOPIC_RX, message);
  Serial.println("Decibel sent!");
}

void turn_humidity_sensor(byte *payload, unsigned int length) {

  // Assuming these functions return float values
  // float humidity = dht.readHumidity();
  // float temperature = dht.readTemperature();

  float humidity = 40.0; // example humidity value
  float temperature = 28.30; // example temperature value

  if (isnan(humidity) || isnan(temperature)) {
    client.publish(HUMIDITY_TOPIC_RX, "failed");
    return;
  }

  char message[32];
  snprintf(message, sizeof(message), "%.2f %.2f", temperature, humidity);

  client.publish(HUMIDITY_TOPIC_RX, message);
  Serial.println("Humidity and Temperature sent!");
}


void take_picture(byte *payload, unsigned int length) {
  Serial.println("Sending photo!");
  byte mockPhoto[] = { 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x01, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00,
                       0xFF, 0xDB, 0x00, 0x43, 0x00, 0x08, 0x06, 0x06, 0x07, 0x06, 0x05, 0x08, 0x07, 0x07, 0x07, 0x09, 0x09, 0x08, 0x0A, 0x0C,
                       0x14, 0x0D, 0x0C, 0x0B, 0x0B, 0x0C, 0x19, 0x12, 0x13, 0x0F, 0x14, 0x1D, 0x1A, 0x1F, 0x1E, 0x1D, 0x1A, 0x1C, 0x1C, 0x20,
                       0x24, 0x2E, 0x27, 0x20, 0x22, 0x2C, 0x23, 0x1C, 0x1C, 0x28, 0x37, 0x29, 0x2C, 0x30, 0x31, 0x34, 0x34, 0x34, 0x1F, 0x27,
                       0x39, 0x3D, 0x38, 0x32, 0x3C, 0x2E, 0x33, 0x34, 0x32 };

  client.publish(PICTURE_TOPIC, mockPhoto, sizeof(mockPhoto));

  Serial.println("Photo sent!");
}


void turn_buzzer(byte *payload, unsigned int length) {
  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryToInt(binaryPayload) & 0x03;

  switch (binaryValue) {
    case 0x03:
      {
        digitalWrite(PIN_BUZZER_1, HIGH);
        tone(PIN_BUZZER_2, 1000);
        Serial.println("Buzzer 1 and 2 turned on");
        break;
      }
    case 0x02:
      {
        tone(PIN_BUZZER_2, 1000);
        Serial.println("Buzzer 2 turned on");
        digitalWrite(PIN_BUZZER_1, LOW);
        break;
      }
    case 0x01:
      {
        digitalWrite(PIN_BUZZER_1, HIGH);
        noTone(PIN_BUZZER_2);
        Serial.println("Buzzer 1 turned on");
        break;
      }
    default:
      {
        digitalWrite(PIN_BUZZER_1, LOW);
        noTone(PIN_BUZZER_2);
        break;
      }
  }
}

void turn_light(byte *payload, unsigned int length) {

  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryToInt(binaryPayload);
  Serial.print(binaryValue);

  if (binaryValue & 0x01) {
    digitalWrite(PIN_LIGHT_1, HIGH);
    Serial.println("Light 1 turned on");
  } else {
    digitalWrite(PIN_LIGHT_1, LOW);
    Serial.println("Light 1 turned off");
  }
  if (binaryValue & 0x02) {
    digitalWrite(PIN_LIGHT_2, HIGH);
    Serial.println("Light 2 turned on");
  } else {
    digitalWrite(PIN_LIGHT_2, LOW);
    Serial.println("Light 2 turned off");
  }
  if (binaryValue & 0x04) {
    digitalWrite(PIN_LIGHT_3, HIGH);
    Serial.println("Light 3 turned on");
  } else {
    digitalWrite(PIN_LIGHT_3, LOW);
    Serial.println("Light 3 turned off");
  }
  if (binaryValue & 0x08) {
    digitalWrite(PIN_LIGHT_4, HIGH);
    Serial.println("Light 4 turned on");
  } else {
    digitalWrite(PIN_LIGHT_4, LOW);
    Serial.println("Light 4 turned off");
  }
  if (binaryValue & 0x10) {
    digitalWrite(PIN_LIGHT_5, HIGH);
    Serial.println("Light 5 turned on");
  } else {
    digitalWrite(PIN_LIGHT_5, LOW);
    Serial.println("Light 5 turned off");
  }
}

void connect_mqtt() {
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client"))
      Serial.println("Connected to MQTT");
  }

  for (size_t i = 0; i < sizeof(on_message) / sizeof(on_message[0]); i++) {
    client.subscribe(on_message[i].topic);
  }
  Serial.println("all topics subscribed");
}



void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
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