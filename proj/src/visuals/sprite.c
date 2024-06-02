#include "sprite.h"
/**
 * @defgroup Sprite Sprite
 * 
 */



/*!
 * @brief Creates a sprite from the given XPM map.
 * @ingroup Sprite Sprite
 * This function allocates memory for a new Sprite object, loads the XPM image,
 * and initializes the sprite's properties.
 * 
 * @param pic The XPM map to load the sprite from.
 * @param x The initial x-coordinate of the sprite.
 * @param y The initial y-coordinate of the sprite.
 * @return Sprite* Pointer to the created Sprite object, or NULL if an error occurred.
 */
Sprite* (create_sprite)(xpm_map_t pic, int x, int y) {
    Sprite *sp = (Sprite *) malloc (sizeof(Sprite));    
    if(sp == NULL) return NULL;

    xpm_image_t img;
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
/*!
 * @brief Destroys a sprite and frees its memory.
 * @ingroup Sprite Sprite
 * This function frees the memory allocated for the sprite's pixel map and the sprite itself.
 * 
 * @param sp Pointer to the Sprite object to be destroyed.
 * @return int Returns 0 on success, 1 if the sprite was NULL.
 */
int (destroy_sprite)(Sprite *sp) {
    if(sp == NULL) return 1;

    if(sp->map) free(sp->map);
    free(sp);
    sp = NULL;

    return 0;
}

/*!
 * @brief Destroys all loaded sprites.
 * @ingroup Sprite Sprite
 * This function destroys all the sprites that have been loaded and prints an error message if any sprite could not be destroyed.
 * 
 * @return int Returns 0 on success, 1 if any sprite could not be destroyed.
 */
int (destroy_all_sprites)() {
    if(destroy_sprite(normalCursor) != 0) {
        printf("Error: problems occured while truing to destroy -normalCursor- sprite! \n");
        return 1;
    }
    /*
    if(destroy_sprite(clickCursor) != 0) {
        printf("Error: problems occured while trying to destroy -clickCursor- sprite! \n");
        return 1;
    }
    */

    if(destroy_sprite(controlShellButton) != 0) {
        printf("Error: problems occured while trying to destroy -controlShellButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(housePlantButton) != 0) {
        printf("Error: problems occured while trying to destroy -housePlantButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(exitButton) != 0) {
        printf("Error: problems occured while trying to destroy -exitButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(helpButton) != 0) {
        printf("Error: problems occured while trying to destroy -helpButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(resolutionButton) != 0) {
        printf("Error: problems occured while trying to destroy -settingsButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(mainMenu) != 0) {
        printf("Error: problems occured while trying to destroy -MainMenu- sprite! \n");
        return 1;
    }

    if(destroy_sprite(resolutionPage) != 0) {
        printf("Error: problems occured while trying to destroy -resolutionPage- sprite! \n");
        return 1;
    }

    if(destroy_sprite(smallResolutionButton) != 0) {
        printf("Error: problems occured while trying to destroy -smallResolutionButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(bigResolutionButton) != 0) {
        printf("Error: problems occured while trying to destroy -bigResolutionButton- sprite! \n");
        return 1;
    }

    if(destroy_sprite(backArrow) != 0) {
        printf("Error: problems occured while trying to destroy -backArrow- sprite! \n");
        return 1;
    }

    if(destroy_sprite(housePlant) != 0) {
        printf("Error: problems occured while trying to destroy -housePlant- sprite! \n");
        return 1;
    }

    if(destroy_sprite(db) != 0) {
        printf("Error: problems occured while trying to destroy -db- sprite! \n");
        return 1;
    }

    if(destroy_sprite(degrees_celcius) != 0) {
        printf("Error: problems occured while trying to destroy -degreesCelsius- sprite! \n");
        return 1;
    }

    if(destroy_sprite(fan) != 0) {
        printf("Error: problems occured while trying to destroy -fan- sprite! \n");
        return 1;
    }

    if(destroy_sprite(horn1) != 0) {
        printf("Error: problems occured while trying to destroy -horn1- sprite! \n");
        return 1;
    }

    if(destroy_sprite(horn2) != 0) {
        printf("Error: problems occured while trying to destroy -horn2- sprite! \n");
        return 1;
    }


    if(destroy_sprite(humidity_and_temperature) != 0) {
        printf("Error: problems occured while trying to destroy -humidity_and_temperature- sprite! \n");
        return 1;
    }

    if(destroy_sprite(light_horizontal1) != 0) {
        printf("Error: problems occured while trying to destroy -light_horizontal1- sprite! \n");
        return 1;
    }

    if(destroy_sprite(light_horizontal2) != 0) {
        printf("Error: problems occured while trying to destroy -light_horizontal2- sprite! \n");
        return 1;
    }

    if(destroy_sprite(light_vertical1) != 0) {
        printf("Error: problems occured while trying to destroy -lightVertical1- sprite! \n");
        return 1;
    }


    if(destroy_sprite(light_vertical2) != 0) {
        printf("Error: problems occured while trying to destroy -lightVertical2- sprite! \n");
        return 1;
    }


    if(destroy_sprite(light_vertical3) != 0) {
        printf("Error: problems occured while trying to destroy -lightVertical3- sprite! \n");
        return 1;
    }

    if(destroy_sprite(percentage) != 0) {
        printf("Error: problems occured while trying to destroy -percentage- sprite! \n");
        return 1;
    }

    if(destroy_sprite(read_humidity) != 0) {
        printf("Error: problems occured while trying to destroy -read_humidity- sprite! \n");
        return 1;
    }

    if(destroy_sprite(read_sound_intensity) != 0) {
        printf("Error: problems occured while trying to destroy -read_sound_intensity- sprite! \n");
        return 1;
    }

    if(destroy_sprite(read_temperature) != 0) {
        printf("Error: problems occured while trying to destroy -read_temperature- sprite! \n");
        return 1;
    }

    if(destroy_sprite(sound_int) != 0) {
        printf("Error: problems occured while trying to destroy -sound_int- sprite! \n");
        return 1;
    }
    
    if (destroy_sprite(colon) != 0) {
        printf("Error: problems occurred while trying to destroy -colon- sprite!\n");
        return 1;
    }

    if (destroy_sprite(slash) != 0) {
        printf("Error: problems occurred while trying to destroy -slash- sprite!\n");
        return 1;
    }

    if (destroy_sprite(zero) != 0) {
        printf("Error: problems occurred while trying to destroy -zero- sprite!\n");
        return 1;
    }

    if (destroy_sprite(one) != 0) {
        printf("Error: problems occurred while trying to destroy -one- sprite!\n");
        return 1;
    }

    if (destroy_sprite(two) != 0) {
        printf("Error: problems occurred while trying to destroy -two- sprite!\n");
        return 1;
    }

    if (destroy_sprite(three) != 0) {
        printf("Error: problems occurred while trying to destroy -three- sprite!\n");
        return 1;
    }

    if (destroy_sprite(four) != 0) {
        printf("Error: problems occurred while trying to destroy -four- sprite!\n");
        return 1;
    }

    if (destroy_sprite(five) != 0) {
        printf("Error: problems occurred while trying to destroy -five- sprite!\n");
        return 1;
    }

    if (destroy_sprite(six) != 0) {
        printf("Error: problems occurred while trying to destroy -six- sprite!\n");
        return 1;
    }

    if (destroy_sprite(seven) != 0) {
        printf("Error: problems occurred while trying to destroy -seven- sprite!\n");
        return 1;
    }

    if (destroy_sprite(eight) != 0) {
        printf("Error: problems occurred while trying to destroy -eight- sprite!\n");
        return 1;
    }

    if (destroy_sprite(nine) != 0) {
        printf("Error: problems occurred while trying to destroy -nine- sprite!\n");
        return 1;
    }

    if (destroy_sprite(helpPage) != 0) {
        printf("Error: problems occurred while trying to destroy -helpPage- sprite!\n");
        return 1;
    }


    return 0;
}

/*!
 * @brief Draws a sprite on the screen.
 * @ingroup Sprite Sprite
 * This function draws the sprite's pixels on the screen, skipping transparent pixels.
 * 
 * @param sp Pointer to the Sprite object to be drawn.
 * @return int Returns 0 on success, 1 if the sprite was NULL.
 */
int (draw_sprite)(Sprite *sp) {
    if(sp == NULL) return 1;

    for(int i = 0; i < sp->width; i++) {
        for(int j = 0; j < sp->height; j++) {
            uint32_t color = sp->map[sp->width * j + i];
            if(color == TRANSPARENT_COLOR) continue;
            else if (color == 0xFFFFFF && sp->hover) color = 0xFDED84;

            vg_draw_pixel(sp->x + i, sp->y + j, color);
        }
    }

    return 0;
}

/*!
 * @brief Loads sprites for the 1152x864 resolution.
 * @ingroup Sprite Sprite
 * This function creates and initializes all the sprites needed for the 1152x864 resolution.
 * 
 * @return int Returns 0 on success, 1 if any sprite could not be loaded.
 */
int (load_sprites_1152x864)() {
    normalCursor = create_sprite((xpm_map_t)mouse_pointer_1152_864_xpm, 100, 100);
    if(normalCursor == NULL) {
        printf("Error: Problems occured while trying to load -normalCursor- sprite! \n");
        return 1;
    }
    /*
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

    housePlantButton = create_sprite((xpm_map_t)house_plant_button_1152_864_xpm, 112, 496);
     if(housePlantButton == NULL) {
        printf("Error: Problems occured while trying to load -housePlantButton- sprite! \n");
        return 1;
    }

    exitButton = create_sprite((xpm_map_t) exit_button_1152_864_xpm, 383, 660);
     if(exitButton == NULL) {
        printf("Error: Problems occured while trying to load -exitButton- sprite! \n");
        return 1;
    }

    helpButton = create_sprite((xpm_map_t) help_1152_864_xpm, 656, 496);
     if(helpButton == NULL) {
        printf("Error: Problems occured while trying to load -helpButton- sprite! \n");
        return 1;
    }

    resolutionButton = create_sprite((xpm_map_t) resolution_button_1152_864_xpm, 656, 332);
     if(resolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -settingsButton- sprite! \n");
        return 1;
    }

    mainMenu = create_sprite((xpm_map_t)main_menu_1152_864_xpm, 0, 0);
    if(mainMenu == NULL) {
        printf("Error: Problems occured while trying to load -mainMenu- sprite! \n");
        return 1;
    }

    resolutionPage = create_sprite((xpm_map_t)resolution_page_1152_864_xpm, 0, 0);
    if(resolutionPage == NULL) {
        printf("Error: Problems occured while trying to load -resolutionPage- sprite! \n");
        return 1;
    }

    smallResolutionButton = create_sprite((xpm_map_t)small_resolution_button_1152_864_xpm, 108, 432);
    if(smallResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -smallResolutionButton- sprite! \n");
        return 1;
    }

    bigResolutionButton = create_sprite((xpm_map_t)big_resolution_button_1152_864_xpm, 656, 432);
    if(bigResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -bigResolutionButton- sprite! \n");
        return 1;
    }

    backArrow = create_sprite((xpm_map_t)back_arrow_1152_864_xpm, 35, 35);
    if(bigResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -backArrow- sprite! \n");
        return 1;
    }

    housePlant = create_sprite((xpm_map_t)house_plant_1152_864_xpm, 0, 0);
    if(housePlant == NULL) {
        printf("Error: Problems occured while trying to load -housePlant- sprite! \n");
        return 1;
    }

    db = create_sprite((xpm_map_t)db_1152_864_xpm, 0, 0);
    if(db == NULL) {
        printf("Error: Problems occured while trying to load -db- sprite! \n");
        return 1;
    }

    degrees_celcius = create_sprite((xpm_map_t)degrees_celsius_1152_864_xpm, 0, 0);
    if(degrees_celcius == NULL) {
        printf("Error: Problems occured while trying to load -degreeCelsius- sprite! \n");
        return 1;
    }

    fan = create_sprite((xpm_map_t)fan_1152_864_xpm, 212, 429);
    if(fan == NULL) {
        printf("Error: Problems occured while trying to load -fan- sprite! \n");
        return 1;
    }   

    horn1 = create_sprite((xpm_map_t)horn_1152_864_xpm, 577, 647);
    if(horn1 == NULL) {
        printf("Error: Problems occured while trying to load -horn1- sprite! \n");
        return 1;
    }

    horn2 = create_sprite((xpm_map_t)horn_1152_864_xpm, 637, 647);
    if(horn2 == NULL) {
        printf("Error: Problems occured while trying to load -horn2- sprite! \n");
        return 1;
    }    

    humidity_and_temperature = create_sprite((xpm_map_t)humidity_and_temperature_1152_864_xpm, 216, 390);
    if(humidity_and_temperature == NULL) {
        printf("Error: Problems occured while trying to load -humidity_and_temperature- sprite! \n");
        return 1;
    }

    light_horizontal1 = create_sprite((xpm_map_t)light_1152_864_xpm, 193, 264);
    if(light_horizontal1 == NULL) {
        printf("Error: Problems occured while trying to load -lightHorizontal1- sprite! \n");
        return 1;
    }

    light_horizontal2 = create_sprite((xpm_map_t)light_1152_864_xpm, 430, 264);
    if(light_horizontal2 == NULL) {
        printf("Error: Problems occured while trying to load -lightHorizontal2- sprite! \n");
        return 1;
    }

    light_vertical1 = create_sprite((xpm_map_t)light_vertical_1152_864_xpm, 120, 569);
    if(light_vertical1 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical1- sprite! \n");
        return 1;
    }

    light_vertical2 = create_sprite((xpm_map_t)light_vertical_1152_864_xpm, 361, 569);
    if(light_vertical2 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical2- sprite! \n");
        return 1;
    }

    light_vertical3 = create_sprite((xpm_map_t)light_vertical_1152_864_xpm, 675, 367);
    if(light_vertical3 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical3- sprite! \n");
        return 1;
    }        

    percentage = create_sprite((xpm_map_t)percentage_1152_864_xpm, 0, 0);
    if(percentage == NULL) {
        printf("Error: Problems occured while trying to load -percentage- sprite! \n");
        return 1;
    }

    read_humidity = create_sprite((xpm_map_t)read_humidity_button_1152_864_xpm, 851, 379);
    if(read_humidity == NULL) {
        printf("Error: Problems occured while trying to load -readHumidity- sprite! \n");
        return 1;
    }

    read_sound_intensity = create_sprite((xpm_map_t)read_sound_intensity_1152_864_xpm, 855, 679);
    if(read_sound_intensity == NULL) {
        printf("Error: Problems occured while trying to load -read_sound_intensity- sprite! \n");
        return 1;
    }

    read_temperature = create_sprite((xpm_map_t)read_temperature_1152_864_xpm, 851, 529);
    if(read_temperature== NULL) {
        printf("Error: Problems occured while trying to load -read_temperature- sprite! \n");
        return 1;
    }

    sound_int= create_sprite((xpm_map_t)sound_intensity_1152_864_xpm, 242, 427);
    if(sound_int == NULL) {
        printf("Error: Problems occured while trying to load -sound_int- sprite! \n");
        return 1;
    }

    colon = create_sprite((xpm_map_t)colon_1152_864_xpm, 0, 0);
    if(colon == NULL) {
        printf("Error: Problems occured while trying to load -colon- sprite! \n");
        return 1;
    }

    slash = create_sprite((xpm_map_t)slash_1152_864_xpm, 0, 0);
    if (slash == NULL) {
        printf("Error: Problems occurred while trying to load -slash- sprite!\n");
        return 1;
    }

    zero = create_sprite((xpm_map_t)zero_1152_864_xpm, 0, 0);
    if (zero == NULL) {
        printf("Error: Problems occurred while trying to load -zero- sprite!\n");
        return 1;
    }

    one = create_sprite((xpm_map_t)one_1152_864_xpm, 0, 0);
    if (one == NULL) {
        printf("Error: Problems occurred while trying to load -one- sprite!\n");
        return 1;
    }

    two = create_sprite((xpm_map_t)two_1152_864_xpm, 0, 0);
    if (two == NULL) {
        printf("Error: Problems occurred while trying to load -two- sprite!\n");
        return 1;
    }

    three = create_sprite((xpm_map_t)three_1152_864_xpm, 0, 0);
    if (three == NULL) {
        printf("Error: Problems occurred while trying to load -three- sprite!\n");
        return 1;
    }

    four = create_sprite((xpm_map_t)four_1152_864_xpm, 0, 0);
    if (four == NULL) {
        printf("Error: Problems occurred while trying to load -four- sprite!\n");
        return 1;
    }

    five = create_sprite((xpm_map_t)five_1152_864_xpm, 0, 0);
    if (five == NULL) {
        printf("Error: Problems occurred while trying to load -five- sprite!\n");
        return 1;
    }

    six = create_sprite((xpm_map_t)six_1152_864_xpm, 0, 0);
    if (six == NULL) {
        printf("Error: Problems occurred while trying to load -six- sprite!\n");
        return 1;
    }

    seven = create_sprite((xpm_map_t)seven_1152_864_xpm, 0, 0);
    if (seven == NULL) {
        printf("Error: Problems occurred while trying to load -seven- sprite!\n");
        return 1;
    }

    eight = create_sprite((xpm_map_t)eight_1152_864_xpm, 0, 0);
    if (eight == NULL) {
        printf("Error: Problems occurred while trying to load -eight- sprite!\n");
        return 1;
    }

    nine = create_sprite((xpm_map_t)nine_1152_864_xpm, 0, 0);
    if (nine == NULL) {
        printf("Error: Problems occurred while trying to load -nine- sprite!\n");
        return 1;
    }

    helpPage = create_sprite((xpm_map_t)help_page_1152_864_xpm, 0, 0);
    if (helpPage == NULL) {
        printf("Error: Problems occurred while trying to load -helpPage- sprite!\n");
        return 1;
    }

    return 0;
}

/*!
 * @brief Loads sprites for the 800x600 resolution.
 * @ingroup Sprite Sprite
 * This function creates and initializes all the sprites needed for the 800x600 resolution.
 * 
 * @return int Returns 0 on success, 1 if any sprite could not be loaded.
 */
int (load_sprites_800x600)() {
    normalCursor = create_sprite((xpm_map_t)mouse_pointer_800_600_xpm, 0, 0);
    if(normalCursor == NULL) {
        printf("Error: Problems occured while trying to load -normalCursor- sprite! \n");
        return 1;
    }

    /*clickCursor = create_sprite();
     if(clickCursor == NULL) {
        printf("Error: Problems occured while trying to load -clickCursor- sprite! \n");
        return 1;
    }*/

    controlShellButton = create_sprite((xpm_map_t)control_shell_button_800_600_xpm, 78, 231);
     if(controlShellButton == NULL) {
        printf("Error: Problems occured while trying to load -controlShellText- sprite! \n");
        return 1;
    }

     housePlantButton = create_sprite((xpm_map_t)house_plant_button_800_600_xpm, 78, 344);
     if(housePlantButton == NULL) {
        printf("Error: Problems occured while trying to load -housePlantText- sprite! \n");
        return 1;
    }

    exitButton = create_sprite((xpm_map_t) exit_button_800_600_xpm, 266, 458);
     if(exitButton == NULL) {
        printf("Error: Problems occured while trying to load -exitButton- sprite! \n");
        return 1;
    }

    helpButton = create_sprite((xpm_map_t) help_800_600_xpm, 456, 344);
     if(helpButton == NULL) {
        printf("Error: Problems occured while trying to load -helpText- sprite! \n");
        return 1;
    }

    resolutionButton = create_sprite((xpm_map_t) resolution_button_800_600_xpm, 456, 231); 
     if(resolutionButton == NULL) { 
        printf("Error: Problems occured while trying to load -resolutionButton- sprite! \n");
        return 1;
    }

    mainMenu = create_sprite((xpm_map_t)main_menu_800_600_xpm, 0, 0);
    if(mainMenu == NULL) {
        printf("Error: Problems occured while trying to load -mainMenu- sprite! \n");
        return 1;
    }    

    resolutionPage = create_sprite((xpm_map_t)resolution_page_800_600_xpm, 0, 0);
    if(resolutionPage == NULL) {
        printf("Error: Problems occured while trying to load -resolutionPage- sprite! \n");
        return 1;
    }

    smallResolutionButton = create_sprite((xpm_map_t)small_resolution_button_800_600_xpm, 78, 314);
    if(smallResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -smallResolutionButton- sprite! \n");
        return 1;
    }


    bigResolutionButton = create_sprite((xpm_map_t)big_resolution_button_800_600_xpm, 456, 314);
    if(bigResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -bigResolutionButton- sprite! \n");
        return 1;
    }

    backArrow = create_sprite((xpm_map_t)back_arrow_800_600_xpm, 10, 10);
    if(bigResolutionButton == NULL) {
        printf("Error: Problems occured while trying to load -backArrow- sprite! \n");
        return 1;
    }

    housePlant = create_sprite((xpm_map_t)house_plant_800_600_xpm, 0, 0);
    if(housePlant == NULL) {
        printf("Error: Problems occured while trying to load -housePlant- sprite! \n");
        return 1;
    }

    db = create_sprite((xpm_map_t)db_800_600_xpm, 0, 0);
    if(db == NULL) {
        printf("Error: Problems occured while trying to load -db- sprite! \n");
        return 1;
    }

    degrees_celcius = create_sprite((xpm_map_t)degrees_celsius_800_600_xpm, 0, 0);
    if(degrees_celcius == NULL) {
        printf("Error: Problems occured while trying to load -degreeCelsius- sprite! \n");
        return 1;
    }

    fan = create_sprite((xpm_map_t)fan_800_600_xpm, 149, 298);
    if(fan == NULL) {
        printf("Error: Problems occured while trying to load -fan- sprite! \n");
        return 1;
    }

    horn1 = create_sprite((xpm_map_t)horn_800_600_xpm, 400, 450);
    if(horn1 == NULL) {
        printf("Error: Problems occured while trying to load -horn1- sprite! \n");
        return 1;
    }

    horn2 = create_sprite((xpm_map_t)horn_800_600_xpm, 442, 450);
    if(horn2 == NULL) {
        printf("Error: Problems occured while trying to load -horn2- sprite! \n");
        return 1;
    }    

    humidity_and_temperature = create_sprite((xpm_map_t)humidity_and_temperature_800_600_xpm, 150, 270);
    if(humidity_and_temperature == NULL) {
        printf("Error: Problems occured while trying to load -humidity_and_temperature- sprite! \n");
        return 1;
    }

    light_horizontal1 = create_sprite((xpm_map_t)light_800_600_xpm, 134, 183);
    if(light_horizontal1 == NULL) {
        printf("Error: Problems occured while trying to load -lightHorizontal1- sprite! \n");
        return 1;
    }

    light_horizontal2 = create_sprite((xpm_map_t)light_800_600_xpm, 290, 183);
    if(light_horizontal2 == NULL) {
        printf("Error: Problems occured while trying to load -lightHorizontal2- sprite! \n");
        return 1;
    }

    light_vertical1 = create_sprite((xpm_map_t)light_vertical_800_600_xpm, 84, 395);
    if(light_vertical1 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical1- sprite! \n");
        return 1;
    }

    light_vertical2 = create_sprite((xpm_map_t)light_vertical_800_600_xpm, 225, 395);
    if(light_vertical2 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical2- sprite! \n");
        return 1;
    }

    light_vertical3 = create_sprite((xpm_map_t)light_vertical_800_600_xpm, 468, 255);
    if(light_vertical3 == NULL) {
        printf("Error: Problems occured while trying to load -lightVertical3- sprite! \n");
        return 1;
    }        

    percentage = create_sprite((xpm_map_t)percentage_800_600_xpm, 0, 0);
    if(percentage == NULL) {
        printf("Error: Problems occured while trying to load -percentage- sprite! \n");
        return 1;
    }

    read_humidity = create_sprite((xpm_map_t)read_humidity_button_800_600_xpm, 584, 245);
    if(read_humidity == NULL) {
        printf("Error: Problems occured while trying to load -readHumidity- sprite! \n");
        return 1;
    }

    read_sound_intensity = create_sprite((xpm_map_t)read_sound_intensity_800_600_xpm, 550, 470);
    if(read_sound_intensity == NULL) {
        printf("Error: Problems occured while trying to load -read_sound_intensity- sprite! \n");
        return 1;
    }

    read_temperature = create_sprite((xpm_map_t)read_temperature_800_600_xpm, 584, 357);
    if(read_temperature== NULL) {
        printf("Error: Problems occured while trying to load -read_temperature- sprite! \n");
        return 1;
    }

    sound_int = create_sprite((xpm_map_t)sound_intensity_800_600_xpm, 170, 299);
    if(sound_int == NULL) {
        printf("Error: Problems occured while trying to load -sound_int- sprite! \n");
        return 1;
    }

    colon = create_sprite((xpm_map_t)colon_800_600_xpm, 0, 0);
    if(colon == NULL) {
        printf("Error: Problems occured while trying to load -colon- sprite! \n");
        return 1;
    }

    slash = create_sprite((xpm_map_t)slash_800_600_xpm, 0, 0);
    if (slash == NULL) {
        printf("Error: Problems occurred while trying to load -slash- sprite!\n");
        return 1;
    }

    zero = create_sprite((xpm_map_t)zero_800_600_xpm, 0, 0);
    if (zero == NULL) {
        printf("Error: Problems occurred while trying to load -zero- sprite!\n");
        return 1;
    }

    one = create_sprite((xpm_map_t)one_800_600_xpm, 0, 0);
    if (one == NULL) {
        printf("Error: Problems occurred while trying to load -one- sprite!\n");
        return 1;
    }

    two = create_sprite((xpm_map_t)two_800_600_xpm, 0, 0);
    if (two == NULL) {
        printf("Error: Problems occurred while trying to load -two- sprite!\n");
        return 1;
    }

    three = create_sprite((xpm_map_t)three_800_600_xpm, 0, 0);
    if (three == NULL) {
        printf("Error: Problems occurred while trying to load -three- sprite!\n");
        return 1;
    }

    four = create_sprite((xpm_map_t)four_800_600_xpm, 0, 0);
    if (four == NULL) {
        printf("Error: Problems occurred while trying to load -four- sprite!\n");
        return 1;
    }

    five = create_sprite((xpm_map_t)five_800_600_xpm, 0, 0);
    if (five == NULL) {
        printf("Error: Problems occurred while trying to load -five- sprite!\n");
        return 1;
    }

    six = create_sprite((xpm_map_t)six_800_600_xpm, 0, 0);
    if (six == NULL) {
        printf("Error: Problems occurred while trying to load -six- sprite!\n");
        return 1;
    }

    seven = create_sprite((xpm_map_t)seven_800_600_xpm, 0, 0);
    if (seven == NULL) {
        printf("Error: Problems occurred while trying to load -seven- sprite!\n");
        return 1;
    }

    eight = create_sprite((xpm_map_t)eight_800_600_xpm, 0, 0);
    if (eight == NULL) {
        printf("Error: Problems occurred while trying to load -eight- sprite!\n");
        return 1;
    }

    nine = create_sprite((xpm_map_t)nine_800_600_xpm, 0, 0);
    if (nine == NULL) {
        printf("Error: Problems occurred while trying to load -nine- sprite!\n");
        return 1;
    }

    helpPage = create_sprite((xpm_map_t)help_page_800_600_xpm, 0, 0);
    if (helpPage == NULL) {
        printf("Error: Problems occurred while trying to load -helpPage- sprite!\n");
        return 1;
    }
     
    return 0;
}

/*!     
 * @brief Loads sprites based on the specified resolution.
 * @ingroup Sprite Sprite
 * This function determines which resolution-specific sprite loading function to call based on the provided resolution.
 * It supports loading sprites for 800x600 and 1152x864 resolutions.
 * 
 * @param res The resolution identifier. It should be either `RES_800_600` or another value for 1152x864 resolution.
 * @return int Returns 0 on success, 1 if any sprite loading fails.
 */
int (load_sprites)(int res) {
    if(res == RES_800_600) {
        if(load_sprites_800x600() != 0) {
            printf("Error: Problems occured while trying to load 800x600 sprites! \n");
            return 1;
        }
    }
    else {
        if(load_sprites_1152x864() != 0) {
            printf("Error: Problems occured while trying to load 1152x864 sprites! \n");
            return 1;
        }
    }

    return 0;
}
