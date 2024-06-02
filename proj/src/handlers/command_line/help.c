#include "help.h"
/**
 * @defgroup Help Help
 * 
 */


/**
 * @ingroup Help Help
 * @brief Provides help information for available commands.
 *
 * This function displays a list of available commands with their general descriptions.
 * If a specific command is provided as an argument, detailed information about that command is displayed.
 *
 * @param args An array of strings representing the command arguments. The first argument
 *             can be the name of the command to get detailed information about. If no command name
 *             is provided, a list of all available commands with their general descriptions will be displayed.
 */
void help(char *args[]) {
  if (args[0] == NULL) {
    printf("\nAvailable commands:\n");
    printf("   exit - Exits the console and returns to the main menu.\n");
    printf("   fan_off - Turns off the fan.\n");
    printf("   fan_on - Turns on the fan with an optional power setting. "
           "Optionally, set a timer to turn off the fan.\n");
    printf("   get_humidity_and_temperature - Retrieves and displays the "
           "current humidity and temperature of the house.\n");
    printf("   get_sound_intensity - Retrieves and displays the current sound "
           "intensity level in the house.\n");
    printf("   help - Provides a general description of each available command "
           "or detailed information about a specific command.\n");
    printf("   horns_off - Turns off specified horns or both horns if no "
           "arguments are provided.\n");
    printf("   horns_on - Turns on specified horns or both horns if no "
           "arguments are provided. Optionally, set a timer to turn off the "
           "horns or set a honking period.\n");
    printf("   lights_off - Turns off specified lights or all lights if no "
           "arguments are provided.\n");
    printf("   lights_on - Turns on specified lights or all lights if no "
           "arguments are provided. Optionally, set a timer to turn off the "
           "lights or set a blinking period.\n");
    printf(
        "   write_message - Displays the specified message on the screen.\n");
  } else if (strcmp(args[0], "help") == 0) {
    printf("\nhelp [ command_name ]\n\n");
    printf("Provides a general description of each available command or "
           "detailed information about a specific command.\n\n");
    printf("Arguments:\n\n");
    printf("   command_name\n");
    printf("   Specifies the name of the command to get detailed information "
           "about. If no command name is provided, a list of all available "
           "commands with their general descriptions will be displayed.\n");
  } else if (strcmp(args[0], "lights_on") == 0) {
    printf("\n");
    printf("lights_on [ light_number ... ] [ -t { time_s | time_m | time_h } ] "
           "[ -p { period_s | period_m } ]\n\n");
    printf("Turns on specified lights or all lights if no arguments are "
           "provided. Optionally, set a timer to turn off the lights or set a "
           "blinking period.\n\n");
    printf("Options:\n\n");
    printf("   -t { time | time_s | time_m | time_h }\n\n");
    printf(
        "   Sets a timer to turn off the lights after the specified time.\n\n");
    printf("   Arguments: \n\n");
    printf("      time: Time in seconds (default if no unit is provided, e.g., "
           "-t 12).\n");
    printf("      time_s: Time in seconds (e.g., -t 12s).\n");
    printf("      time_m: Time in minutes (e.g., -t 5m).\n");
    printf("      time_h: Time in hours (e.g., -t 1h).\n");
    printf("\n");
    printf("   -p { period | period_s | period_m }\n\n");
    printf("   Sets the period of blinking. If this flag is not set, the "
           "lights do not blink.\n\n");
    printf("   Arguments: \n\n");
    printf("      period: Period in seconds (default if no unit is provided, "
           "e.g., -p 2).\n");
    printf("      period_s: Blinking period in seconds (e.g., -p 2s).\n");
    printf("      period_m: Blinking period in minutes (e.g., -p 1m).\n");
    printf("\n");
    printf("Arguments: \n\n");
    printf("   light_number ...\n");
    printf(
        "   A list of one or more light numbers (e.g., 1 2 3) specifying which "
        "lights to turn on. If it is not provided, all lights will turn on.\n");
    printf("\n");
  } else if (strcmp(args[0], "lights_off") == 0) {
    printf("\n");
    printf("lights_off [ light_number ... ]\n\n");
    printf("Turns off specified lights or all lights if no arguments are "
           "provided.\n\n");
    printf("Arguments: \n\n");
    printf("   light_number ...\n");
    printf("   A list of one or more light numbers (e.g., 1 2 3) specifying "
           "which lights to turn off. If it is not provided, all lights will "
           "turn off.\n");
    printf("\n");
  } else if (strcmp(args[0], "horns_on") == 0) {
    printf("\n");
    printf("horns_on [ horn_number ... ] [ -t { time_s | time_m | time_h } ] [ "
           "-p { period_s | period_m } ]\n\n");
    printf("Turns on specified horns or both horns if no arguments are "
           "provided. Optionally, set a timer to turn off the horns or set a "
           "honking period.\n\n");
    printf("Options:\n\n");
    printf("   -t { time | time_s | time_m | time_h }\n\n");
    printf(
        "   Sets a timer to turn off the horns after the specified time.\n\n");
    printf("   Arguments: \n\n");
    printf("      time: Time in seconds (default if no unit is provided, e.g., "
           "-t 12).\n");
    printf("      time_s: Time in seconds (e.g., -t 12s).\n");
    printf("      time_m: Time in minutes (e.g., -t 5m).\n");
    printf("      time_h: Time in hours (e.g., -t 1h).\n");
    printf("\n");
    printf("   -p { period | period_s | period_m }\n\n");
    printf("   Sets the period of honking. If this flag is not set, the horns "
           "do not honk repeatedly.\n\n");
    printf("   Arguments: \n\n");
    printf("      period: Period in seconds (default if no unit is provided, "
           "e.g., -p 2).\n");
    printf("      period_s: Honking period in seconds (e.g., -p 2s).\n");
    printf("      period_m: Honking period in minutes (e.g., -p 1m).\n");
    printf("\n");
    printf("Arguments: \n\n");
    printf("   horn_number ...\n");
    printf(
        "   A list of one or two horn numbers (e.g., 1 2) specifying which "
        "horns to turn on. If it is not provided, both horns will turn on.\n");
    printf("\n");
  } else if (strcmp(args[0], "horns_off") == 0) {
    printf("\n");
    printf("horns_off [ horn_number ... ]\n\n");
    printf("Turns off specified horns or both horns if no arguments are "
           "provided.\n\n");
    printf("Arguments: \n\n");
    printf("   horn_number ...\n");
    printf("   A list of one or two horn numbers (e.g., 1 2) specifying which "
           "horns to turn off. If it is not provided, both horns will turn "
           "off.\n");
    printf("\n");
  } else if (strcmp(args[0], "fan_on") == 0) {
    printf("\n");
    printf("fan_on [ power ] [ -t { time_s | time_m | time_h } ]\n\n");
    printf("Turns on the fan with an optional power setting. Optionally, set a "
           "timer to turn off the fan.\n\n");
    printf("Options:\n\n");
    printf("   -t { time | time_s | time_m | time_h }\n\n");
    printf("   Sets a timer to turn off the fan after the specified time.\n\n");
    printf("   Arguments: \n\n");
    printf("      time: Time in seconds (default if no unit is provided, e.g., "
           "-t 12).\n");
    printf("      time_s: Time in seconds (e.g., -t 12s).\n");
    printf("      time_m: Time in minutes (e.g., -t 5m).\n");
    printf("      time_h: Time in hours (e.g., -t 1h).\n");
    printf("\n");
    printf("Arguments: \n\n");
    printf("   power\n");
    printf(
        "   Specifies the power level of the fan. A number from 1 to 31 (e.g., "
        "15). If it is not provided, the fan is turned on at maximum power.\n");
    printf("\n");
  } else if (strcmp(args[0], "fan_off") == 0) {
    printf("\n");
    printf("fan_off\n\n");
    printf("Turns off the fan.\n\n");
    printf("This command does not require any arguments.\n");
    printf("\n");
  } else if (strcmp(args[0], "write_message") == 0) {
    printf("\n");
    printf("write_message <message>\n\n");
    printf("Displays the specified message on the screen.\n\n");
    printf("Arguments: \n\n");
    printf("   message\n");
    printf("   Specifies the message to display (e.g., Hello, World!)\n");
    printf("\n");
  } else if (strcmp(args[0], "get_humidity_and_temperature") == 0) {
    printf("\n");
    printf("get_humidity_and_temperature\n\n");
    printf("Retrieves and displays the current humidity and temperature of the "
           "house.\n\n");
    printf("\n");
  } else if (strcmp(args[0], "get_sound_intensity") == 0) {
    printf("\n");
    printf("get_sound_intensity\n\n");
    printf("Retrieves and displays the current sound intensity level in the "
           "house.\n\n");
    printf("\n");
  } else if (strcmp(args[0], "exit") == 0) {
    printf("\n");
    printf("exit\n\n");
    printf("Exits the console and returns to the main menu.\n\n");
    printf("\n");
  } else {
    printf("Unknown command: %s\n", args[0]);
  }
}
