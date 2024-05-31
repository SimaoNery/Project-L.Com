#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "CMD.h"
#include "drivers/serial_port/serial.h"

void lights_on(char* args[]);
void lights_off(char* args[]);

#endif /*_LIGHTS_*/


