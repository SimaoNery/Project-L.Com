#include "lights.h"
/**
 * @defgroup Lights Lights
 * 
 */
uint8_t command = 0;

uint32_t lights_counter[5] = {0};
bool count_time[5] = {false};

uint32_t blink_counter[5] = {0};
bool blink_time[5] = {false};

/*!
 * @ingroup Lights Lights
 * @brief Turns on specified lights based on the provided arguments.
 * 
 * This function parses the arguments to determine which lights to turn on, whether to set a timer, or to enable blinking.
 * It updates the command variable and associated counters for timing and blinking, then sends a message to the serial port.
 * 
 * @param args Array of arguments specifying which lights to turn on and optional timers or blinking periods.
 */
void lights_on(char *args[]) {

  uint8_t command_aux = 0;

  uint32_t lights_counter_aux[5] = {0};
  bool count_time_aux[5] = {false};

  uint32_t blink_counter_aux[5] = {0};
  bool blink_time_aux[5] = {false};

  uint8_t lights[] = {LIGHT_1, LIGHT_2, LIGHT_3, LIGHT_4, LIGHT_5};

  if (args[0] == NULL) {
    command_aux |= LIGHT_5 | LIGHT_4 | LIGHT_3 | LIGHT_2 | LIGHT_1;
  }

  bool parsing_args = true;

  bool parsing_lights = true;
  bool parsing_blinking_period = false;
  bool parsing_time = false;

  for (int i = 0; args[i] != NULL; i++) {

    if (parsing_args) {
      if (strcmp(args[i], "-t") == 0) {

        if (i == 0)
          command_aux |= LIGHT_5 | LIGHT_4 | LIGHT_3 | LIGHT_2 | LIGHT_1;

        parsing_args = false;
        parsing_lights = false;
        parsing_time = true;

      } else if (strcmp(args[i], "-p") == 0) {

        if (i == 0)
          command_aux &= LIGHT_4 | LIGHT_3 | LIGHT_2 | LIGHT_1;

        parsing_args = false;
        parsing_lights = false;
        parsing_blinking_period = true;

      } else if (parsing_lights) {
        if (strcmp(args[i], "1") == 0) {
          command_aux |= LIGHT_1;

        } else if (strcmp(args[i], "2") == 0) {
          command_aux |= LIGHT_2;

        } else if (strcmp(args[i], "3") == 0) {
          command_aux |= LIGHT_3;

        } else if (strcmp(args[i], "4") == 0) {
          command_aux |= LIGHT_4;

        } else if (strcmp(args[i], "5") == 0) {
          command_aux |= LIGHT_5;

        } else {
          printf("There is no such light: %s\n", args[i]);
          return;
        }
      } else {
        printf("Invalid argument: %s\n", args[i]);
        return;
      }
    } else if (parsing_time) {
      char *string_part;

      uint32_t time = strtod(args[i], &string_part);
      if (time > 0) {
        if ((strcmp(string_part, "s") == 0) || (strlen(string_part) == 0)) {
          if (time <= 86400) {
            for (int i = 0; i < 5; i++) {
              if (command_aux & lights[i]) {
                lights_counter_aux[i] = time;
                count_time_aux[i] = true;
              }
            }
            parsing_time = false;
            parsing_args = true;
          } else {
            printf("Please provide a time in seconds up to 86400 and no more "
                   "than that.\n");
            return;
          }
        } else if (strcmp(string_part, "m") == 0) {
          if (time <= 1440) {
            time *= 60;
            for (int i = 0; i < 5; i++) {
              if (command_aux & lights[i]) {
                lights_counter_aux[i] = time;
                count_time_aux[i] = true;
              }
            }
            parsing_time = false;
            parsing_args = true;
          } else {
            printf("Please provide a time in minutes up to 1440 and no more "
                   "than that.\n");
            return;
          }

        } else if (strcmp(string_part, "h") == 0) {
          if (time <= 24) {
            time *= 3600;
            for (int i = 0; i < 5; i++) {
              if (command_aux & lights[i]) {
                lights_counter_aux[i] = time;
                count_time_aux[i] = true;
              }
            }
            parsing_time = false;
            parsing_args = true;
          } else {
            printf("Please provide a time in hours up to 24 and no more than "
                   "that.\n");
            return;
          }
        } else {
          printf("%s is not a valid unit of time.\n", string_part);
          return;
        }

      } else if (args[i] == NULL) {
        printf("No time was provided.\n");
        return;
      } else {
        printf("Invalid time provided: %s\n", args[i]);
        return;
      }

    } else if (parsing_blinking_period) {
      char *string_part;

      uint32_t time = strtod(args[i], &string_part);

      if (time > 0) {
        if ((strcmp(string_part, "s") == 0) || (strlen(string_part) == 0)) {
          if (time <= 300) {
            for (int i = 0; i < 5; i++) {
              if (command_aux & lights[i]) {
                blink_counter_aux[i] = time;
                blink_time_aux[i] = true;
              }
            }

            parsing_time = false;
            parsing_args = true;
          } else {
            printf("Please provide a period in seconds up to 300 and no more "
                   "than that.\n");
            return;
          }
        } else if (strcmp(string_part, "m") == 0) {

          if (time <= 5) {
            time *= 60;
            for (int i = 0; i < 5; i++) {
              if (command_aux & lights[i]) {
                blink_counter_aux[i] = time;
                blink_time_aux[i] = true;
              }
            }

            parsing_time = false;
            parsing_args = true;
          } else {
            printf("Please provide a period in minutes up to 5 and no more "
                   "than that.\n");
            break;
          }

        } else {
          printf("%s is not a valid unit of time\n", string_part);
          return;
        }

      } else if (args[i] == NULL) {
        printf("No period was provided.\n");
        return;
      } else {
        printf("Invalid period provided: %s\n", args[i]);
        return;
      }
    }
  }
  command |= command_aux;
  send_serial_port_msg(command);

  for (int i = 0; i < 5; i++) {
    if (count_time_aux[i]) {
      count_time[i] = true;
      lights_counter[i] = lights_counter_aux[i];
    }

    if (blink_time_aux[i]) {
      blink_time[i] = true;
      blink_counter[i] = blink_counter_aux[i];
    }
  }
}

