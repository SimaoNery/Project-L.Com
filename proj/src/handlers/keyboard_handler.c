#include "keyboard_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

extern uint8_t out_buf;
extern bool running;

#define MAX_LINE_LENGTH 1024
char line_buffer[MAX_LINE_LENGTH];
int cursor_pos = 0;  // Track cursor position within the buffer
int line_length = 0; // Track the length of the current line

void keyboard_main_menu_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) running = false;
}

void keyboard_control_shell_handler () {
  kbc_int_handler();
  if (out_buf == 0x81) {running = false;}
  if (line_length < MAX_LINE_LENGTH) translate_scancode(out_buf);
  if (out_buf == 0x1C) {
    printf("\n");
    handle_command(line_buffer);
    printf("\nminix$ ");
    line_buffer[0] = '\0';
    cursor_pos = line_length = 0;
  } 
  
}

void keyboard_house_plant_handler () {}

void keyboard_security_camera_handler () {}

void keyboard_display_message_handler () {}

void keyboard_settings_handler () {}

void keyboard_help_handler () {}

char scancode_to_char[128] = {
    [0x02] = '1',    [0x03] = '2',    [0x04] = '3',    [0x05] = '4',
    [0x06] = '5',    [0x07] = '6',    [0x08] = '7',    [0x09] = '8',
    [0x0A] = '9',    [0x0B] = '0',    
    [0x10] = 'q',    [0x11] = 'w',    [0x12] = 'e',    [0x13] = 'r',
    [0x14] = 't',    [0x15] = 'y',    [0x16] = 'u',    [0x17] = 'i',
    [0x18] = 'o',    [0x19] = 'p',    [0x1A] = '+',    [0x1B] = '\'',
    [0x0C] = '\'',
    [0x1E] = 'a',    [0x1F] = 's',    [0x20] = 'd',    [0x21] = 'f',
    [0x22] = 'g',    [0x23] = 'h',    [0x24] = 'j',    [0x25] = 'k',
    [0x26] = 'l',   [0x29] = '\\',    [0x2B] = '~',
    [0x2C] = 'z',    [0x2D] = 'x',    [0x2E] = 'c',
    [0x2F] = 'v',    [0x30] = 'b',    [0x31] = 'n',    [0x32] = 'm',
    [0x33] = ',', [0x34] = '.',    [0x35] = '-',
    [0x39] = ' ',  
};

char shift_scancode_to_char[128] = {
    [0x02] = '!',    [0x03] = '"',    [0x04] = '#',    [0x05] = '$',
    [0x06] = '%',    [0x07] = '&',    [0x08] = '/',    [0x09] = '(',
    [0x0A] = ')',    [0x0B] = '=',    [0x0C] = '?',
    [0x10] = 'Q',    [0x11] = 'W',    [0x12] = 'E',    [0x13] = 'R',
    [0x14] = 'T',    [0x15] = 'Y',    [0x16] = 'U',    [0x17] = 'I',
    [0x18] = 'O',    [0x19] = 'P',    [0x1A] = '*',    [0x1B] = '`',
    [0x1E] = 'A',    [0x1F] = 'S',    [0x20] = 'D',    [0x21] = 'F',
    [0x22] = 'G',    [0x23] = 'H',    [0x24] = 'J',    [0x25] = 'K',
    [0x26] = 'L',    [0x29] = '|',    [0x2B] = '^',
    [0x2C] = 'Z',    [0x2D] = 'X',    [0x2E] = 'C',
    [0x2F] = 'V',    [0x30] = 'B',    [0x31] = 'N',    [0x32] = 'M',
    [0x33] = ';',    [0x34] = ':',    [0x35] = '_'
};
//acento filhao
char altgr_scancode_to_char[128] = {
    [0x02] = '|',    [0x03] = '@',    [0x07] = '&',    [0x08] = '{',    [0x09] = '[',
    [0x0A] = ']',    [0x0B] = '}',    [0x0C] = '?', [0x1A] = '[',
    [0x2B] = '}'
};

bool waiting_for_another_char = false;
bool left_shift_pressed = false;
bool right_shift_pressed = false;
bool altgr_pressed = false;
bool caps_lock = false;

