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
        printf("Error: problems occured while truing to destroy -clickCursor- sprite! \n");
        return 1;
    }*/

    if(destroy_sprite(wagnerzim) != 0) {
        printf("Error: problems occured while truing to destroy -wagnerzim- sprite! \n");
        return 1;
    }

    if(destroy_sprite(titleText) != 0) {
        printf("Error: problems occured while truing to destroy -titleText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(controlShellText) != 0) {
        printf("Error: problems occured while truing to destroy -controlShellText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(housePlantText) != 0) {
        printf("Error: problems occured while truing to destroy -housePlantText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(securityCameraText) != 0) {
        printf("Error: problems occured while truing to destroy -securityCameraText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(displayMessageText) != 0) {
        printf("Error: problems occured while truing to destroy -displayMessageText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(helpText) != 0) {
        printf("Error: problems occured while truing to destroy -helpText- sprite! \n");
        return 1;
    }

    if(destroy_sprite(numberZero) != 0) {
        printf("Error: problems occured while truing to destroy -numberZero- sprite! \n");
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

int (load_sprites)() {
    int initial_margin = 10;
    int buttons_margin = vmi_p.YResolution / 20;

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

    wagnerzim = create_sprite((xpm_map_t)XPM_Wagnerzim, (initial_margin), initial_margin);
    if(wagnerzim== NULL) {
        printf("Error: Problems occured while trying to load -wagnerzim- sprite! \n");
        return 1;
    }

    titleText = create_sprite((xpm_map_t)XPM_TitleText, (vmi_p.XResolution / 5 + 35), initial_margin);
    if(titleText == NULL) {
        printf("Error: Problems occured while trying to load -titleText- sprite! \n");
        return 1;
    }

    controlShellText = create_sprite((xpm_map_t)XPM_ControlShellButton, (vmi_p.XResolution / 3), (initial_margin + titleText->height + buttons_margin));
     if(controlShellText == NULL) {
        printf("Error: Problems occured while trying to load -controlShellText- sprite! \n");
        return 1;
    }

    housePlantText = create_sprite((xpm_map_t)XPM_HousePlantButton, (vmi_p.XResolution / 3), (initial_margin + 2*titleText->height + 2*buttons_margin));
     if(housePlantText == NULL) {
        printf("Error: Problems occured while trying to load -housePlantText- sprite! \n");
        return 1;
    }

    securityCameraText = create_sprite((xpm_map_t) XPM_SecurityCameraButton, (vmi_p.XResolution / 3), (initial_margin + 3*titleText->height + 3*buttons_margin));
     if(securityCameraText == NULL) {
        printf("Error: Problems occured while trying to load -securityCameraText- sprite! \n");
        return 1;
    }

    displayMessageText = create_sprite((xpm_map_t) XPM_DisplayMessageButton, (vmi_p.XResolution / 3), (initial_margin + 4*titleText->height + 4*buttons_margin));
     if(displayMessageText == NULL) {
        printf("Error: Problems occured while trying to load -displayMessageText- sprite! \n");
        return 1;
    }

    helpText = create_sprite((xpm_map_t) XPM_HelpButton, (vmi_p.XResolution / 3), (initial_margin + 5*titleText->height + 5*buttons_margin));
     if(helpText == NULL) {
        printf("Error: Problems occured while trying to load -helpText- sprite! \n");
        return 1;
    }

    numberZero = create_sprite((xpm_map_t) XPM_Zero, (25), (initial_margin + 3*titleText->height + 3*buttons_margin));
     if(helpText == NULL) {
        printf("Error: Problems occured while trying to load -helpText- sprite! \n");
        return 1;
    }

    return 0;
}

int (animate_sprite)(Sprite *sp) {
    return 0;
}
