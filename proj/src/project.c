#include "project.h"

struct handler
{
  void (*handler)();
};

static const handler_t timer_handler[] = {
    {timer_main_menu_handler},
    {timer_control_shell_handler},
    {timer_house_plant_handler},
    {timer_security_camera_handler},
    {timer_display_message_handler},
    {timer_settings_handler},
    {timer_help_handler}
};

static const handler_t keyboard_handler[] = {
    {keyboard_main_menu_handler},
    {keyboard_control_shell_handler},
    {keyboard_house_plant_handler},
    {keyboard_security_camera_handler},
    {keyboard_display_message_handler},
    {keyboard_settings_handler},
    {keyboard_help_handler}
};

static const handler_t mouse_handler[] = {
    {mouse_main_menu_handler},
    {mouse_control_shell_handler},
    {mouse_house_plant_handler},
    {mouse_security_camera_handler},
    {mouse_display_message_handler},
    {mouse_settings_handler},
    {mouse_help_handler}
};

static const handler_t real_time_clock_handler[] = {
    {real_time_clock_main_menu_handler},
    {real_time_clock_control_shell_handler},
    {real_time_clock_house_plant_handler},
    {real_time_clock_security_camera_handler},
    {real_time_clock_display_message_handler},
    {real_time_clock_settings_handler},
    {real_time_clock_help_handler}
};

/*static const handler_t serial_port_handler[] = {
    {serial_port_main_menu_handler},
    {serial_port_house_plant_handler},
    {serial_port_security_camera_handler},
    {serial_port_display_message_handler},
    {serial_port_settings_handler},
    {serial_port_help_handler}
};*/

uint8_t irq_timer, irq_keyboard, irq_mouse, irq_real_time_clock; //irq_serial_port;
uint16_t resolution = RES_1152_864;
bool running = true;
uint8_t page_state = MAIN_MENU;


int (project_start)() {

    if(map_frame_buffer(resolution) != 0) {
        printf("Error: A problem occured while trying to map video memory! \n");
        return 1;
    }

    if(vg_set_graphics_mode(resolution) != 0) {
        printf("Error: A problem occured while trying to change graphics to video mode! \n");
        return 1;
    }

    if(load_sprites_1152x864() != 0) {
        printf("Error: A problem occured while loading project sprites! \n");
        return 1;
    }

    if(timer_subscribe_int(&irq_timer) != 0) {
        printf("Error: A problem occured while trying to subscribe timer interrupts! \n");
        return 1;
    }

    if(kbc_subscribe_int(&irq_keyboard) != 0) {
        printf("Error: A problem occured while trying to subscribe keyboard interrupts! \n");
        return 1;
    }

    if(mouse_subscribe_int(&irq_mouse) != 0) {
        printf("Error: A problem occured while trying to subscribe mouse interrupts! \n");
        return 1;
    }

    if(rtc_subscribe_int(&irq_real_time_clock) != 0) {
        printf("Error: A problem occured while trying to subscribe real time clock interrupts! \n");
        return 1;
    }

    /*
    if(sp_subscribe_int(&irq_serial_port) != 0) {
        printf("Error: A problem occured while trying to subscribe serial port interrupts! \n");
        return 1;
    }
    */

    if(timer_set_frequency(0, 60) != 0) {
        printf("Error: A problem occured while trying to set timer 0 frequency! \n");
        return 1;
    }

    return 0;
}

int (project_loop)() {

  if(draw_page() != 0) {
    printf("Error: Problems occured while trying to draw the main menu! \n");
    return 1;
  }

  int ipc_status;
  message msg;
  
  while (running) {
    if( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
      printf("Error");
      continue;
    }

    if(is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_timer) {

            timer_handler[page_state].handler();
          }

          if (msg.m_notify.interrupts & irq_keyboard) {
            keyboard_handler[page_state].handler();
          }

          if (msg.m_notify.interrupts & irq_mouse) {
            mouse_handler[page_state].handler();
          }

          if (msg.m_notify.interrupts & irq_real_time_clock) {
            real_time_clock_handler[page_state].handler();
          }

          /*  
          if (msg.m_notify.interrupts & irq_serial_port) {
            serial_port_handler[page_state].handler(serial_port_handler);
          }
          */
         
        break;
      default:
        break;
      }
    }  
  }

  return 0;
}

int (project_stop)() {

    if(timer_unsubscribe_int() != 0) {
        printf("Error: A problem occured while trying to unsubscribe timer interrupts! \n");
        return 1;
    }

    if(kbc_unsubscribe_int() != 0) {
        printf("Error: A problem occured while trying to unsubcribe keyboard interrupts! \n");
        return 1;
    }

    if(mouse_unsubscribe_int() != 0) {
        printf("Error: A problem occured while trying to unsubscribe mouse interrupts! \n");
        return 1;
    }

    if(rtc_unsubscribe_int() != 0) {
        printf("Error: A problem occured while trying to unsubscribe real time clock interrupts! \n");
        return 1;
    }

    /*
    if(sp_unsubscribe_int() != 0) {
        printf("Error: A problem occured while trying to unsubscribe serial port interrupts! \n");
        return 1;
    }
    */

    if(vg_exit() != 0) {
        printf("Error: A problem occured while trying to go back to text mode! \n");
        return 1;
    }

    if(destroy_all_sprites() != 0) {
        printf("Error: A problem occured while destroying all sprites! \n");
        return 1;
    }

    return 0;
}
