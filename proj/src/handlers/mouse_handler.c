#include "mouse_handler.h"

/**
 * @defgroup Mouse_Handler Mouse_Handler
 * 
 */

extern uint8_t page_state;
extern uint8_t out_buf;
extern bool running;
extern int packet_number;
extern mouse_packet_t mouse_packet;
extern Sprite *controlShellButton;
extern Sprite *housePlantButton;
extern Sprite *exitButton;
extern Sprite *helpButton;
extern Sprite *resolutionPage;
extern Sprite *normalCursor;
extern Sprite *backArrow;
extern Sprite *housePlant;

extern Sprite *adjustFanPower;
extern Sprite *db;
extern Sprite *degrees_celcius;
extern Sprite *fan;
extern Sprite *horn1;
extern Sprite *horn2;
extern Sprite *humidity_and_temperature;
extern Sprite *light_horizontal1;
extern Sprite *light_horizontal2;
extern Sprite *light_vertical1;
extern Sprite *light_vertical2;
extern Sprite *light_vertical3;
extern Sprite *percentage;
extern Sprite *read_humidity;
extern Sprite *read_sound_intensity;
extern Sprite *read_temperature;
extern Sprite *sound_int;

/*!
 * @brief Handles mouse input for the main menu.
 * @ingroup Mouse_Handler Mouse_Handler
 * This function processes mouse packets and updates the cursor position and button states.
 * It also checks for button clicks and updates the page state accordingly.
 */
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
      exitButton->hover = false;
      helpButton->hover = false;
      resolutionButton->hover = false;
      
    }
    packet_number = 0;
    draw_page();
  }
  
}

/*!
 * @brief Handles mouse input for the control shell.
 * @ingroup Mouse_Handler Mouse_Handler
 * This function processes mouse packets and updates the mouse packet structure.
 */
void mouse_control_shell_handler () {
  mouse_ih();
  if(packet_number == 3) {
     parse_bytes_to_packet();
  }
}

bool asking_for_humidity = false;
bool asking_for_temp = false;
bool asking_for_sound_plant = false;

/*!
 * @brief Handles mouse input for the house plant section.
 * @ingroup Mouse_Handler Mouse_Handler
 * This function processes mouse packets, updates the cursor position, and checks for button hovers and clicks.
 */

