#include "esp_headers.h"
#include "mosquitto_headers.hpp"
#include <Arduino.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <esp_camera.h>

WiFiClient espClient;
PubSubClient client(espClient);

//DHT dht(DHTPin, DHTTYPE);

void setup() {
  pinMode(PIN_LIGHT_1, OUTPUT);
  pinMode(PIN_LIGHT_2, OUTPUT);
  pinMode(PIN_LIGHT_3, OUTPUT);
  pinMode(PIN_LIGHT_4, OUTPUT);
  pinMode(PIN_LIGHT_5, OUTPUT);
  pinMode(PIN_BUZZER_1, OUTPUT);
  pinMode(PIN_BUZZER_2, OUTPUT);

  Serial.begin(115200);

  // Configure Wifi
  setup_wifi();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // Camera Init
  /*
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }*/

  // Configure Mosquitto
  connect_mqtt();
  //dht.begin();
}

typedef struct {
  char *topic;
  void (*redirect_message)(byte *payload, unsigned int length);
} on_message_t;

static const on_message_t on_message[] = {
  {LIGHT_TOPIC, turn_light},
  {BUZZER_TOPIC, turn_buzzer},
  {MOTOR_TOPIC, turn_motor},
  {HUMIDITY_SENSOR_TOPIC, turn_humidity_sensor},
  {DECIBEL_SENSOR_TOPIC, turn_decibel_sensor},
  {PICTURE_TOPIC, take_picture}};

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

void take_picture(byte *payload, unsigned int length) {
  Serial.println("Photo requested");
  /*
  camera_fb_t *fb = esp_camera_fb_get();
  if (fb) {
    // Send the picture over MQTT
    client.publish(PICTURE_TOPIC, fb->buf, fb->len);
    esp_camera_fb_return(fb);
  }*/
}

void turn_decibel_sensor(byte *payload, unsigned int length) {
  //Serial.println("Decibel requested");
  /*
  uint8_t msg = 0x00;
  Serial.write(msg);

  int attempts = 10;

  while(attempts--) {
    if (Serial.available() > 0) {
      String requestString = Serial.readStringUntil('\n');
      if (requestString.length() >= 2) {
        client.publish(DECIBEL_TOPIC_RX, requestString);
        return;
      } 
    }
    delay(100);
  }*/
}

void turn_humidity_sensor(byte *payload, unsigned int length) {
  /*
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    client.publish(HUMIDITY_TOPIC_RX, "failed");
    return;
  }
  char message[9];
  snprintf(message, sizeof(message), "%d_%d", temperature, humidity);
  client.publish(HUMIDITY_TOPIC_RX, message);*/
}


void turn_motor(byte *payload, unsigned int length) {
  /*
  //Serial.println("Motor turned on");
  uint8_t speed = payload & 0x1F;
  uint8_t msg = 0x10 | speed;
  Serial.println(msg);*/
}

void turn_buzzer(byte *payload, unsigned int length) {
  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryToInt(binaryPayload) & 0x03;

  switch (binaryValue) {
    case 0x03: {
      digitalWrite(PIN_BUZZER_1, HIGH);
      tone(PIN_BUZZER_2, 1000);
      Serial.println("Buzzer 1 and 2 turned on");
      delay(1000);
      break;
    }
    case 0x02: {
      tone(PIN_BUZZER_2, 1000);
      Serial.println("Buzzer 2 turned on");
      delay(1000);
      break;
    }
    case 0x01: {
      digitalWrite(PIN_BUZZER_1, HIGH);
      Serial.println("Buzzer 1 turned on");
      delay(1000);
      break;
    }
    default: {
      digitalWrite(PIN_BUZZER_1, LOW);
      noTone(PIN_BUZZER_2);
      break;
    }
  }

  digitalWrite(PIN_BUZZER_1, LOW);
  noTone(PIN_BUZZER_2);
}

void turn_light(byte *payload, unsigned int length) {

  String binaryPayload = mosquittoMessage(payload, length);
  unsigned int binaryValue = binaryToInt(binaryPayload);
  Serial.print(binaryValue);

  if (binaryValue & 0x01) {
    digitalWrite(PIN_LIGHT_1, HIGH);
    Serial.println("Light 1 turned on");
  }
  else {
    digitalWrite(PIN_LIGHT_1, LOW);
    Serial.println("Light 1 turned off");
  }
  if (binaryValue & 0x02) {
    digitalWrite(PIN_LIGHT_2, HIGH);
    Serial.println("Light 2 turned on");
  }
  else {
    digitalWrite(PIN_LIGHT_2, LOW);
    Serial.println("Light 2 turned off");
  }
  if (binaryValue & 0x04) {
    digitalWrite(PIN_LIGHT_3, HIGH);
    Serial.println("Light 3 turned on");
  }
  else {
    digitalWrite(PIN_LIGHT_3, LOW);
    Serial.println("Light 3 turned off");
  }
  if (binaryValue & 0x08) {
    digitalWrite(PIN_LIGHT_4, HIGH);
    Serial.println("Light 4 turned on");
  }
  else {
    digitalWrite(PIN_LIGHT_4, LOW);
    Serial.println("Light 4 turned off");
  }
  if (binaryValue & 0x10) {
    digitalWrite(PIN_LIGHT_5, HIGH);
    Serial.println("Light 5 turned on");
  }
  else {
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