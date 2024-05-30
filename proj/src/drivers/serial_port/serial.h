#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "queue.h"
#include "serial_headers.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

int serial_initial_config();

int serial_port_subscribe_int(uint8_t *bit_no);

int serial_port_unsubscribe_int();

void serial_port_int_handler();

int send_serial_port_msg(uint8_t msg);

int read_serial_port_msg();

int serial_port_clear_int();

void serial_port_clear_all();

queue_t *get_queue();

#endif /* _SERIAL_H_ */

