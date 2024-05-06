// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>


#include "project.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]

  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (proj_main_loop)() {
  if(project_start() != 0) {
    printf("Error: Problems occured while trying to start the project! \n");
    return 1;
  }

  /*if(project_loop() != 0) {
    printf("Error: Problems occured while trying to run the project! \n");
    return 1;
  }*/

  if(draw_main_menu() != 0) {
    printf("Error: Problems occured while trying to draw the main menu! \n");
    return 1;
  }

  sleep(10);
  

  if(project_stop() != 0) {
    printf("Error: Problems occured while trying to stop the project! \n");
    return 1;
  }

  printf("Success!!! \n");
  return 0;
}
