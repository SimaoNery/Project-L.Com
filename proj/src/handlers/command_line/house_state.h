#ifndef _HOUSE_STATE_H_
#define _HOUSE_STATE_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "CMD.h"
#include "drivers/serial_port/serial.h"

void get_humidity_and_temperature();
void get_sound_intensity();

#endif /*__HOUSE_STATE_*/