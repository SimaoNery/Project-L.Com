#include "project.h"

uint8_t irq_timer, irq_keyboard, irq_mouse;
project_state state = MAIN_MENU;

int (project_start)() {
    //setup video buffer
    if(map_frame_buffer(RES_1024_768) != 0) {
        printf("Error: Problems occured while trying to map video memory! \n");
        return 1;
    }


    //set graphics to video mode
    if(vg_set_graphics_mode(RES_1024_768) != 0) {
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
    

    //set timer 0 frequency
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
   return 0;
}

int (project_stop)() {
    if(vg_exit() != 0) {
        printf("Error: Problems occured while trying to go back to text mode! \n");
        return 1;
    }

    if(timer_unsubscribe_int() != 0) {
        printf("Error: Problems occured while trying to unsubscribe timer interrupts! \n");
        return 1;
    }

    if(kbc_unsubscribe_int() != 0) {
        printf("Error: Problems occured while trying to unsubcribe keyboard interrupts! \n");
        return 1;
    }

    if(mouse_unsubscribe_int() != 0) {
        printf("Error: Problems occured while trying to unsubscribe mouse interrupts! \n");
        return 1;
    }

    if(destroy_all_sprites() != 0) {
        printf("Error: Problems occured while destroying all sprites! \n");
        return 1;
    }

    return 0;
}

int (draw_manager)() {
    switch(state) {
        case MAIN_MENU:
            draw_main_menu();
            break;
        case HOUSE_PLANT:
            draw_house_plant();
            break;
        case SECURITY_CAMERA:
            draw_security_camera();
            break;
        case DISPLAY_MESSAGE:
            draw_display_message();
            break;
        case HELP:
            draw_help();
            break;
        default:
            break;
    }

    return 0;
}

int (draw_main_menu)() {
    if(draw_sprite(titleText) != 0){
        printf("Error: Problems occured while drawing -titleText- sprite! \n");
        return 1;
    }

    /*if(draw_sprite(controlShellText) != 0){
        printf("Error: Problems occured while drawing -controlShellText- sprite! \n");
        return 1;
    }
    
    if(draw_sprite(housePlantText) != 0){
        printf("Error: Problems occured while drawing -housePlantText- sprite! \n");
        return 1;
    }
    
    if(draw_sprite(securityCameraText) != 0){
        printf("Error: Problems occured while drawing -securityCameraText- sprite! \n");
        return 1;
    }
    
    if(draw_sprite(displayMessageText) != 0){
        printf("Error: Problems occured while drawing -displayMessageText- sprite! \n");
        return 1;
    }

    if(draw_sprite(helpText) != 0) {
        printf("Error: Problems occured while drawing -helpText- sprite! \n");     
        return 1;   
    }*/

    return 0;
}

int (draw_house_plant)() {
    return 0;
}

int (draw_security_camera)() {
    return 0;
}

int (draw_display_message)() {
    return 0;
}

int (draw_help)() {
    return 0;
}
