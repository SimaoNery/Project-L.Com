#ifndef _SERIAL_PORT_HANDLER_H_
#define _SERIAL_PORT_HANDLER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

void serial_port_main_menu_handler ();
void serial_port_control_shell_handler ();
void serial_port_house_plant_handler ();
void serial_port_security_camera_handler ();
void serial_port_display_message_handler ();
void serial_port_settings_handler ();
void serial_port_help_handler ();

#endif /*_SERIAL_PORT_HANDLER_H_*/
