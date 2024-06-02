#include "command_line.h"

extern uint16_t resolution;
extern uint8_t page_state;

char line_buffer[MAX_LINE_LENGTH];
int cursor_pos = 0;  // Track cursor position within the buffer
int line_length = 0; // Track the length of the current line

void input_to_command_line(uint8_t scancode) {
  if (line_length < MAX_LINE_LENGTH)
    translate_scancode(scancode);
  if (scancode == ENTER_MAKE_CODE) {
    printf("\n");
    handle_command(line_buffer);
    printf("minix$ ");
    line_buffer[0] = '\0';
    cursor_pos = line_length = 0;
  }
}

char scancode_to_char[128] = {
    [0x02] = '1', [0x03] = '2',  [0x04] = '3',  [0x05] = '4', [0x06] = '5',
    [0x07] = '6', [0x08] = '7',  [0x09] = '8',  [0x0A] = '9', [0x0B] = '0',
    [0x10] = 'q', [0x11] = 'w',  [0x12] = 'e',  [0x13] = 'r', [0x14] = 't',
    [0x15] = 'y', [0x16] = 'u',  [0x17] = 'i',  [0x18] = 'o', [0x19] = 'p',
    [0x1A] = '+', [0x1B] = '\'', [0x0C] = '\'', [0x1E] = 'a', [0x1F] = 's',
    [0x20] = 'd', [0x21] = 'f',  [0x22] = 'g',  [0x23] = 'h', [0x24] = 'j',
    [0x25] = 'k', [0x26] = 'l',  [0x29] = '\\', [0x2B] = '~', [0x2C] = 'z',
    [0x2D] = 'x', [0x2E] = 'c',  [0x2F] = 'v',  [0x30] = 'b', [0x31] = 'n',
    [0x32] = 'm', [0x33] = ',',  [0x34] = '.',  [0x35] = '-', [0x39] = ' ',
    [0x56] = '<'};