/*!
  * @ingroup Lights Lights
 * @brief Turns off specified lights based on the provided arguments.
 * 
 * This function parses the arguments to determine which lights to turn off.
 * It updates the command variable and resets the counters for the lights being turned off, then sends a message to the serial port.
 * 
 * @param args Array of arguments specifying which lights to turn off.
 */
void lights_off(char *args[]) {

  uint8_t command_aux = command;

  bool turn_off[5] = {false};

  if (args[0] == NULL) {
    for (int i = 0; i < 5; i++) {
      turn_off[i] = true;
    }
    command_aux = 0;
  }

  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "1") == 0) {
      turn_off[i] = true;

      command_aux &= ~(LIGHT_1);

    } else if (strcmp(args[i], "2") == 0) {

      turn_off[i] = true;

      command_aux &= ~(LIGHT_2);

    } else if (strcmp(args[i], "3") == 0) {

      turn_off[i] = true;

      command_aux &= ~(LIGHT_3);

    } else if (strcmp(args[i], "4") == 0) {

      turn_off[i] = true;

    } else if (strcmp(args[i], "5") == 0) {

      turn_off[i] = true;

      command_aux &= ~(LIGHT_5);

    } else {
      printf("There is no such light: %s\n", args[i]);
      return;
    }
  }

  for (int i = 0; i < 5; i++) {
    if (turn_off[i]) {
      count_time[i] = false;
      lights_counter[i] = 0;
      blink_time[i] = false;
      blink_counter[i] = 0;
    }
  }

  command = command_aux;
  send_serial_port_msg(command);
}
