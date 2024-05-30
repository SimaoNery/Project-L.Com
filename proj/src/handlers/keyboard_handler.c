#include "keyboard_handler.h"

extern uint8_t out_buf;
extern bool running;

int written_chars_counter = 0;


void keyboard_main_menu_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

void keyboard_control_shell_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;

  //kbd_print_scancode(!(out_buf & BIT(7)), out_buf == 0xE0 ? 2 : 1, &out_buf);
  translate_scancode(out_buf);
  
}

void keyboard_house_plant_handler () {}

void keyboard_security_camera_handler () {}

void keyboard_display_message_handler () {}

void keyboard_settings_handler () {}

void keyboard_help_handler () {}

char scancode_to_char[128] = {
    [0x02] = '1',    [0x03] = '2',    [0x04] = '3',    [0x05] = '4',
    [0x06] = '5',    [0x07] = '6',    [0x08] = '7',    [0x09] = '8',
    [0x0A] = '9',    [0x0B] = '0',    [0x0C] = '-',    [0x0D] = '=',
    [0x0E] = '\b',   // Backspace
    [0x0F] = '\t',   // Tab
    [0x10] = 'q',    [0x11] = 'w',    [0x12] = 'e',    [0x13] = 'r',
    [0x14] = 't',    [0x15] = 'y',    [0x16] = 'u',    [0x17] = 'i',
    [0x18] = 'o',    [0x19] = 'p',    [0x1A] = '[',    [0x1B] = ']',
    [0x1C] = '\n',   // Enter
    [0x1E] = 'a',    [0x1F] = 's',    [0x20] = 'd',    [0x21] = 'f',
    [0x22] = 'g',    [0x23] = 'h',    [0x24] = 'j',    [0x25] = 'k',
    [0x26] = 'l',    [0x27] = ';',    [0x28] = '\'',   [0x29] = '`',
    [0x2B] = '\\',   [0x2C] = 'z',    [0x2D] = 'x',    [0x2E] = 'c',
    [0x2F] = 'v',    [0x30] = 'b',    [0x31] = 'n',    [0x32] = 'm',
    [0x33] = ',',    [0x34] = '.',    [0x35] = '/',    [0x37] = '*',    // Keypad *
    [0x39] = ' ',    // Space
    [0x47] = '7',    // Keypad 7/Home
    [0x48] = '8',    // Keypad 8/Up
    [0x49] = '9',    // Keypad 9/PgUp
    [0x4A] = '-',    // Keypad -
    [0x4B] = '4',    // Keypad 4/Left
    [0x4C] = '5',    // Keypad 5
    [0x4D] = '6',    // Keypad 6/Right
    [0x4E] = '+',    // Keypad +
    [0x4F] = '1',    // Keypad 1/End
    [0x50] = '2',    // Keypad 2/Down
    [0x51] = '3',    // Keypad 3/PgDn
    [0x52] = '0',    // Keypad 0/Ins
    [0x53] = '.',    // Keypad .Del
};

char shift_scancode_to_char[128] = {
    [0x02] = '!',    [0x03] = '@',    [0x04] = '#',    [0x05] = '$',
    [0x06] = '%',    [0x07] = '^',    [0x08] = '&',    [0x09] = '*',
    [0x0A] = '(',    [0x0B] = ')',    [0x0C] = '_',    [0x0D] = '+',
    [0x10] = 'Q',    [0x11] = 'W',    [0x12] = 'E',    [0x13] = 'R',
    [0x14] = 'T',    [0x15] = 'Y',    [0x16] = 'U',    [0x17] = 'I',
    [0x18] = 'O',    [0x19] = 'P',    [0x1A] = '{',    [0x1B] = '}',
    [0x1E] = 'A',    [0x1F] = 'S',    [0x20] = 'D',    [0x21] = 'F',
    [0x22] = 'G',    [0x23] = 'H',    [0x24] = 'J',    [0x25] = 'K',
    [0x26] = 'L',    [0x27] = ':',    [0x28] = '"',    [0x29] = '~',
    [0x2B] = '|',    [0x2C] = 'Z',    [0x2D] = 'X',    [0x2E] = 'C',
    [0x2F] = 'V',    [0x30] = 'B',    [0x31] = 'N',    [0x32] = 'M',
    [0x33] = '<',    [0x34] = '>',    [0x35] = '?'
};
/*
char altgr_scancode_to_char[128] = {
    [0x02] = '¹',    [0x03] = '²',    [0x04] = '³',    [0x05] = '¢',
    [0x06] = '€',    [0x07] = '£',    [0x08] = '¥',    [0x09] = 'ª',
    [0x0A] = 'º',    [0x0B] = '§',    [0x10] = '@',    [0x11] = 'ł',
    [0x12] = '€',    [0x13] = '®',    [0x14] = 'þ',    [0x15] = '←',
    [0x16] = 'ú',    [0x17] = 'í',    [0x18] = 'ó',    [0x19] = 'π',
    [0x1E] = 'á',    [0x1F] = 'ß',    [0x20] = 'ð',    [0x21] = 'đ',
    [0x22] = 'ŋ',    [0x23] = 'ħ',    [0x24] = 'j',    [0x25] = 'ĸ',
    [0x26] = 'ł',    [0x2C] = 'ž',    [0x2D] = 'ß',    [0x2E] = '©',
    [0x2F] = 'ð',    [0x30] = 'æ',    [0x31] = 'ŋ',    [0x32] = 'µ',
    [0x33] = 'ç',    [0x34] = '˙',    [0x35] = '¸'
};
*/
bool waiting_for_another_char = false;
bool left_shift_pressed = false;
bool right_shift_pressed = false;
bool altgr_pressed = false;
bool caps_lock = false;


void translate_scancode(uint8_t scancode) {
  char ch;
  switch (scancode)
  {
  case 0xE0:
    waiting_for_another_char = true;
  case 0x2A:
    left_shift_pressed = true;
    break;
  case 0x36:
    right_shift_pressed = true;
    break;
  case 0xAA:
    left_shift_pressed = false;
    break;
  case 0xB6:
    right_shift_pressed = false;  
    break;
  case 0x38:
    altgr_pressed = true;
    break;
  case 0xB8:
    altgr_pressed = false;
    break;
  case 0x3A:
    caps_lock = !caps_lock;
    break;  
  default:
    if ((scancode & BIT(7)) == 0) {
      ch = scancode_to_char[scancode];
      if (waiting_for_another_char) {
        waiting_for_another_char = false;
      }

      if (caps_lock && ch >= 'a' && ch <= 'z') {
        if (!left_shift_pressed && !right_shift_pressed) ch -= 32;
        printf("%c", ch);
      }
      else if (left_shift_pressed || right_shift_pressed) {
        char char_to_print  = shift_scancode_to_char[scancode];
        if (char_to_print) printf("%c", char_to_print);
        else if (ch) printf("%c", ch);
      }

      else if (ch) {
        printf("%c", ch);
      }
    }

  }
}



