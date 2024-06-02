#include "fan.h"

uint8_t command_fan = FAN_ID;

uint32_t fan_counter = 0;
bool fan_time = false;

void fan_on(char *args[]) {

  uint8_t command_aux = FAN_ID;
  uint32_t fan_counter_aux = 0;
  bool fan_time_aux = false;

  int i = 0;

  if (args[i] == NULL)
    command_aux |= FAN_MAX_POWER;

  else if (strcmp(args[0], "-t") != 0) {
    i++;
    char *endptr;
    long power = 0;

    power = strtol(args[0], &endptr, 10);

    if (endptr != args[0] && power > 0 && power <= 31) {
      command_aux |= (uint8_t)power;
    } else {
      printf("Please provide a power value between 1 and 31.\n");
      return;
    }
  }
  if (args[i] != NULL) {
    if (i == 0)
      command_aux |= FAN_MAX_POWER;
    if (strcmp(args[i], "-t") == 0) {
      i++;
      if (args[i] != NULL) {
        char *string_part;

        uint32_t time = strtod(args[i], &string_part);
        if (time > 0) {
          if ((strcmp(string_part, "s") == 0) || (strlen(string_part) == 0)) {
            if (time <= 86400) {
              fan_counter_aux = time;
              fan_time_aux = true;
            } else {
              printf("Please provide a time in seconds up to 86400 and no more "
                     "than that.\n");
              return;
            }
          } else if (strcmp(string_part, "m") == 0) {
            if (time <= 1440) {
              time *= 60;
              fan_counter_aux = time;
              fan_time_aux = true;
            } else {
              printf("Please provide a time in minutes up to 1440 and no more "
                     "than that.\n");
              return;
            }

          } else if (strcmp(string_part, "h") == 0) {
            if (time <= 24) {
              time *= 3600;
              fan_counter_aux = time;
              fan_time_aux = true;
            } else {
              printf("Please provide a time in hours up to 24 and no more than "
                     "that.\n");
              return;
            }
          } else {
            printf("%s is not a valid unit of time.\n", string_part);
            return;
          }

        } else {
          printf("Invalid time provided: %s\n", args[i]);
          return;
        }
      } else {
        printf("No time was provided.\n");
        return;
      }

    } else {
      printf("Invalid argument: %s\n", args[i]);
      return;
    }
  }

  command_fan = command_aux;
  send_serial_port_msg(command_fan);

  if (fan_time_aux) {
    fan_counter = fan_counter_aux;
    fan_time = true;
  }
}

void fan_off() {
  fan_counter = 0;
  fan_time = false;
  command_fan = FAN_ID;
  send_serial_port_msg(command_fan);
}