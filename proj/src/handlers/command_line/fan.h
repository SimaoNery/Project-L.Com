#ifndef _FAN_H_
#define _FAN_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "CMD.h"
#include "drivers/serial_port/serial.h"

void fan_on(char *args[]);
void fan_off();

#endif /*_FAN_*/
