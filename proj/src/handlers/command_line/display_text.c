#include "display_text.h"

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
