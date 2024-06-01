#include "mouse_handler.h"

extern uint8_t page_state;
extern uint8_t out_buf;
extern int packet_number;
extern mouse_packet_t mouse_packet;
extern Sprite *controlShellButton;
extern Sprite *housePlantButton;
extern Sprite *securityCameraButton;
extern Sprite *displayMessageButton;
extern Sprite *helpButton;
extern Sprite *settingsButton;
extern Sprite *settingsButton;
extern Sprite *normalCursor;


void mouse_main_menu_handler () {
  mouse_ih();
  if (packet_number == 3) {
    parse_bytes_to_packet();

    normalCursor->x = mouse_packet.x;
    normalCursor->y = mouse_packet.y;

  
    if (mouse_packet.x >= controlShellButton->x && mouse_packet.x <= controlShellButton->x + controlShellButton->width && mouse_packet.y >= controlShellButton->y && mouse_packet.y <= controlShellButton->y + controlShellButton->height)  {

      if (mouse_packet.left_button) page_state = CONTROL_SHELL;
      else controlShellButton->hover = true;
    }

    else if (mouse_packet.x >= housePlantButton->x && mouse_packet.x <= housePlantButton->x + housePlantButton->width && mouse_packet.y >= housePlantButton->y && mouse_packet.y <= housePlantButton->y + housePlantButton->height)  {
      
      if (mouse_packet.left_button) page_state = HOUSE_PLANT;
      else housePlantButton->hover = true;
    }

    else if (mouse_packet.x >= securityCameraButton->x && mouse_packet.x <= securityCameraButton->x + securityCameraButton->width && mouse_packet.y >= securityCameraButton->y && mouse_packet.y <= securityCameraButton->y + securityCameraButton->height)  {
      
      if (mouse_packet.left_button) page_state = SECURITY_CAMERA;
      else securityCameraButton->hover = true;
    }

    else if (mouse_packet.x >= displayMessageButton->x && mouse_packet.x <= displayMessageButton->x + displayMessageButton->width && mouse_packet.y >= displayMessageButton->y && mouse_packet.y <= displayMessageButton->y + displayMessageButton->height)  {
      
      if (mouse_packet.left_button) page_state = DISPLAY_MESSAGE;
      else displayMessageButton->hover = true;
    }

    else if (mouse_packet.x >= helpButton->x && mouse_packet.x <= helpButton->x + helpButton->width && mouse_packet.y >= helpButton->y && mouse_packet.y <= helpButton->y + helpButton->height)  {
      
      if (mouse_packet.left_button) page_state = HELP;
      else helpButton->hover = true;
    }

    else if (mouse_packet.x >= settingsButton->x && mouse_packet.x <= settingsButton->x + settingsButton->width && mouse_packet.y >= settingsButton->y && mouse_packet.y <= settingsButton->y + settingsButton->height)  {
      
      if (mouse_packet.left_button) page_state = SETTINGS;
      else settingsButton->hover = true;
    }

    else {

      controlShellButton->hover = false;
      housePlantButton->hover = false;
      securityCameraButton->hover = false;
      displayMessageButton->hover = false;
      helpButton->hover = false;
      settingsButton->hover = false;
      
    }
    packet_number = 0;
    draw_page();
  }
  
}

void mouse_control_shell_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}

void mouse_house_plant_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}

void mouse_security_camera_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}

void mouse_display_message_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}

void mouse_settings_handler () {
  mouse_ih();
  if (packet_number == 3) {
    parse_bytes_to_packet();

    normalCursor->x = mouse_packet.x;
    normalCursor->y = mouse_packet.y;

  
    if (mouse_packet.x >= smallResolutionButton->x && mouse_packet.x <= smallResolutionButton->x + smallResolutionButton->width && mouse_packet.y >= smallResolutionButton->y && mouse_packet.y <= smallResolutionButton->y + smallResolutionButton->height)  {
      smallResolutionButton->hover = true;
      if (mouse_packet.left_button) change_resolution(RES_800_600);
    }

    else if (mouse_packet.x >= bigResolutionButton->x && mouse_packet.x <= bigResolutionButton->x + bigResolutionButton->width && mouse_packet.y >= bigResolutionButton->y && mouse_packet.y <= bigResolutionButton->y + bigResolutionButton->height)  {
      bigResolutionButton->hover = true;
      if (mouse_packet.left_button) change_resolution(RES_1152_864);
    }

    else {

      smallResolutionButton->hover = false;
      bigResolutionButton->hover = false;
      
    }

    packet_number = 0;
    draw_page();
  }

}

void mouse_help_handler () {}