char shift_scancode_to_char[128] = {
    [0x02] = '!', [0x03] = '"', [0x04] = '#', [0x05] = '$', [0x06] = '%',
    [0x07] = '&', [0x08] = '/', [0x09] = '(', [0x0A] = ')', [0x0B] = '=',
    [0x0C] = '?', [0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R',
    [0x14] = 'T', [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I', [0x18] = 'O',
    [0x19] = 'P', [0x1A] = '*', [0x1B] = '`', [0x1E] = 'A', [0x1F] = 'S',
    [0x20] = 'D', [0x21] = 'F', [0x22] = 'G', [0x23] = 'H', [0x24] = 'J',
    [0x25] = 'K', [0x26] = 'L', [0x29] = '|', [0x2B] = '^', [0x2C] = 'Z',
    [0x2D] = 'X', [0x2E] = 'C', [0x2F] = 'V', [0x30] = 'B', [0x31] = 'N',
    [0x32] = 'M', [0x33] = ';', [0x34] = ':', [0x35] = '_', [0x56] = '>'};
// acento filhao
char altgr_scancode_to_char[128] = {
    [0x02] = '|', [0x03] = '@', [0x07] = '&', [0x08] = '{', [0x09] = '[',
    [0x0A] = ']', [0x0B] = '}', [0x0C] = '?', [0x1A] = '[', [0x2B] = '}'};

bool waiting_for_another_char = false;
bool left_shift_pressed = false;
bool right_shift_pressed = false;
bool altgr_pressed = false;
bool caps_lock = false;

void delete_character() {
  if (cursor_pos > 0) {
    memmove(&line_buffer[cursor_pos - 1], &line_buffer[cursor_pos],
            line_length - cursor_pos);
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
  switch (scancode) {
  case WAITING_FOR_ANOTHER_CHAR:
    waiting_for_another_char = true;
    break;
  case LEFT_SHIFT_MAKE_CODE:
    left_shift_pressed = true;
    break;
  case RIGHT_SHIFT_MAKE_CODE:
    right_shift_pressed = true;
    break;
  case LEFT_SHIFT_BREAK_CODE:
    left_shift_pressed = false;
    break;
  case RIGHT_SHIFT_BREAK_CODE:
    right_shift_pressed = false;
    break;
  case CAPS_LOCK_MAKE_CODE:
    caps_lock = !caps_lock;
    break;
  case BACKSPACE_MAKE_CODE:
    delete_character();
    break;
  default:
    if (waiting_for_another_char) {
      waiting_for_another_char = false;
      switch (scancode) {
      case ALTGR_MAKE_CODE:
        altgr_pressed = true;
        break;
      case ALTGR_BREAK_CODE:
        altgr_pressed = false;
        break;
      case LEFT_ARROW_MAKE_CODE: // Left arrow key
        if (cursor_pos > 0) {
          printf("\033[D"); // Move cursor left
          cursor_pos--;
        }
        break;
      case RIGHT_ARROW_MAKE_CODE: // Right arrow key
        if (cursor_pos < line_length) {
          printf("\033[C"); // Move cursor right
          cursor_pos++;
        }
        break;
      case DOWN_ARROW_MAKE_CODE: // Down arrow key (not handled)
        break;
      case UP_ARROW_MAKE_CODE: // Up arrow key (not handled)
        break;
      case DELETE_MAKE_CODE:
        delete_character();
      }
      break;
    }
    if ((scancode & BIT(7)) == 0) {
      ch = scancode_to_char[scancode];
      if (caps_lock && ch >= 'a' && ch <= 'z') {
        if (!left_shift_pressed && !right_shift_pressed)
          ch -= 32;
      } else if (left_shift_pressed || right_shift_pressed) {
        char char_to_print = shift_scancode_to_char[scancode];
        if (char_to_print)
          ch = char_to_print;
      } else if (altgr_pressed) {
        char char_to_print = altgr_scancode_to_char[scancode];
        if (char_to_print)
          ch = char_to_print;
      }

      if (ch) {
        if (cursor_pos < line_length)
          memmove(&line_buffer[cursor_pos + 1], &line_buffer[cursor_pos],
                  line_length - cursor_pos);
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
char *tokens[MAX_TOKENS];

void tokenize_line(char *line_buffer) {

  memset(tokens, 0, sizeof(tokens));

  char *token = strtok(line_buffer, " ");
  int index = 0;
  while (token != NULL && index < MAX_TOKENS - 1) {
    tokens[index++] = token;
    token = strtok(NULL, " ");
  }

  tokens[index] = NULL;
}

void handle_command(char *line_buffer) {

  tokenize_line(line_buffer);
  if (tokens[0] == NULL) {
    return;
  }

  char *command = tokens[0];

  if (strcmp(command, "lights_on") == 0) {
    lights_on(&tokens[1]);
  } else if (strcmp(command, "lights_off") == 0) {
    lights_off(&tokens[1]);
  } else if (strcmp(command, "horns_on") == 0) {
    horns_on(&tokens[1]);
  } else if (strcmp(command, "horns_off") == 0) {
    horns_off(&tokens[1]);
  } else if (strcmp(command, "write_message") == 0) {
    display_text(&tokens[1]);
  } else if (strcmp(command, "fan_on") == 0) {
    fan_on(&tokens[1]);
  } else if (strcmp(command, "fan_off") == 0) {
    fan_off();
  } else if (strcmp(command, "livestream") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "take_photo") == 0) {
    printf("dnqjwq");
  } else if (strcmp(command, "get_humidity_and_temperature") == 0) {
    get_humidity_and_temperature();
  } else if (strcmp(command, "get_sound_intensity") == 0) {
    get_sound_intensity();
  } else if (strcmp(command, "help") == 0) {
    help(&tokens[1]);
  } else if (strcmp(command, "exit") == 0) {
    vg_set_graphics_mode(resolution);
    page_state = MAIN_MENU;
    draw_page();
    write_mouse_cmd(ENABLE_DATA_REPORTING);
  } else {
    printf("%s: not found\n", command);
  }
}

/*
  Commands

   lights_on: Turns on the chosen lights.
   Typing `lights_on <1,2,3,4,5>
*/