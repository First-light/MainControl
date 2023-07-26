#ifndef ARCHERY_H_
#define ARCHERY_H_

#include "stm32f4xx.h"
#include "system_config.h"
#include "delay.h"
//#define ARCHERY_DEBUG_

#define PMPOSITIONRATIO 3.7058823529f

typedef enum
{
    PULL,
    SHOT,
    A_CHECK
}ArcheryState;

typedef struct
{
   volatile ArcheryState archery_state;
   volatile int arrow_count; 
}ArcheryController;

extern volatile ArcheryController Archery_Controller;

void ArcheryControllerInit(void);
void ArcheryControllerRun(void);





#endif