#include "stubs_asm.h"

// Addresses for firmware task handlers (used in taskHook)


// Addresses for firmware functions


// pointed to NULL -> changed to call a "BX LR" instruction
NHSTUB(SetZoomActuatorSpeedPercent,		0xFF841798)
NHSTUB(kbd_pwr_on,						0xFF841798)
