#include "mouse_handler.h"

extern uint8_t page_state;
extern uint8_t out_buf;
extern bool running;
extern int packet_number;
extern mouse_packet_t mouse_packet;
extern Sprite *controlShellButton;
extern Sprite *housePlantButton;
extern Sprite *securityCameraButton;
extern Sprite *exitButton;
extern Sprite *helpButton;
extern Sprite *settingsButton;
extern Sprite *resolutionButton;
extern Sprite *normalCursor;
extern Sprite *backArrow;


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

    else if (mouse_packet.x >= exitButton->x && mouse_packet.x <= exitButton->x + exitButton->width && mouse_packet.y >= exitButton->y && mouse_packet.y <= exitButton->y + exitButton->height)  {
      
      if (mouse_packet.left_button) running = false;
      else exitButton->hover = true;
    }

    else if (mouse_packet.x >= helpButton->x && mouse_packet.x <= helpButton->x + helpButton->width && mouse_packet.y >= helpButton->y && mouse_packet.y <= helpButton->y + helpButton->height)  {
      
      if (mouse_packet.left_button) page_state = HELP;
      else helpButton->hover = true;
    }

    else if (mouse_packet.x >= resolutionButton->x && mouse_packet.x <= resolutionButton->x + resolutionButton->width && mouse_packet.y >= resolutionButton->y && mouse_packet.y <= resolutionButton->y + resolutionButton->height)  {
      
      if (mouse_packet.left_button) page_state = RESOLUTION;
      else resolutionButton->hover = true;
    }

    else {

      controlShellButton->hover = false;
      housePlantButton->hover = false;
      securityCameraButton->hover = false;
      exitButton->hover = false;
      helpButton->hover = false;
      resolutionButton->hover = false;
      
    }
    packet_number = 0;
    draw_page();
  }
  
}

void mouse_control_shell_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}