void delete_character() {
    if (cursor_pos > 0) {
        memmove(&line_buffer[cursor_pos - 1], &line_buffer[cursor_pos], line_length - cursor_pos);
        cursor_pos--;
        line_length--;
        line_buffer[line_length] = '\0';
        printf("\b \b");
        if (cursor_pos < line_length) {        
            printf("%s", &line_buffer[cursor_pos]);
            printf(" \b");
            for (int i = line_length; i > cursor_pos; i--) {
                printf("\033[D"); 
            }
        }
    }
}

void translate_scancode(uint8_t scancode) {
  char ch;
  switch (scancode)
  {
  case 0xE0:
    waiting_for_another_char = true;
    break;
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
  case 0x0E:
    delete_character();
    break;
  default:
    if (waiting_for_another_char) {
      waiting_for_another_char = false;
        switch (scancode)
        {
        case 0x4B: // Left arrow key
          if (cursor_pos > 0) {
              printf("\033[D"); // Move cursor left
              cursor_pos--;
          }
          break;
        case 0x4D: // Right arrow key
          if (cursor_pos < line_length) {
              printf("\033[C"); // Move cursor right
              cursor_pos++;
          }
          break;
        case 0x50: // Down arrow key (not handled)
          break;
        case 0x48: // Up arrow key (not handled)
          break;
        case 0x53:
          delete_character();
        }
      break;
    }
    if ((scancode & BIT(7)) == 0) {
      ch = scancode_to_char[scancode];
      if (caps_lock && ch >= 'a' && ch <= 'z') {
        if (!left_shift_pressed && !right_shift_pressed) ch -= 32;
      }
      else if (left_shift_pressed || right_shift_pressed) {
        char char_to_print  = shift_scancode_to_char[scancode];
        if (char_to_print) ch = char_to_print;
      }
      else if (altgr_pressed) {
        char char_to_print  = altgr_scancode_to_char[scancode];
        if (char_to_print) ch = char_to_print;
      }
      
      if (ch) {
        if (cursor_pos < line_length)
          memmove(&line_buffer[cursor_pos + 1], &line_buffer[cursor_pos], line_length - cursor_pos);
        line_buffer[cursor_pos] = ch;
        line_length++;
        line_buffer[line_length] = '\0';
        printf("%c", ch);
        if (cursor_pos < line_length) {
          printf("%s", &line_buffer[cursor_pos + 1]);
          for (int i = line_length; i > cursor_pos + 1; i--) {
            printf("\033[D"); 
          }
        }
        cursor_pos++;
      }
    }
  }
}

#define MAX_TOKENS 50
char* tokens[MAX_TOKENS];

void tokenize_line(char* line_buffer) {
    
  memset(tokens, 0, sizeof(tokens));

  char* token = strtok(line_buffer, " ");
  int index = 0;
  while (token != NULL && index < MAX_TOKENS - 1) {
      tokens[index++] = token;
      token = strtok(NULL, " ");
  }

  tokens[index] = NULL;
}

void handle_command(char* line_buffer) {

  tokenize_line(line_buffer);
  if (tokens[0] == NULL) {
    return;
  }

  char* command = tokens[0];

  if (strcmp(command, "lights_on") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "lights_off") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "horn_on") == 0) {
    printf("dnqjwq");   
  } else if (strcmp(command, "horn_off") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "write_message") == 0) {
    printf("dnqjwq");  
  } else if (strcmp(command, "fan_on") == 0) {
    printf("dnqjwq"); 
  } else if (strcmp(command, "fan_off") == 0) {
    printf("dnqjwq");   
  } else if (strcmp(command, "livestream") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "take_photo") == 0) {
    printf("dnqjwq");    
  } else if (strcmp(command, "get_humidity") == 0) {
    printf("dnqjwq");   
  } else if (strcmp(command, "get_sound_intensity") == 0) {
    printf("dnqjwq"); 
  } else if (strcmp(command, "help") == 0) {
    printf("dnqjwq");   
  } else if (strcmp(command, "help") == 0) {
    printf("dnqjwq");           
  } else {
    printf("%s: not found", command);
  }

}


