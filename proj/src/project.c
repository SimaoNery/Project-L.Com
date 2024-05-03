#include "project.h"

uint8_t irq_timer, irq_keyboard, irq_mouse;

int (project_start)() {
    //setup video buffers
    if(map_frame_buffers(VBE_MODE_SET) != 0) {
        printf("Error: Problems occured while trying to map video memory! \n");
        return 1;
    }

    //set graphics to video mode
    if(vg_set_graphics_mode(VBE_MODE_SET) != 0) {
        printf("Error: Problems occured while trying to change graphics to video mode! \n");
        return 1;
    }

    //Subscribe interrupts
    if(timer_subscribe_int(&irq_timer) != 0) {
        printf("Error: Problems occured while trying to subscribe timer interrupts! \n");
        return 1;
    }

    if(kbc_subscribe_int(&irq_keyboard) != 0) {
        printf("Error: Problems occured while trying to subscribe keyboard interrupts! \n");
        return 1;
    }

    if(mouse_subscribe_int(&irq_mouse) != 0) {
        printf("Error: Problems occured while trying to subscribe mouse interrupts! \n");
        return 1;
    }
    
    //set timer 0 frequency so we get better movement to do hovers and transitions
    if(timer_set_frequency(0, 60) != 0) {
        printf("Error: Problems occured while trying to set timer 0 frequency! \n");
        return 1;
    }

    //load sprites
    if(load_sprites() != 0) {
        printf("Error: Problems occured while loading project sprites! \n");
        return 1;
    }

    return 0;
}

int (project_loop)() {

}

int (project_stop)() {

}

int (draw_manager)() {
    
}

int (draw_main_menu)() {

}

int (draw_house_plant)() {

}

int (draw_security_camera)() {

}

int (draw_display_message)() {

}

int (draw_help)() {

}