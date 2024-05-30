#define BIT(n) (1 << (n))


/* ___MESSAGES_TO_BE_SENT_FROM_MINIX___ */
#define LIGHT_MASK 0x0
#define BUZZER_MASK 0x1
#define LCD_DISPLAY_TEXT_MASK 0x2
#define LCD_DISPLAY_ANIMATION_MASK 0x3
#define MOTOR_MASK 0x4
#define HUMIDITY_SENSOR_MASK 0x5
#define DECIBEL_SENSOR_MASK 0x6
#define CAMERA_MASK 0x7


#define TURN_LIGHT_ON(x) (BIT(x))

#define TURN_BUZZER_ON(x) ((0b001 << 5) | BIT(x))
#define TURN_BOTH_BUZZERS_ON 0x23
#define TURN_BUZZER_OFF 0x20

#define LCD_DISPLAY_TEXT_MODE(x) ((0b010 << 5) | (x))
#define LCD_DISPLAY_ANIMATION_MODE 0x60

#define TURN_MOTOR_ON(x) ((0b100 << 5) | (x))
#define TURN_MOTOR_OFF 0x80

#define GET_HUMIDITY 0xA0
#define GET_DECIBEL 0xC0

#define CAMERA_PHOTO 0x71
#define CAMERA_STREAM 0x72
#define CAMERA_STOP 0x70


/* ___SOCKET___ */
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4321
