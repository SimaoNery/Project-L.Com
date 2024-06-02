#include "horns.h"
/**
 * @defgroup Horns Horns
 * 
 */

uint8_t command_horns = HORN_ID;

uint32_t horns_counter[2] = {0};
bool count_time_horns[2] = {false};

uint32_t blink_counter_horns[2] = {0};
bool blink_time_horns[2] = {false};


/**
 * @ingroup Horns Horns
 * @brief Turns the horns on with optional timer and blinking period.
 *
 * This function turns on the specified horns. If no horns are specified, both horns are turned on.
 * Optionally, a timer can be set to turn off the horns after a specified duration, and a blinking period can be set.
 *
 * @param args An array of strings representing the command arguments. The arguments can include:
 *             - Horn numbers ("1" or "2") to specify which horns to turn on.
 *             - "-t <time><unit>" to set a timer, where <unit> can be 's' (seconds), 'm' (minutes), or 'h' (hours).
 *             - "-p <period><unit>" to set a blinking period, where <unit> can be 's' (seconds) or 'm' (minutes).
 *
 * @note If no horn numbers are provided, both horns will be turned on.
 * @note The maximum timer duration is 86400 seconds (24 hours).
 * @note The maximum blinking period is 300 seconds (5 minutes).
 */
void horns_on(char *args[]) {

  uint8_t command_aux = 0;

  uint32_t horns_counter_aux[2] = {0};
  bool count_time_horns_aux[2] = {false};

  uint32_t blink_counter_horns_aux[2] = {0};
  bool blink_time_horns_aux[2] = {false};

  uint8_t lights[] = {HORN_1, HORN_2};

  if (args[0] == NULL) {
    command_aux |= HORN_2 | HORN_1;
  }

  bool parsing_args = true;

  bool parsing_lights = true;
  bool parsing_blinking_period = false;
  bool parsing_time = false;

  for (int i = 0; args[i] != NULL; i++) {

    if (parsing_args) {
      if (strcmp(args[i], "-t") == 0) {

        if (i == 0)
          command_aux |= HORN_2 | HORN_1;

        parsing_args = false;
        parsing_lights = false;
        parsing_time = true;

      } else if (strcmp(args[i], "-p") == 0) {

        if (i == 0)
          command_aux |= HORN_2 | HORN_1;

        parsing_args = false;
        parsing_lights = false;
        parsing_blinking_period = true;

      } else if (parsing_lights) {
        if (strcmp(args[i], "1") == 0) {
          command_aux |= HORN_1;

        } else if (strcmp(args[i], "2") == 0) {
          command_aux |= HORN_2;

        } else {
          printf("There is no such horn: %s\n", args[i]);
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
            for (int i = 0; i < 2; i++) {
              if (command_aux & lights[i]) {
                horns_counter_aux[i] = time;
                count_time_horns_aux[i] = true;
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
            for (int i = 0; i < 2; i++) {
              if (command_aux & lights[i]) {
                horns_counter_aux[i] = time;
                count_time_horns_aux[i] = true;
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
            for (int i = 0; i < 2; i++) {
              if (command_aux & lights[i]) {
                horns_counter_aux[i] = time;
                count_time_horns_aux[i] = true;
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
            for (int i = 0; i < 2; i++) {
              if (command_aux & lights[i]) {
                blink_counter_horns_aux[i] = time;
                blink_time_horns_aux[i] = true;
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
            for (int i = 0; i < 2; i++) {
              if (command_aux & lights[i]) {
                blink_counter_horns_aux[i] = time;
                blink_time_horns_aux[i] = true;
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
  command_horns |= command_aux;
  send_serial_port_msg(command_horns);

  for (int i = 0; i < 2; i++) {
    if (count_time_horns_aux[i]) {
      count_time_horns[i] = true;
      horns_counter[i] = horns_counter_aux[i];
    }

    if (blink_time_horns_aux[i]) {
      blink_time_horns[i] = true;
      blink_counter_horns[i] = blink_counter_horns_aux[i];
    }
  }
}

/**
  * @ingroup Horns Horns
 * @brief Turns the horns off.
 *
 * This function turns off the specified horns. If no horns are specified, both horns are turned off.
 *
 * @param args An array of strings representing the command arguments. The arguments can include:
 *             - Horn numbers ("1" or "2") to specify which horns to turn off.
 *
 * @note If no horn numbers are provided, both horns will be turned off.
 */
void horns_off(char *args[]) {

  uint8_t command_aux = command_horns;

  bool turn_off[2] = {false};

  if (args[0] == NULL) {
    for (int i = 0; i < 2; i++) {
      turn_off[i] = true;
    }
    command_aux = HORN_ID;
  }

  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "1") == 0) {
      turn_off[i] = true;

      command_aux &= ~(HORN_1);

    } else if (strcmp(args[i], "2") == 0) {

      turn_off[i] = true;

      command_aux &= ~(HORN_2);

    } else {
      printf("There is no such horn: %s\n", args[i]);
      return;
    }
  }

  for (int i = 0; i < 2; i++) {
    if (turn_off[i]) {
      count_time_horns[i] = false;
      horns_counter[i] = 0;
      blink_time_horns[i] = false;
      blink_counter_horns[i] = 0;
    }
  }

  command_horns = command_aux;
  send_serial_port_msg(command_horns);
}
