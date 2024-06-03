// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>


#include "project.h"

/*!
 * @brief Main function that initializes and starts the project.
 * 
 * This function sets the language for LCF messages, enables logging and tracing if needed,
 * and hands control over to LCF to handle command line arguments and invoke the appropriate functions.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return int Returns 0 on success, 1 on failure.
 */
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]

  //lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/**
 * @brief Main loop function for the project.
 * 
 * This function starts the project, runs the main loop, and stops the project.
 * It handles any errors that occur during these phases and prints a success message upon completion.
 * 
 * @return int Returns 0 on success, 1 on failure.
 */
int (proj_main_loop)() {
  if(project_start() != 0) {
    printf("Error: Problems occured while trying to start the project! \n");
    return 1;
  }

  if(project_loop() != 0) {
    printf("Error: Problems occured while trying to run the project! \n");
  return 1;
  }

  if(project_stop() != 0) {
    printf("Error: Problems occured while trying to stop the project! \n");
    return 1;
  }

  printf("Success!!! \n");
  return 0;
}
