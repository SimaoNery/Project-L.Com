#ifndef _COMMAND_LINE_H_
#define _COMMAND_LINE_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "../../project.h"
#include "CMD.h"
#include "display_text.h"
#include "fan.h"
#include "help.h"
#include "horns.h"
#include "house_state.h"
#include "lights.h"

void input_to_command_line(uint8_t scancode);
void translate_scancode(uint8_t scancode);
void handle_command(char *line_buffer);

#endif /*_COMMAND_LINE_H_*/