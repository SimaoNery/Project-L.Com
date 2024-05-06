#include "draw.h"

extern 

int draw_main_menu() {
    if(draw_sprite(mainMenu) != 0) {
        printf("Error: Problems occured while trying to draw -mainMenu- sprite! \n");
        return 1;
    }

    if(draw_main_buttons() != 0) {
        printf("Error: Problems occured while trying to draw Main Menu buttons! \n");
        return 1;
    }

    return 0;
}

int draw_control_shell() {
    return 0;
}

int draw_display_message() {
    return 0;
}

int draw_security_camera() {
    return 0;
}

int draw_settings() {
    return 0;
}

int draw_house_plant() {
    return 0;
}

int draw_help() {
    return 0;
}

int draw_main_buttons() {
    if(draw_sprite(controlShellButton) != 0) {
        printf("Error: Problems occured trying to draw -controlShellButton- sprite! \n");
        return 1;
    };

    if(draw_sprite(housePlantButton) != 0) {
        printf("Error: Problems occured trying to draw -housePlantButton- sprite! \n");
        return 1;
    };

    if(draw_sprite(securityCameraButton) != 0) {
        printf("Error: Problems occured trying to draw -securityCameraButton- sprite! \n");
        return 1;
    };

    if(draw_sprite(displayMessageButton) != 0) {
        printf("Error: Problems occured trying to draw -displayMessageButton- sprite! \n");
        return 1;
    };

    if(draw_sprite(helpButton) != 0) {
        printf("Error: Problems occured trying to draw -helpButtonButton- sprite! \n");
        return 1;
    };

    if(draw_sprite(settingsButton) != 0) {
        printf("Error: Problems occured trying to draw -settingsButton- sprite! \n");
        return 1;
    };

    return 0;
}
