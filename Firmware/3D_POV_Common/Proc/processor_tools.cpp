#include "ti/devices/msp432p4xx/inc/msp.h"
#include "core_cm4.h"

// Do we be in an interrupt???? true: we do; false: we do not
bool interruptActive()
{
    if(SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk)
    {
        return true;
    }
    else
    {
        return false;
    }
}
