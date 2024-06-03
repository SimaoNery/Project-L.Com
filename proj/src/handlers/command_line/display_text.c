#include "display_text.h"
/**
 * @defgroup Display_Text Display_Text
 * 
 */


/**
 * @ingroup Display_Text Display_Text
 * @brief Displays text by sending it to a serial port.
 *
 * This function takes an array of strings (arguments) and concatenates them into a single buffer.
 * It then sends the concatenated text to a serial port, preceded by a command identifier.
 *
 * @param args An array of strings to be displayed. The array must be NULL-terminated.
 *
 * @note If no text is provided (i.e., args[0] is NULL), the function will print an error message and return.
 * @note The maximum number of characters that can be sent is defined by MAX_CHARS.
 */
void display_text(char *args[]) {

  if (args[0] == NULL) {
    printf("No text was provided.\n");
    return;
  }

  uint8_t command = DISPLAY_TEXT_ID;
  char buffer[MAX_CHARS];
  int total_chars = 0;

  for (int i = 0; args[i] != NULL && total_chars < MAX_CHARS; i++) {
    if (i != 0)
      buffer[total_chars++] = ' ';
    int j = 0;
    while (args[i][j] != '\0' && total_chars < MAX_CHARS) {
      buffer[total_chars++] = args[i][j++];
      buffer[total_chars] = '\0';
    }
  }
  command |= (total_chars - 1);
  send_serial_port_msg(command);
  int i = 0;
  while (buffer[i] != '\0') {
    send_serial_port_msg(buffer[i++]);
  }
}
