#ifndef _LCOM_CMD_H_
#define _LCOM_CMD_H_

#include <lcom/lcf.h>

/** @defgroup CMD CMD
 * @
 *
 */

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 50

#define WAITING_FOR_ANOTHER_CHAR 0xE0
#define LEFT_SHIFT_MAKE_CODE 0x2A
#define RIGHT_SHIFT_MAKE_CODE 0x36
#define LEFT_SHIFT_BREAK_CODE 0xAA
#define RIGHT_SHIFT_BREAK_CODE 0xB6
#define CAPS_LOCK_MAKE_CODE 0x3A
#define BACKSPACE_MAKE_CODE 0x0E
#define ALTGR_MAKE_CODE 0x38
#define ALTGR_BREAK_CODE 0XB8
#define LEFT_ARROW_MAKE_CODE 0x4B
#define RIGHT_ARROW_MAKE_CODE 0x4D
#define UP_ARROW_MAKE_CODE 0x48
#define DOWN_ARROW_MAKE_CODE 0x50
#define DELETE_MAKE_CODE 0x53
#define ENTER_MAKE_CODE 0x1C

#define LIGHT_1 BIT(0)
#define LIGHT_2 BIT(1)
#define LIGHT_3 BIT(2)
#define LIGHT_4 BIT(3)
#define LIGHT_5 BIT(4)

#define FAN_ID BIT(6) | BIT(5)
#define FAN_TURN_OFF 0
#define FAN_MAX_POWER 31

#define HUMIDITY_AND_TEMPERATURE_ID BIT(7)
#define SOUND_INTENSITY_ID BIT(7) | BIT(5)
#define DISPLAY_TEXT_ID BIT(6)
#define HORN_ID BIT(5)
#define HORN_1 BIT(0)
#define HORN_2 BIT(1)

#define MAX_CHARS 32

#endif /* _LCOM_CMD_H */