void mouse_house_plant_handler() {
  mouse_ih();
  parse_bytes_to_packet();

  normalCursor->x = mouse_packet.x;
  normalCursor->y = mouse_packet.y;

  if (mouse_packet.x >= adjustFanPower->x && mouse_packet.x <= adjustFanPower->x + adjustFanPower->width && mouse_packet.y >= adjustFanPower->y && mouse_packet.y <= adjustFanPower->y + adjustFanPower->height)  {
    adjustFanPower->hover = true;
    
  }
  else if (mouse_packet.x >= cam->x && mouse_packet.x <= cam->x + cam->width && mouse_packet.y >= cam->y && mouse_packet.y <= cam->y + cam->height)  {

    cam->hover = true;
  }
  else if (mouse_packet.x >= fan->x && mouse_packet.x <= fan->x + fan->width && mouse_packet.y >= fan->y && mouse_packet.y <= fan->y + fan->height)  {
    if (mouse_packet.left_button) {
      if (db->hover) {
        db->hover = false;
        send_serial_port_msg(0x70);
      } else {
        db->hover = false;
        send_serial_port_msg(0x7F);
      }
    }
  }
  else if (mouse_packet.x >= horn1->x && mouse_packet.x <= horn1->x + horn1->width && mouse_packet.y >= horn1->y && mouse_packet.y <= horn1->y + horn1->height)  {
    if (mouse_packet.left_button) {
      if (horn1->hover) {
        horn1->hover = false;
        if (horn2->hover) {
          send_serial_port_msg(0x22);
        } else {
          send_serial_port_msg(0x20);
        }
        
      } else {
        if (horn2->hover) {
          send_serial_port_msg(0x23);
        } else {
          send_serial_port_msg(0x21);
        }
      }
    }
  }
  else if (mouse_packet.x >= horn2->x && mouse_packet.x <= horn2->x + horn2->width && mouse_packet.y >= horn2->y && mouse_packet.y <= horn2->y + horn2->height)  {
    if (mouse_packet.left_button) {
      if (horn2->hover) {
        horn2->hover = false;
        if (horn1->hover) {
          send_serial_port_msg(0x21);
        } else {
          send_serial_port_msg(0x20);
        }

      } else {
        if (horn1->hover) {
          send_serial_port_msg(0x23);
        } else {
          send_serial_port_msg(0x22);
        }
      }
    }
  }
  else if (mouse_packet.x >= humidity_and_temperature->x && mouse_packet.x <= humidity_and_temperature->x + humidity_and_temperature->width && mouse_packet.y >= humidity_and_temperature->y && mouse_packet.y <= humidity_and_temperature->y + humidity_and_temperature->height)  {
    humidity_and_temperature->hover = true;
  }
  else if (mouse_packet.x >= light_horizontal1->x && mouse_packet.x <= light_horizontal1->x + light_horizontal1->width && mouse_packet.y >= light_horizontal1->y && mouse_packet.y <= light_horizontal1->y + light_horizontal1->height)  {
    light_horizontal1->hover = true;
  }
  else if (mouse_packet.x >= light_horizontal2->x && mouse_packet.x <= light_horizontal2->x + light_horizontal2->width && mouse_packet.y >= light_horizontal2->y && mouse_packet.y <= light_horizontal2->y + light_horizontal2->height)  {
    light_horizontal2->hover = true;
  }
  else if (mouse_packet.x >= light_vertical1->x && mouse_packet.x <= light_vertical1->x + light_vertical1->width && mouse_packet.y >= light_vertical1->y && mouse_packet.y <= light_vertical1->y + light_vertical1->height)  {
    light_vertical1->hover = true;
  }
  else if (mouse_packet.x >= light_vertical2->x && mouse_packet.x <= light_vertical2->x + light_vertical2->width && mouse_packet.y >= light_vertical2->y && mouse_packet.y <= light_vertical2->y + light_vertical2->height)  {
    light_vertical2->hover = true;
  }
  else if (mouse_packet.x >= light_vertical3->x && mouse_packet.x <= light_vertical3->x + light_vertical3->width && mouse_packet.y >= light_vertical3->y && mouse_packet.y <= light_vertical3->y + light_vertical3->height)  {
    light_vertical3->hover = true;
  }
  else if (mouse_packet.x >= percentage->x && mouse_packet.x <= percentage->x + percentage->width && mouse_packet.y >= percentage->y && mouse_packet.y <= percentage->y + percentage->height)  {
    percentage->hover = true;
  }
  else if (mouse_packet.x >= read_humidity->x && mouse_packet.x <= read_humidity->x + read_humidity->width && mouse_packet.y >= read_humidity->y && mouse_packet.y <= read_humidity->y + read_humidity->height)  {
    read_humidity->hover = true;
  }
  else if (mouse_packet.x >= read_sound_intensity->x && mouse_packet.x <= read_sound_intensity->x + read_sound_intensity->width && mouse_packet.y >= read_sound_intensity->y && mouse_packet.y <= read_sound_intensity->y + read_sound_intensity->height)  {
    read_sound_intensity->hover = true;
  }
  else if (mouse_packet.x >= read_temperature->x && mouse_packet.x <= read_temperature->x + read_temperature->width && mouse_packet.y >= read_temperature->y && mouse_packet.y <= read_temperature->y + read_temperature->height)  {
    read_temperature->hover = truadjustFanPower;
  }
  else if (mouse_packet.x >= take_picture->x && mouse_packet.x <= take_picture->x + take_picture->width && mouse_packet.y >= take_picture->y && mouse_packet.y <= take_picture->y + take_picture->height)  {
    take_picture->hover = true;
  }
  else {
    controlShellButton->hover = false;
    housePlantButton->hover = false;
    securityCameraButton->hover = false;
    exitButton->hover = false;
    helpButton->hover = false;
    resolutionButton->hover = false;

    adjustFanPower->hover = false;
    cam->hover = false;
    db->hover = false;
    degrees_celcius->hover = false;
    fan->hover = false;
    horn1->hover = false;
    horn2->hover = false;
    humidity_and_temperature->hover = false;
    light_horizontal1->hover = false;
    light_horizontal2->hover = false;
    light_vertical1->hover = false;
    light_vertical2->hover = false;
    light_vertical3->hover = false;
    percentage->hover = false;
    read_humidity->hover = false;
    read_sound_intensity->hover = false;
    read_temperature->hover = false;
    sound_intensity->hover = false;
    take_picture->hover = false;
  }

  packet_number = 0;
  draw_page();
}



void mouse_security_camera_handler () {
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

   else if (mouse_packet.x >= backArrow->x && mouse_packet.x <= backArrow->x + bigResolutionButton->width && mouse_packet.y >= backArrow->y && mouse_packet.y <= backArrow->y + backArrow->height)  {
      if (mouse_packet.left_button) page_state = MAIN_MENU;
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



