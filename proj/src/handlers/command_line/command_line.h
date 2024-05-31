#ifndef _COMMAND_LINE_H_
#define _COMMAND_LINE_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "CMD.h"
#include "lights.h"

void input_to_command_line(uint8_t scancode);
void translate_scancode(uint8_t scancode);
void handle_command(char* line_buffer);

#endif /*_COMMAND_LINE_H_*/


