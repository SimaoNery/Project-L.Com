#include "house_state.h"
/**
 * @defgroup House_state House_state
 * 
 */
bool asking_for_humidity_and_temp = false;
bool asking_for_sound = false;

/**
 * @ingroup House_state House_state
 * @brief Requests the current humidity and temperature.
 *
 * This function sets the flag for requesting humidity and temperature and sends
 * the appropriate command to the serial port.
 */
void get_humidity_and_temperature() {
  asking_for_humidity_and_temp = true;
  send_serial_port_msg(HUMIDITY_AND_TEMPERATURE_ID);
}

/**
  * @ingroup House_state House_state
 * @brief Requests the current sound intensity.
 *
 * This function sets the flag for requesting sound intensity and sends
 * the appropriate command to the serial port.
 */
void get_sound_intensity() {
  asking_for_sound = true;
  send_serial_port_msg(HUMIDITY_AND_TEMPERATURE_ID);
}
