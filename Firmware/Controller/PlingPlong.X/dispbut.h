/* 
 * File:   dispbut.h
 * Author: Mats
 *
 * Created on October 29, 2013, 11:22 PM
 */

#ifndef DISPBUT_H
#define	DISPBUT_H

#include <stdint.h>         // uint8_t definitions

extern volatile uint8_t    disp[3];
extern volatile uint16_t   leds;
extern volatile uint16_t   keys;
extern volatile uint8_t    butt;

void RefreshDisp(void);
void DispValue(uint16_t value);

extern const uint8_t charmap[];


#endif	/* DISPBUT_H */

