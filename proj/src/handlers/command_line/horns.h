#ifndef _HORNS_H_
#define _HORNS_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "CMD.h"
#include "drivers/serial_port/serial.h"

void horns_on(char *args[]);
void horns_off(char *args[]);

#endif /*_HORNS_*/