void mouse_house_plant_handler() {
  mouse_ih();
  if(packet_number == 3) {
    parse_bytes_to_packet();

  normalCursor->x = mouse_packet.x;
  normalCursor->y = mouse_packet.y;




  if (mouse_packet.x >= fan->x && mouse_packet.x <= fan->x + fan->width && mouse_packet.y >= fan->y && mouse_packet.y <= fan->y + fan->height)  {
    if (mouse_packet.left_button) {
      if (fan->hover) {
        fan->hover = false;
        send_serial_port_msg(0x70);
      } else {
        fan->hover = true;
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
        horn1->hover = true;
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
        horn2->hover = true;
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
    if (mouse_packet.left_button) {
      asking_for_humidity = true;
      asking_for_temp = true;
      send_serial_port_msg(0x80);
    }
  }
  else if (mouse_packet.x >= light_horizontal1->x && mouse_packet.x <= light_horizontal1->x + light_horizontal1->width && mouse_packet.y >= light_horizontal1->y && mouse_packet.y <= light_horizontal1->y + light_horizontal1->height)  {
   uint8_t lights_hover = (light_vertical3->hover << 4) | (light_vertical2->hover << 3) | (light_vertical1->hover << 2) | (light_horizontal2->hover << 1);
   if (mouse_packet.left_button) {
      if (light_horizontal1->hover) {
        light_horizontal1->hover = false;
        send_serial_port_msg(lights_hover);

      } else {
        light_horizontal1->hover = true;
        lights_hover |= BIT(0);
        send_serial_port_msg(lights_hover);
      }
    }
  }
  else if (mouse_packet.x >= light_horizontal2->x && mouse_packet.x <= light_horizontal2->x + light_horizontal2->width && mouse_packet.y >= light_horizontal2->y && mouse_packet.y <= light_horizontal2->y + light_horizontal2->height)  {
   uint8_t lights_hover = (light_vertical3->hover << 4) | (light_vertical2->hover << 3) | (light_vertical1->hover << 2) | (light_horizontal1->hover);
   if (mouse_packet.left_button) {
      if (light_horizontal2->hover) {
        light_horizontal2->hover = false;
        send_serial_port_msg(lights_hover);

      } else {
        light_horizontal2->hover = true;
        lights_hover |= BIT(1);
        send_serial_port_msg(lights_hover);
      }
    }
  }
  else if (mouse_packet.x >= light_vertical1->x && mouse_packet.x <= light_vertical1->x + light_vertical1->width && mouse_packet.y >= light_vertical1->y && mouse_packet.y <= light_vertical1->y + light_vertical1->height)  {
   uint8_t lights_hover = (light_vertical3->hover << 4) | (light_vertical2->hover << 3) | (light_horizontal2->hover << 1) | (light_horizontal1->hover);
   if (mouse_packet.left_button) {
      if (light_vertical1->hover) {
        light_vertical1->hover = false;
        send_serial_port_msg(lights_hover);

      } else {
        light_vertical1->hover = true;
        lights_hover |= BIT(2);
        send_serial_port_msg(lights_hover);
      }
    }
  }
  else if (mouse_packet.x >= light_vertical2->x && mouse_packet.x <= light_vertical2->x + light_vertical2->width && mouse_packet.y >= light_vertical2->y && mouse_packet.y <= light_vertical2->y + light_vertical2->height)  {
   uint8_t lights_hover = (light_vertical3->hover << 4) | (light_vertical1->hover << 2) | (light_horizontal2->hover << 1) | (light_horizontal1->hover);
   if (mouse_packet.left_button) {
      if (light_vertical2->hover) {
        light_vertical2->hover = false;
        send_serial_port_msg(lights_hover);

      } else {
        light_vertical2->hover = true;
        lights_hover |= BIT(3);
        send_serial_port_msg(lights_hover);
      }
    }
  }
  else if (mouse_packet.x >= light_vertical3->x && mouse_packet.x <= light_vertical3->x + light_vertical3->width && mouse_packet.y >= light_vertical3->y && mouse_packet.y <= light_vertical3->y + light_vertical3->height)  {
   uint8_t lights_hover = (light_vertical2->hover << 3) | (light_vertical1->hover << 2) | (light_horizontal2->hover << 1) | (light_horizontal1->hover);
   if (mouse_packet.left_button) {
      if (light_vertical3->hover) {
        light_vertical3->hover = false;
        send_serial_port_msg(lights_hover);

      } else {
        light_vertical3->hover = true;
        lights_hover |= BIT(4);
        send_serial_port_msg(lights_hover);
      }
    }
  }
  else if (mouse_packet.x >= read_humidity->x && mouse_packet.x <= read_humidity->x + read_humidity->width && mouse_packet.y >= read_humidity->y && mouse_packet.y <= read_humidity->y + read_humidity->height)  {
    read_humidity->hover = true;
    if (mouse_packet.left_button) {
      asking_for_humidity = true;
      send_serial_port_msg(0x80);
    }

  }
  else if (mouse_packet.x >= read_sound_intensity->x && mouse_packet.x <= read_sound_intensity->x + read_sound_intensity->width && mouse_packet.y >= read_sound_intensity->y && mouse_packet.y <= read_sound_intensity->y + read_sound_intensity->height)  {
    
    read_sound_intensity->hover = true;
    if (mouse_packet.left_button) {
      asking_for_sound_plant = true;
      send_serial_port_msg(0xA0);
    }

  }
  else if (mouse_packet.x >= sound_int->x && mouse_packet.x <= sound_int->x + sound_int->width && mouse_packet.y >= sound_int->y && mouse_packet.y <= sound_int->y + sound_int->height)  {
    
    sound_int->hover = true;
    if (mouse_packet.left_button) {
      asking_for_sound_plant = true;
      send_serial_port_msg(0xA0);
    }
  }

  else if (mouse_packet.x >= read_temperature->x && mouse_packet.x <= read_temperature->x + read_temperature->width && mouse_packet.y >= read_temperature->y && mouse_packet.y <= read_temperature->y + read_temperature->height)  {
    read_temperature->hover = true;

    if (mouse_packet.left_button) {
      asking_for_temp = true;
      send_serial_port_msg(0x80);
    }
  }

  else if (mouse_packet.x >= backArrow->x && mouse_packet.x <= backArrow->x + bigResolutionButton->width && mouse_packet.y >= backArrow->y && mouse_packet.y <= backArrow->y + backArrow->height)  {
    if (mouse_packet.left_button) {
      page_state = MAIN_MENU;
      zero->x = 0;
      zero->y = 0;
      one->x = 0;
      one->y = 0;
      two->x = 0;
      two->y = 0;
      three->x = 0;
      three->y = 0;
      four->x = 0;
      four->y = 0;
      five->x = 0;
      five->y = 0;
      six->x = 0;
      six->y = 0;
      seven->x = 0;
      seven->y = 0;
      eight->x = 0;
      eight->y = 0;
      nine->x = 0;
      nine->y = 0;

    }
  }

  else {
    humidity_and_temperature->hover = false;
    read_humidity->hover = false;
    read_sound_intensity->hover = false;
    read_temperature->hover = false;
    sound_int->hover = false;
  }

  packet_number = 0;
  draw_page();
  }
}

/*!
 * @brief Handles mouse input for the security camera section.
 * @ingroup Mouse_Handler Mouse_Handler
 * This function processes mouse packets and updates the mouse packet structure.
 */
void mouse_security_camera_handler () {
  mouse_ih();
  parse_bytes_to_packet();
}

/*!
 * @brief Handles mouse input for the settings menu.
 * @ingroup Mouse_Handler Mouse_Handler
 * This function processes mouse packets, updates the cursor position, and checks for button hovers and clicks.
 */
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

/**
 * @brief Interrupt Handler of the help page
 * @ingroup Mouse_Handler Mouse_Handler
 */
void mouse_help_handler () {
  mouse_ih();
  if (packet_number == 3) {
    parse_bytes_to_packet();

    normalCursor->x = mouse_packet.x;
    normalCursor->y = mouse_packet.y;

  
    if (mouse_packet.x >= backArrow->x && mouse_packet.x <= backArrow->x + bigResolutionButton->width && mouse_packet.y >= backArrow->y && mouse_packet.y <= backArrow->y + backArrow->height)  {
      if (mouse_packet.left_button) page_state = MAIN_MENU;
    }

    packet_number = 0;
    draw_page();
  }
}



