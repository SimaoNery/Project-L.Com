#include "draw.h"

extern uint8_t page_state;
extern uint16_t resolution;

extern real_time_info time_info;

extern int humidity_temp[4];
extern int sound_intensity[2];

/*!
 * @brief Draws the current page based on the page state.
 * 
 * This function switches between different page states and calls the appropriate drawing functions.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_page() {
  switch (page_state) {
    case MAIN_MENU:
      draw_main_menu();
      break;
    case CONTROL_SHELL:
      draw_control_shell();
      break;
    case HOUSE_PLANT:
      draw_house_plant();
      break;
    case RESOLUTION:
      draw_resolution();
      break;
    case HELP:
      draw_help();
      break;
  }

  return 0;
}

/*!
 * @brief Draws the main menu page.
 * 
 * This function draws the main menu sprite, main buttons, and the mouse pointer.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_main_menu() {
  if (draw_sprite(mainMenu) != 0) {
    printf("Error: Problems occured while trying to draw -mainMenu- sprite! \n");
    return 1;
  }

  if (draw_date_time() != 0) {
    printf("Error: Problems occured while trying to draw the date and time! \n");
    return 1;
  }

  if (draw_main_buttons() != 0) {
    printf("Error: Problems occured while trying to draw Main Menu buttons! \n");
    return 1;
  }

  if (draw_sprite(normalCursor) != 0) {
    printf("ErrorDISABLE_DATA_REPORTING: Problems occured while trying to draw the mouse pointer! \n");
    return 1;
  }

  if(buffering_method() != 0) {
    printf("Error detecting buffering method! \n");
    return 1;
  }

  return 0;
}

/*!
 * @brief Draws the control shell page.
 * 
 * This function exits the video graphics mode and prints the control shell welcome message.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_control_shell() {
  if(write_mouse_cmd(DISABLE_DATA_REPORTING) != 0) return 1;

  if (vg_exit() != 0) return 1;

  printf("Welcome to Wagner's House Control Shell!\nYour house's devices are at the distance of a command.\nType help for a list of commands or exit to leave the shell.\nminix$ ");

  return 0;
  
}

int draw_display_message() {
  return 0;
}

/*!
 * @brief Draws the resolution page.
 * 
 * This function draws the resolution page sprite, resolution buttons, and the mouse pointer.
 * It also detects the buffering method.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_resolution() {
  if(draw_sprite(resolutionPage) != 0) {
    printf("Error: Problems occured while trying to draw -resolutionPage- sprite! \n");
    return 1;
  }

  if(draw_resolution_buttons() != 0) {
    printf("Error: Problems occured while trying to draw Resolution Page Buttons! \n");
    return 1;
  }

  if (draw_sprite(normalCursor) != 0) {
    printf("Error: Problems occured while trying to draw the mouse pointer! \n");
    return 1;
  }

  if(buffering_method() != 0) {
    printf("Error detecting buffering method! \n");
    return 1;
  }

  return 0;
}

/*!
 * @brief Draws the house plant page.
 * 
 * This function sends serial port messages, draws the house plant sprite, house plant buttons, and the mouse pointer.
 * It also detects the buffering method.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_house_plant() {

  send_serial_port_msg(BIT(7));
  send_serial_port_msg(0xA0);

  if(draw_sprite(housePlant) != 0) {
     printf("Error: Problems occured while trying to draw -housePlantPage- sprite! \n");
    return 1;
  }

  if (draw_humidity() != 0) {
    printf("Error: Problems occured while trying to draw the ! \n");
    return 1;
  }

  if (draw_temperature() != 0) {
    printf("Error: Problems occured while trying to draw the date and time! \n");
    return 1;
  }

  if (draw_sound_intensity() != 0) {
    printf("Error: Problems occured while trying to draw the date and time! \n");
    return 1;
  }
  
  if(draw_housePlant_buttons() != 0) {
    printf("Error: Problems occured while trying to draw housePlant buttons! \n");
    return 1;
  }

  if(draw_sprite(normalCursor) != 0) {
    printf("Error: Problems occured while trying to draw the mouse pointer! \n");
    return 1;
  }

  if(buffering_method() != 0) {
    printf("Error detecting buffering method! \n");
    return 1;
  }

  return 0;
}

int draw_help() {
  return 0;
}

/*!
 * @brief Draws the main menu buttons.
 * 
 * This function draws the control shell button, house plant button, exit button, help button, and resolution button.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int draw_main_buttons() {
  if (draw_sprite(controlShellButton) != 0) {
    printf("Error: Problems occured trying to draw -controlShellButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(housePlantButton) != 0) {
    printf("Error: Problems occured trying to draw -housePlantButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(exitButton) != 0) {
    printf("Error: Problems occured trying to draw -displayMessageButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(helpButton) != 0) {
    printf("Error: Problems occured trying to draw -helpButtonButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(resolutionButton) != 0) {
    printf("Error: Problems occured trying to draw -resolutionButton- sprite! \n");
    return 1;
  };

  return 0;
}

/*!
 * @brief Draws the resolutions  buttons.
 * 
 * This function draws the resolutions buttons
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int (draw_resolution_buttons)() {
  if (draw_sprite(smallResolutionButton) != 0) {
    printf("Error: Problems occured trying to draw -smallResolutionButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(bigResolutionButton) != 0) {
    printf("Error: Problems occured trying to draw -bigResolutionButton- sprite! \n");
    return 1;
  };

  if(draw_sprite(backArrow) != 0) {
    printf("Error: Problems occured while trying to draw -backArrow- sprite! \n");
    return 1;
  }

  return 0;
}


/*!
 * @brief Draws the House Plant buttons.
 * 
 * This function draws the House Plant buttons
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int(draw_housePlant_buttons)() {
  if (draw_sprite(adjustFanPower) != 0) {
    printf("Error: Problems occurred trying to draw -adjustFanPower- sprite! \n");
    return 1;
  };


  if (draw_sprite(fan) != 0) {
    printf("Error: Problems occurred trying to draw -fan- sprite! \n");
    return 1;
  };

  if (draw_sprite(horn1) != 0) {
    printf("Error: Problems occurred trying to draw -horn1- sprite! \n");
    return 1;
  };

  if (draw_sprite(horn2) != 0) {
    printf("Error: Problems occurred trying to draw -horn2- sprite! \n");
    return 1;
  };

  if (draw_sprite(humidity_and_temperature) != 0) {
    printf("Error: Problems occurred trying to draw -humidity_and_temperature- sprite! \n");
    return 1;
  };

  if (draw_sprite(light_horizontal1) != 0) {
    printf("Error: Problems occurred trying to draw -light_horizontal1- sprite! \n");
    return 1;
  };

  if (draw_sprite(light_horizontal2) != 0) {
    printf("Error: Problems occurred trying to draw -light_horizontal2- sprite! \n");
    return 1;
  }

  if (draw_sprite(light_vertical1) != 0) {
    printf("Error: Problems occurred trying to draw -light_vertical1- sprite! \n");
    return 1;
  };

  if (draw_sprite(light_vertical2) != 0) {
    printf("Error: Problems occurred trying to draw -light_vertical2- sprite! \n");
    return 1;
  };

  if (draw_sprite(light_vertical3) != 0) {
    printf("Error: Problems occurred trying to draw -light_vertical3- sprite! \n");
    return 1;
  };

  if (draw_sprite(read_humidity) != 0) {
    printf("Error: Problems occurred trying to draw -read_humidity- sprite! \n");
    return 1;
  };

  if (draw_sprite(read_sound_intensity) != 0) {
    printf("Error: Problems occurred trying to draw -read_sound_intensity- sprite! \n");
    return 1;
  };

  if (draw_sprite(read_temperature) != 0) {
    printf("Error: Problems occurred trying to draw -read_temperature- sprite! \n");
    return 1;
  };

  if (draw_sprite(sound_int) != 0) {
    printf("Error: Problems occurred trying to draw -sound_int- sprite! \n");
    return 1;
  };

  if(draw_sprite(backArrow) != 0) {
    printf("Error: Problems occurred while trying to draw -backArrow- sprite! \n");
    return 1;
  }

  return 0;
}

int draw_digit_value(Sprite* to_draw, int height, int width, int *x_counter) {
  to_draw->x = width + *x_counter;
  to_draw->y = height;

  if (draw_sprite(to_draw) != 0) {
    printf("Error: Problems occurred trying to draw! \n");
    return 1;
  }
  *x_counter += to_draw->width;
  return 0;
}

int draw_digit_date(Sprite* to_draw, int *x_counter) {
  to_draw->x = *x_counter;
  if (draw_sprite(to_draw) != 0) {
    printf("Error: Problems occurred trying to draw! \n");
    return 1;
  }
  *x_counter += to_draw->width;
  return 0;
}

int draw_unit_sprites(uint8_t time_val, int *x_counter) {

  char num_str[3];
  sprintf(num_str, "%02u", time_val); 

  for (int i = 0; num_str[i] != '\0'; i++) {

    
    switch (num_str[i]) {
    case '0':
      if (draw_digit_date(zero, x_counter) != 0) return 1;
      break;

    case '1':
      if (draw_digit_date(one, x_counter) != 0) return 1;
      break;
    
    case '2':
      if (draw_digit_date(two, x_counter) != 0) return 1;
      break;

    case '3':
      if (draw_digit_date(three, x_counter) != 0) return 1;
      break;

    case '4':
      if (draw_digit_date(four, x_counter) != 0) return 1;
      break;

    case '5':
      if (draw_digit_date(five, x_counter) != 0) return 1;
      break;

    case '6':
      if (draw_digit_date(six, x_counter) != 0) return 1;
      break;

    case '7':
      if (draw_digit_date(seven, x_counter) != 0) return 1;
      break;

    case '8':
      if (draw_digit_date(eight, x_counter) != 0) return 1;
      break;

    case '9':
      if (draw_digit_date(nine, x_counter) != 0) return 1;
      break;

    }
  }

  return 0;
}


int draw_value_sprites(int val, int height, int width, int *x_counter) {

  char num_str[3];
  sprintf(num_str, "%0d", val); 

  for (int i = 0; num_str[i] != '\0'; i++) {

    
    switch (num_str[i]) {
    case '0':
      if (draw_digit_value(zero, height, width, x_counter) != 0) return 1;
      break;

    case '1':
      if (draw_digit_value(one, height,  width,x_counter) != 0) return 1;
      break;
    
    case '2':
      if (draw_digit_value(two, height,  width,x_counter) != 0) return 1;
      break;

    case '3':
      if (draw_digit_value(three, height, width, x_counter) != 0) return 1;
      break;

    case '4':
      if (draw_digit_value(four, height, width, x_counter) != 0) return 1;
      break;

    case '5':
      if (draw_digit_value(five, height, width, x_counter) != 0) return 1;
      break;

    case '6':
      if (draw_digit_value(six, height, width, x_counter) != 0) return 1;
      break;

    case '7':
      if (draw_digit_value(seven, height,  width,x_counter) != 0) return 1;
      break;

    case '8':
      if (draw_digit_value(eight, height, width, x_counter) != 0) return 1;
      break;

    case '9':
      if (draw_digit_value(nine, height, width, x_counter) != 0) return 1;
      break;

    }
  }

  return 0;
}


int draw_date_time() {
  
  uint8_t year = time_info.year;
  uint8_t month = time_info.month;
  uint8_t day = time_info.day;
  uint8_t hour = time_info.hours;
  uint8_t minute = time_info.minutes;

  int x_counter = 0;

  if (draw_digit_date(two, &x_counter) != 0) return 1;
  if (draw_digit_date(zero, &x_counter) != 0) return 1;
  if (draw_unit_sprites(year, &x_counter) != 0) return 1;
  if (draw_digit_date(slash, &x_counter) != 0) return 1;
  if (draw_unit_sprites(month, &x_counter) != 0) return 1;
  if (draw_digit_date(slash, &x_counter) != 0) return 1;
  if (draw_unit_sprites(day, &x_counter) != 0) return 1;
  x_counter += two->width;
  if (draw_unit_sprites(hour, &x_counter) != 0) return 1;

  if (draw_digit_date(colon, &x_counter) != 0) return 1;

  if (draw_unit_sprites(minute, &x_counter) != 0) return 1;

  return 0;
}

int draw_humidity() {
  int humidity = (humidity_temp[0] << 8) | (humidity_temp[1]);

  int x_counter = 0;

  int x = 0;
  int y = 0;
  if(resolution == (uint16_t)RES_1152_864) {
    x = 880;
    y = 308;
  }
  else {
    x = 604;
    y = 189;
  }
  if(draw_value_sprites(humidity, y, x, &x_counter) != 0) {
    return 1;
  }

  if(draw_digit_value(percentage, y, x, &x_counter) != 0) return 1;

  return 0;
}

int draw_temperature() {
  int temperature = (humidity_temp[2] << 8) | (humidity_temp[3]);

  int x_counter = 0;


  int x = 0;
  int y = 0;
  if(resolution == (uint16_t)RES_1152_864) {
    x = 863;
    y = 458;
  }
  else {
    x = 592;
    y = 301;
  }

  if(draw_value_sprites(temperature, y, x, &x_counter) != 0) {
    return 1;
  }

  if(draw_digit_value(degrees_celcius, y, x, &x_counter) != 0) return 1;

  return 0;
}

int draw_sound_intensity() {
  int sound = (sound_intensity[0] << 8) | (sound_intensity[1]);

  int x_counter = 0;


  int x = 0;
  int y = 0;
  if(resolution == (uint16_t)RES_1152_864) {
    x = 851;
    y = 608;
  }
  else {
    x = 584;
    y = 414;
  }

  if(draw_value_sprites(sound, y, x, &x_counter) != 0) {
    return 1;
  }

  if(draw_digit_value(db, y, x, &x_counter) != 0) return 1;

  return 0;
}
