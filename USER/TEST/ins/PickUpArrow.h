#ifndef PICKUP_ARROW_H_
#define PICKUP_ARROW_H_

//#define PICKUP_ARROE_DEBUG_

typedef enum
{
    INIT,
    PICK
}PichState;

typedef struct
{
    
}PickUpArrowController;

void PickUpArrowControllerInit(void);
void PickUpArrowControllerCmd(void);
void PickUpArrowControllerDebug(void);

#endif