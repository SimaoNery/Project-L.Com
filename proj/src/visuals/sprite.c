#include "sprite.h"

Sprite* (create_sprite)(xpm_map_t pic, int x, int y) {
    //allocate space for the object
    Sprite *sp = (Sprite *) malloc (sizeof(Sprite));    
    if(sp == NULL) return NULL;

    xpm_image_t img;

    //read the sprite pixmap
    sp->map = (uint32_t*)xpm_load(pic, XPM_8_8_8_8, &img);

    if(sp->map == NULL) {
        free(sp);          
        return NULL;
    }

    sp->width = img.width;
    sp->height = img.height;
    sp->x = x;
    sp->y = y;
    
    return sp;
}

int (destroy_sprite)(Sprite *sp) {
    if(sp == NULL) return 1;

    if(sp->map) free(sp->map);
    free(sp);
    sp = NULL;

    return 0;
}

int (destroy_all_sprites)() {
    /*if(destroy_sprite(normalCursor) != 0) {
        printf("Error: problems occured while truing to destroy -normalCursor- sprite! \n");
        return 1;
    }

    if(destroy_sprite(clickCursor) != 0) {
        printf("Error: problems occured while trying to destroy -clickCursor- sprite! \n");
        return 1;
    }*/

    if(destroy_sprite(controlShellButton) != 0) {
        printf("Error: problems occured while trying to destroy -controlShellButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(housePlantButton) != 0) {
        printf("Error: problems occured while trying to destroy -housePlantButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(securityCameraButton) != 0) {
        printf("Error: problems occured while trying to destroy -securityCameraButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(displayMessageButton) != 0) {
        printf("Error: problems occured while trying to destroy -displayMessageButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(helpButton) != 0) {
        printf("Error: problems occured while trying to destroy -helpButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(settingsButton) != 0) {
        printf("Error: problems occured while trying to destroy -settingsButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(mainMenu) != 0) {
        printf("Error: problems occured while trying to destroy -MainMenu- sprite! \n");
        return 1;
    }

    return 0;
}

int (draw_sprite)(Sprite *sp) {
    if(sp == NULL) return 1;

    for(int i = 0; i < sp->width; i++) {
        for(int j = 0; j < sp->height; j++) {
            uint32_t color = sp->map[sp->width * j + i];
            if(color == xpm_transparency_color(XPM_8_8_8_8)) continue;

            vg_draw_pixel(sp->x + i, sp->y + j, color);
        }
    }

    return 0;
}

int (load_sprites_1152x864)() {
    /*normalCursor = create_sprite();
    if(normalCursor == NULL) {
        printf("Error: Problems occured while trying to load -normalCursor- sprite! \n");
        return 1;
    }

    clickCursor = create_sprite();
     if(clickCursor == NULL) {
        printf("Error: Problems occured while trying to load -clickCursor- sprite! \n");
        return 1;
    }*/

    controlShellButton = create_sprite((xpm_map_t)control_shell_1152_864_xpm, 112, 332);
     if(controlShellButton == NULL) {
        printf("Error: Problems occured while trying to load -controlShellButton- sprite! \n");
        return 1;
    }

    housePlantButton = create_sprite((xpm_map_t)house_plant_1152_864_xpm, 112, 660);
     if(housePlantButton == NULL) {
        printf("Error: Problems occured while trying to load -housePlantButton- sprite! \n");
        return 1;
    }

    securityCameraButton = create_sprite((xpm_map_t) security_camera_1152_864_xpm, 112, 496);
     if(securityCameraButton == NULL) {
        printf("Error: Problems occured while trying to load -securityCameraButton- sprite! \n");
        return 1;
    }

    displayMessageButton = create_sprite((xpm_map_t) display_message_1152_864_xpm, 656, 332);
     if(displayMessageButton == NULL) {
        printf("Error: Problems occured while trying to load -displayMessageButton- sprite! \n");
        return 1;
    }

    helpButton = create_sprite((xpm_map_t) help_1152_864_xpm, 656, 660);
     if(helpButton == NULL) {
        printf("Error: Problems occured while trying to load -helpButton- sprite! \n");
        return 1;
    }

    settingsButton = create_sprite((xpm_map_t) settings_1152_864_xpm, 656, 496);
     if(helpButton == NULL) {
        printf("Error: Problems occured while trying to load -settingsButton- sprite! \n");
        return 1;
    }

    mainMenu = create_sprite((xpm_map_t)main_menu_1152_864_xpm, 0, 0);
    if(mainMenu == NULL) {
        printf("Error: Problems occured while trying to load -mainMenu- sprite! \n");
        return 1;
    }

    return 0;
}

int (load_sprites_800x600)() {
    /*normalCursor = create_sprite();
    if(normalCursor == NULL) {
        printf("Error: Problems occured while trying to load -normalCursor- sprite! \n");
        return 1;
    }

    clickCursor = create_sprite();
     if(clickCursor == NULL) {
        printf("Error: Problems occured while trying to load -clickCursor- sprite! \n");
        return 1;
    }*/

    controlShellButton = create_sprite((xpm_map_t)control_shell_button_800_600_xpm, 78, 231);
     if(controlShellButton == NULL) {
        printf("Error: Problems occured while trying to load -controlShellText- sprite! \n");
        return 1;
    }

     housePlantButton = create_sprite((xpm_map_t)house_plant_button_800_600_xpm, 78, 458);
     if(housePlantButton == NULL) {
        printf("Error: Problems occured while trying to load -housePlantText- sprite! \n");
        return 1;
    }

    securityCameraButton = create_sprite((xpm_map_t) security_camera_button_800_600_xpm, 78, 344);
    if(securityCameraButton == NULL) {
        printf("Error: Problems occured while trying to load -securityCameraText- sprite! \n");
        return 1;
    }

    displayMessageButton = create_sprite((xpm_map_t) display_message_button_800_600_xpm, 456, 231);
     if(displayMessageButton == NULL) {
        printf("Error: Problems occured while trying to load -displayMessageText- sprite! \n");
        return 1;
    }

    helpButton = create_sprite((xpm_map_t) help_800_600_xpm, 456, 458);
     if(helpButton == NULL) {
        printf("Error: Problems occured while trying to load -helpText- sprite! \n");
        return 1;
    }

    settingsButton = create_sprite((xpm_map_t) settings_800_600_xpm, 456, 344);
     if(settingsButton == NULL) {
        printf("Error: Problems occured while trying to load -helpText- sprite! \n");
        return 1;
    }

    mainMenu = create_sprite((xpm_map_t)main_menu_800_600_xpm, 0, 0);
    if(mainMenu == NULL) {
        printf("Main Menu is null \n");
        return 1;
    }    

    return 0;
}
