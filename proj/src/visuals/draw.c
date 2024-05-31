#include "draw.h"

extern uint8_t page_state;

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
    case SECURITY_CAMERA:
      draw_security_camera();
      break;
    case DISPLAY_MESSAGE:
      draw_display_message();
      break;
    case SETTINGS:
      draw_settings();
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

  if(swap_buffers() != 0) {
    printf("Error: Problems occured while trying to swap buffers! \n");
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

int draw_security_camera() {
  
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
  printf("conaça");
  return 0;
}

int draw_settings() {
  if(draw_sprite(settingsPage) != 0) {
    printf("Error: Problems occured while trying to draw -settingsPage- sprite! \n");
    return 1;
  }

  if(draw_settings_buttons() != 0) {
    printf("Error: Problems occured while trying to draw Settings Page Buttons! \n");
    return 1;
  }

  if (draw_sprite(normalCursor) != 0) {
    printf("Error: Problems occured while trying to draw the mouse pointer! \n");
    return 1;
  }

  if(swap_buffers() != 0) {
    printf("Error: Problems occured while trying yo swap buffers! \n");
    return 1;
  }

  return 0;
}

int draw_house_plant() {
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

  if (draw_sprite(securityCameraButton) != 0) {
    printf("Error: Problems occured trying to draw -securityCameraButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(displayMessageButton) != 0) {
    printf("Error: Problems occured trying to draw -displayMessageButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(helpButton) != 0) {
    printf("Error: Problems occured trying to draw -helpButtonButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(settingsButton) != 0) {
    printf("Error: Problems occured trying to draw -settingsButton- sprite! \n");
    return 1;
  };

  return 0;
}

int draw_settings_buttons() {
  if (draw_sprite(smallResolutionButton) != 0) {
    printf("Error: Problems occured trying to draw -smallResolutionButton- sprite! \n");
    return 1;
  };

  if (draw_sprite(bigResolutionButton) != 0) {
    printf("Error: Problems occured trying to draw -bigResolutionButton- sprite! \n");
    return 1;
  };

  return 0;
}
