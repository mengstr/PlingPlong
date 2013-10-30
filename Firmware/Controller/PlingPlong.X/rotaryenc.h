#ifndef ROTARYENC_H
#define	ROTARYENC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>         /* For uint8_t definition */

//#define HALFSTEP
#define DIR_NONE 0x0    // No complete step yet.
#define DIR_CW 0x10     // Clockwise step.
#define DIR_CCW 0x20    // Anti-clockwise step.

uint8_t PollRotaryEncoder(uint8_t pin1, uint8_t pin2);

#ifdef	__cplusplus
}
#endif

#endif	/* ROTARYENC_H */

