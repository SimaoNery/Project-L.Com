#include "draw.h"

extern uint8_t page_state;
extern uint16_t resolution;

int draw_page() {
  switch (page_state) {
    case MAIN_MENU:
      draw_main_menu();
      break;
    case CONTROL_SHELL:
      draw_control_shell();
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

int draw_main_menu() {
  if (draw_sprite(mainMenu) != 0) {
    printf("Error: Problems occured while trying to draw -mainMenu- sprite! \n");
    return 1;
  }
   
  if (draw_main_buttons() != 0) {
    printf("Error: Problems occured while trying to draw Main Menu buttons! \n");
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

int draw_control_shell() {
  if (vg_exit() != 0) return 1;

  printf("Welcome to Wagner's House Control Shell!\nYour house's devices are at the distance of a command.\nType help for a list of commands or exit to leave the shell.\nminix$ ");

  return 0;
  
}

int draw_display_message() {
  return 0;
}

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

int draw_house_plant() {

  send_serial_port_msg(BIT(7));
  send_serial_port_msg(0xA0)); //1010 0000

  if(draw_sprite(housePlant) != 0) {
     printf("Error: Problems occured while trying to draw -housePlantPage- sprite! \n");
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

int(draw_housePlant_buttons)() {
  if (draw_sprite(adjustFanPower) != 0) {
    printf("Error: Problems occurred trying to draw -adjustFanPower- sprite! \n");
    return 1;
  };
  
  if (draw_sprite(db) != 0) {
    printf("Error: Problems occurred trying to draw -db- sprite! \n");
    return 1;
  };

  if (draw_sprite(degrees_celcius) != 0) {
    printf("Error: Problems occurred trying to draw -degrees_celcius- sprite! \n");
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

  if (draw_sprite(percentage) != 0) {
    printf("Error: Problems occurred trying to draw -percentage- sprite! \n");
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

  if (draw_sprite(sound_intensity) != 0) {
    printf("Error: Problems occurred trying to draw -sound_intensity- sprite! \n");
    return 1;
  };

  if(draw_sprite(backArrow) != 0) {
    printf("Error: Problems occurred while trying to draw -backArrow- sprite! \n");
    return 1;
  }

  return 0;
}
