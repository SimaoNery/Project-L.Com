/* _HEADERS_H_
    This file defines the common headers to be used in the project, such as:
        - MQTT Topics
        - Macros to be sent and their meaning
 */

#define MQTT_HOST "192.168.1.102"
#define MQTT_PORT 8443


/* ___MOSQUITTO_TOPICS___ */

#define LIGHT_TOPIC "light_topic"
#define BUZZER_TOPIC "buzzer_topic"
#define LCD_DISPLAY_TEXT_TOPIC "lcd_display_test_topic"
#define LCD_DISPLAY_ANIMATION_TOPIC "lcd_display_animation_topic"
#define MOTOR_TOPIC "motor_topic"
#define HUMIDITY_SENSOR_TOPIC "humidity_sensor_topic"
#define DECIBEL_SENSOR_TOPIC "decibel_sensor_topic"
#define CAMERA_TOPIC "camera_topic"


#define HUMIDITY_TOPIC_RX "humidity_topic_rx"
#define DECIBEL_TOPIC_RX "decibel_topic_rx"
#define CAMERA_PHOTO_TOPIC_RX "camera_photo_topic_rx"

/* ___LIGHT_TOPIC_MESSAGES___ */

