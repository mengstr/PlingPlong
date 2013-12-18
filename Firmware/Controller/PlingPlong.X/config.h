/* 
 * File:   config.h
 * Author: Mats
 *
 * Created on October 29, 2013, 11:48 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define  testbit(var, bit)   ((var) & (1UL <<(bit)))
#define  setbit(var, bit)    ((var) |= (1UL << (bit)))
#define  clrbit(var, bit)    ((var) &= ~(1UL << (bit)))

    
#define _XTAL_FREQ  16000000
#define CHANNEL     0x0F        // Channel 16
#define VELOCITY    127         // High velocity


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

