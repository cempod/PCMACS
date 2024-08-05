#include "board.h"
#include "rtos.h"
#include "FreeRTOSConfig.h"

int 
main(void) {
  board_init();

  threads_init();

  vTaskStartScheduler();
  
  while (1) {
  
  }
  
}

#if ( configCHECK_FOR_STACK_OVERFLOW > 0 )

    void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                        char * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( void ) xTask;
        ( void ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */
