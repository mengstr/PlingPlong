/* 
 * File:   touch.h
 * Author: Mats
 *
 * Created on October 29, 2013, 11:35 PM
 */

#ifndef TOUCH_H
#define	TOUCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PADS    24

#include <stdint.h>         // uint8_t definitions

void SetupCTMU(void);
uint16_t ReadPad(uint8_t no);
void CalibratePads(void);
int16_t GetPadBaseValue(uint8_t no);

#ifdef	__cplusplus
}
#endif

#endif	/* TOUCH_H */

