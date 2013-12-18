#include <stdint.h>         // uint8_t definitions
#include <string.h>         // strcpy for easteregg
#include <usart.h>

#include "config.h"
#include "dispbut.h"
#include "touch.h"
#include "easteregg.h"



const uint16_t hadLeds[]={
    0x7c9f,0x43f0,0x43f0,0x729f,    //  HTTP
    0x0140,0x6083,0x6083,0x7c9f,    //  ://H
    0x3e8f,0x462e,0x6c9f,0x3e8f,    //  ACKA
    0x3a3f,0x3e8f,0x60f8,0x0020,    //  DAY.
    0x462e,0x7e3f,0x7d9f            //  COM
};


//
// MIDI converted by Miditones https://code.google.com/p/miditones/ made by Len Shustek
//
const uint8_t eeMidiNyan [] = {
0x90,87, 0,102, 0x80, 0,3, 0x90,88, 0,102, 0x80, 0,3, 0x90,90, 0,102, 0x80, 0,109,
0x90,95, 0,102, 0x80, 0,3, 0x90,88, 0,102, 0x80, 0,3, 0x90,87, 0,102, 0x80, 0,3,
0x90,88, 0,102, 0x80, 0,3, 0x90,90, 0,102, 0x80, 0,3, 0x90,95, 0,102, 0x80, 0,3,
0x90,99, 0,102, 0x80, 0,3, 0x90,100, 0,102, 0x80, 0,3, 0x90,99, 0,102, 0x80, 0,3,
0x90,94, 0,102, 0x80, 0,3, 0x90,95, 0,102, 0x80, 0,109, 0x90,90, 0,102, 0x80, 0,109,
0x90,87, 0,102, 0x80, 0,3, 0x90,88, 0,102, 0x80, 0,3, 0x90,90, 0,102, 0x80, 0,109,
0x90,95, 0,102, 0x80, 0,109, 0x90,97, 0,102, 0x80, 0,3, 0x90,94, 0,102, 0x80, 0,3,
0x90,95, 0,102, 0x80, 0,3, 0x90,97, 0,102, 0x80, 0,3, 0x90,100, 0,102, 0x80, 0,3,
0x90,99, 0,102, 0x80, 0,3, 0x90,100, 0,102, 0x80, 0,3, 0x90,97, 0,102, 0x80, 0,3,
0x90,40, 0x91,78, 0,207, 0x81, 0,3, 0x80, 0x90,80, 0x91,52, 0,207, 0x80, 0,3, 0x81, 0x90,74,
0x91,42, 0,102, 0x80, 0,3, 0x90,75, 0,105, 0x81, 0x91,54, 0,102, 0x80, 0,3, 0x90,73,
0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,39, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3,
0x81, 0x90,71, 0x91,51, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,44, 0,207, 0x80, 0,3, 0x81,
0x90,73, 0x91,56, 0,207, 0x80, 0,3, 0x81, 0x90,74, 0x91,37, 0,207, 0x80, 0,3, 0x81, 0x90,74,
0x91,49, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,42, 0,102,
0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,54, 0,102, 0x80, 0,3, 0x90,78,
0,102, 0x80, 0,3, 0x81, 0x90,80, 0x91,35, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,47, 0,102,
0x80, 0,3, 0x81, 0x90,78, 0x91,35, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81,
0x90,75, 0x91,37, 0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3, 0x81, 0x90,73, 0x91,39,
0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,40, 0,207, 0x80, 0,3,
0x81, 0x90,78, 0x91,52, 0,207, 0x80, 0,3, 0x81, 0x90,80, 0x91,42, 0,102, 0x80, 0,3, 0x90,75,
0,102, 0x80, 0,3, 0x81, 0x90,78, 0x91,54, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3,
0x81, 0x90,75, 0x91,39, 0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,51,
0,102, 0x80, 0,3, 0x90,75, 0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,44, 0,102, 0x80, 0,3,
0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,56, 0,102, 0x80, 0,3, 0x90,73, 0,102,
0x80, 0,3, 0x81, 0x90,74, 0x91,37, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,49, 0,102, 0x80,
0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,42, 0,102, 0x80, 0,3, 0x90,78,
0,102, 0x80, 0,3, 0x81, 0x90,73, 0x91,54, 0,102, 0x80, 0,3, 0x90,74, 0,102, 0x80, 0,3,
0x81, 0x90,73, 0x91,35, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,47, 0,102, 0x80, 0,3, 0x81,
0x90,73, 0x91,35, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,37, 0,207, 0x80, 0,3, 0x81, 0x90,73,
0x91,39, 0,207, 0x80, 0,3, 0x81, 0x90,78, 0x91,40, 0,207, 0x80, 0,3, 0x81, 0x90,80, 0x91,52,
0,207, 0x80, 0,3, 0x81, 0x90,74, 0x91,42, 0,102, 0x80, 0,3, 0x90,75, 0,105, 0x81, 0x91,54,
0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,39, 0,102, 0x80, 0,3,
0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,51, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,44,
0,207, 0x80, 0,3, 0x81, 0x90,73, 0x91,56, 0,207, 0x80, 0,3, 0x81, 0x90,74, 0x91,37, 0,207,
0x80, 0,3, 0x81, 0x90,74, 0x91,49, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81,
0x90,71, 0x91,42, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,54,
0,102, 0x80, 0,3, 0x90,78, 0,102, 0x80, 0,3, 0x81, 0x90,80, 0x91,35, 0,102, 0x80, 0,3,
0x81, 0x90,75, 0x91,47, 0,102, 0x80, 0,3, 0x81, 0x90,78, 0x91,35, 0,102, 0x80, 0,3, 0x90,73,
0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,37, 0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3,
0x81, 0x90,73, 0x91,39, 0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,40,
0,207, 0x80, 0,3, 0x81, 0x90,78, 0x91,52, 0,207, 0x80, 0,3, 0x81, 0x90,80, 0x91,42, 0,102,
0x80, 0,3, 0x90,75, 0,102, 0x80, 0,3, 0x81, 0x90,78, 0x91,54, 0,102, 0x80, 0,3, 0x90,73,
0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,39, 0,102, 0x80, 0,3, 0x90,71, 0,102, 0x80, 0,3,
0x81, 0x90,74, 0x91,51, 0,102, 0x80, 0,3, 0x90,75, 0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,44,
0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,56, 0,102, 0x80, 0,3,
0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,74, 0x91,37, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,49,
0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,42, 0,102, 0x80, 0,3,
0x90,78, 0,102, 0x80, 0,3, 0x81, 0x90,73, 0x91,54, 0,102, 0x80, 0,3, 0x90,74, 0,102,
0x80, 0,3, 0x81, 0x90,73, 0x91,35, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,47, 0,102, 0x80,
0,3, 0x81, 0x90,73, 0x91,35, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,37, 0,207, 0x80, 0,3,
0x81, 0x90,73, 0x91,39, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,40, 0,207, 0x80, 0,3, 0x81,
0x90,66, 0x91,52, 0,102, 0x80, 0,3, 0x90,68, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,42,
0,207, 0x80, 0,3, 0x81, 0x90,66, 0x91,54, 0,102, 0x80, 0,3, 0x90,68, 0,102, 0x80, 0,3,
0x81, 0x90,71, 0x91,39, 0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,51,
0,102, 0x80, 0,3, 0x90,73, 0,102, 0x80, 0,3, 0x81, 0x90,76, 0x91,44, 0,102, 0x80, 0,3,
0x90,75, 0,102, 0x80, 0,3, 0x81, 0x90,76, 0x91,56, 0,102, 0x80, 0,3, 0x90,78, 0,102,
0x80, 0,3, 0x81, 0x90,71, 0x91,37, 0,207, 0x80, 0,3, 0x81, 0x90,71, 0x91,49, 0,207, 0x80,
0,3, 0x81, 0x90,66, 0x91,42, 0,102, 0x80, 0,3, 0x90,68, 0,102, 0x80, 0,3, 0x81, 0x90,71,
0x91,54, 0,102, 0x80, 0,3, 0x90,66, 0,102, 0x80, 0,3, 0x81, 0x90,76, 0x91,35, 0,102,
0x80, 0,3, 0x81, 0x90,75, 0x91,47, 0,102, 0x80, 0,3, 0x81, 0x90,73, 0x91,35, 0,102, 0x80,
0,3, 0x90,71, 0,102, 0x80, 0,3, 0x81, 0x90,64, 0x91,37, 0,102, 0x80, 0,3, 0x90,63,
0,102, 0x80, 0,3, 0x81, 0x90,64, 0x91,39, 0,102, 0x80, 0,3, 0x90,66, 0,102, 0x80, 0,3,
0x81, 0x90,71, 0x91,40, 0,207, 0x80, 0,3, 0x81, 0x90,66, 0x91,52, 0,102, 0x80, 0,3, 0x90,68,
0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,42, 0,207, 0x80, 0,3, 0x81, 0x90,66, 0x91,54, 0,102,
0x80, 0,3, 0x90,68, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,39, 0,102, 0x80, 0,3, 0x90,71,
0,102, 0x80, 0,3, 0x81, 0x90,73, 0x91,51, 0,102, 0x80, 0,3, 0x90,75, 0,102, 0x80, 0,3,
0x81, 0x90,71, 0x91,44, 0,102, 0x80, 0,3, 0x90,66, 0,102, 0x80, 0,3, 0x81, 0x90,68, 0x91,56,
0,102, 0x80, 0,3, 0x90,66, 0,102, 0x80, 0,3, 0x81, 0x90,71, 0x91,37, 0,207, 0x80, 0,3,
0x81, 0x90,71, 0x91,49, 0,105, 0x92,70, 0,102, 0x82, 0x80, 0,3, 0x81, 0x90,71, 0x91,42, 0,102,
0x80, 0,3, 0x90,66, 0,102, 0x80, 0,3, 0x81, 0x90,68, 0x91,54, 0,102, 0x80, 0,3, 0x90,71,
0,102, 0x80, 0,3, 0x81, 0x90,76, 0x91,35, 0,102, 0x80, 0,3, 0x81, 0x90,75, 0x91,47, 0,102,
0x80, 0,3, 0x81, 0x90,76, 0x91,35, 0,102, 0x80, 0,3, 0x90,78, 0,102, 0x80, 0,3,0x81,
0x90,71, 0x91,37, 0,207, 0x80, 0,3, 0xf0,
};



//
// MIDI converted by Miditones https://code.google.com/p/miditones/ made by Len Shustek
// Song is "The Fox" by Ylvis
// Arranged by S0L1DGH0ST1
//
//  The bytestream is a series of commands that turn notes on and off, and
//  start delays until the next note change.  Here are the details, with numbers
//  shown in hexadecimal.
//
//  If the high-order bit of the byte is 1, then it is one of the following commands:
//
//    9t nn  Start playing note nn on tone generator t.  Generators are numbered
//           starting with 0.  The notes numbers are the MIDI numbers for the chromatic
//           scale, with decimal 60 being Middle C, and decimal 69 being Middle A (440 Hz).
//
//    8t     Stop playing the note on tone generator t.
//
//    F0     End of score: stop playing.
//
//
//  If the high-order bit of the byte is 0, it is a command to delay for a while until
//  the next note change..  The other 7 bits and the 8 bits of the following byte are
//  interpreted as a 15-bit big-endian integer that is the number of milliseconds to
//  wait before processing the next command.  For example,
//
//     07 D0
//
//  would cause a delay of 0x07d0 = 2000 decimal millisconds, or 2 seconds.  Any tones
//  that were playing before the delay command will continue to play.
//
//
const uint8_t eeMidiFox [] = {
0x90,73, 0x91,52, 0x92,56, 0x93,61, 0,229, 0x80, 0,4, 0x90,76, 0,229, 0x81, 0x82, 0x83, 0,4,
0x91,49, 0,229, 0x80, 0,4, 0x90,76, 0,229, 0x80, 0,4, 0x90,78, 0,229, 0x81, 0,4,
0x91,49, 0,229, 0x80, 0,4, 0x90,83, 0,229, 0x80, 0,4, 0x90,80, 0,229, 0x81, 0x80, 0,4,
0x90,51, 0x91,54, 0x92,59, 0,234, 0x93,73, 0,229, 0x80, 0x81, 0x82, 0,4, 0x90,47, 0,229,
0x83, 0,4, 0x91,76, 0,229, 0x81, 0,4, 0x91,78, 0,229, 0x80, 0,4, 0x90,47, 0,229,
0x81, 0,4, 0x91,80, 0,229, 0x81, 0,4, 0x91,73, 0,229, 0x80, 0x81, 0,4, 0x90,49, 0x91,54,
0x92,58, 0,234, 0x93,73, 0,229, 0x80, 0x81, 0x82, 0,4, 0x90,42, 0,229, 0x83, 0,4, 0x91,76,
0,229, 0x81, 0,4, 0x91,78, 0,229, 0x80, 0,4, 0x90,42, 0,229, 0x81, 0,4, 0x91,83,
0,229, 0x81, 0,4, 0x91,80, 0,229, 0x80, 0x81, 0,4, 0x90,42, 0,234, 0x91,73, 0,229,
0x80, 0,4, 0x90,42, 0,229, 0x81, 0,4, 0x91,73, 0,229, 0x81, 0,4, 0x91,76, 0,229,
0x80, 0x81, 0,4, 0x90,42, 0x91,75, 0,229, 0x81, 0,4, 0x91,71, 0,229, 0x81, 0,4, 0x91,73,
0,229, 0x80, 0x81, 0,4, 0x90,49, 0,229, 0x80, 0,4, 0x90,56, 0,229, 0x80, 0,4, 0x90,61,
0,229, 0x80, 0,4, 0x90,64, 0,229, 0x80, 0,4, 0x90,68, 0x91,61, 0,229, 0x81, 0,4,
0x91,56, 0,229, 0x80, 0x81, 0,4, 0x90,68, 0x91,49, 1,207, 0x80, 0x81, 0,4, 0x90,66, 0x91,47,
0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4, 0x91,59, 0,229, 0x81, 0,4, 0x91,63,
0,229, 0x80, 0x81, 0,4, 0x90,63, 0x91,59, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81,
0,4, 0x90,66, 0x91,47, 1,207, 0x80, 0x81, 0,4, 0x90,66, 0x91,42, 0,229, 0x81, 0,4,
0x91,49, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4, 0x91,58, 0,229, 0x80, 0x81, 0,4,
0x90,63, 0x91,54, 0,229, 0x81, 0,4, 0x91,49, 0,229, 0x80, 0x81, 0,4, 0x90,66, 0x91,42,
1,207, 0x80, 0x81, 0,4, 0x90,66, 0x91,42, 0,229, 0x81, 0,4, 0x91,49, 0,229, 0x80, 0x81,
0,4, 0x90,63, 0x91,54, 0,229, 0x81, 0,4, 0x91,49, 0,229, 0x80, 0x81, 0,4, 0x90,64,
0x91,58, 0,229, 0x81, 0,4, 0x91,49, 0,229, 0x80, 0x81, 0,4, 0x90,63, 0x91,54, 0,229,
0x81, 0,4, 0x91,49, 0,229, 0x80, 0x81, 0,4, 0x90,61, 0x91,49, 0,229, 0x81, 0,4, 0x91,56,
0,229, 0x81, 0,4, 0x91,61, 0,229, 0x81, 0,4, 0x91,64, 0,229, 0x80, 0x81, 0,4, 0x90,68,
0x91,61, 0,229, 0x81, 0,4, 0x91,56, 0,229, 0x80, 0x81, 0,4, 0x90,68, 0x91,49, 1,207,
0x80, 0x81, 0,4, 0x90,66, 0x91,47, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4, 0x91,59,
0,229, 0x81, 0,4, 0x91,63, 0,229, 0x80, 0x81, 0,4, 0x90,63, 0x91,59, 0,229, 0x81, 0,4,
0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,66, 0x91,47, 1,207, 0x80, 0x81, 0,4, 0x90,66, 0x91,42,
0,229, 0x81, 0,4, 0x91,49, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4, 0x91,58,
0,229, 0x80, 0x81, 0,4, 0x90,54, 0,229, 0x80, 0,4, 0x90,63, 0x91,49, 0,229, 0x80, 0x81,
0,4, 0x90,66, 0x91,42, 0,229, 0x80, 0,4, 0x90,71, 0,229, 0x81, 0,4, 0x91,42, 0,229,
0x80, 0x81, 0,4, 0x90,70, 0x91,49, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81, 0,4,
0x90,68, 0x91,49, 0,229, 0x81, 0,4, 0x91,58, 0,229, 0x80, 0x81, 0,4, 0x90,70, 0x91,49,
0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,68, 0x91,49, 0,229, 0x81, 0,4,
0x91,49, 0,229, 0x80, 0x81, 0,4, 0x90,56, 0,229, 0x80, 0,4, 0x90,61, 0,229, 0x80, 0,4,
0x90,64, 0,229, 0x80, 0,4, 0x90,68, 0x91,61, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,56,
0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,49, 1,207, 0x81, 0,4, 0x91,47, 0,229, 0x81, 0,4,
0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,59, 0,229, 0x80, 0,4, 0x90,68, 0x91,63, 0,229,
0x80, 0x81, 0,4, 0x90,71, 0x91,59, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,54, 0,229, 0x80,
0x81, 0,4, 0x90,71, 0x91,47, 0,229, 0x80, 0,4, 0x90,70, 0,229, 0x81, 0,4, 0x91,42,
0,229, 0x81, 0,4, 0x91,49, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4, 0x91,58,
0,229, 0x80, 0x81, 0,4, 0x90,54, 0,229, 0x80, 0,4, 0x90,68, 0x91,49, 0,229, 0x80, 0x81,
0,4, 0x90,68, 0x91,42, 0,229, 0x80, 0,4, 0x90,71, 0,229, 0x81, 0,4, 0x91,42, 0,229,
0x80, 0x81, 0,4, 0x90,70, 0x91,49, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81, 0,4,
0x90,68, 0x91,49, 0,229, 0x81, 0,4, 0x91,58, 0,229, 0x80, 0x81, 0,4, 0x90,68, 0x91,49,
0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,68, 0x91,49, 0,229, 0x81, 0,4,
0x91,49, 0,229, 0x81, 0,4, 0x91,56, 0,229, 0x80, 0x81, 0,4, 0x90,61, 0,229, 0x80, 0,4,
0x90,68, 0x91,64, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,61, 0,229, 0x80, 0x81, 0,4, 0x90,71,
0x91,56, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,49, 0,229, 0x80, 0,4, 0x90,70, 0,229,
0x81, 0,4, 0x91,47, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,59, 0,229,
0x80, 0,4, 0x90,68, 0x91,63, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,59, 0,229, 0x80, 0x81,
0,4, 0x90,71, 0x91,54, 0,229, 0x80, 0x81, 0,4, 0x90,71, 0x91,47, 0,229, 0x80, 0,4,
0x90,70, 0,229, 0x81, 0,4, 0x91,42, 0,229, 0x81, 0,4, 0x91,49, 0,229, 0x81, 0,4,
0x91,54, 0,229, 0x81, 0,4, 0x91,58, 0,229, 0x81, 0,4, 0x91,54, 0,229, 0x81, 0,4,
0x91,49, 0,229,0x81, 0,4, 0x91,42, 1,207, 0x80, 0x81, 0,4, 0x90,30, 0x91,42, 0,234,
0x92,66, 0x93,78, 0,229, 0x82, 0x83,
0xA0,16, // change sound
0,4, 0x92,66, 0x93,78, 0,229, 0x82, 0x83, 0,4, 0x92,64,
0x93,76, 0,229, 0x82, 0x83, 0,4, 0x92,68, 0x93,80, 1,207, 0x82, 0x83, 0,4, 0x92,61, 0x93,73,
1,207, 0x80, 0x81, 0x82, 0x83, 0,4, 0x90,37, 0x91,73, 0x92,44, 0x93,85, 0,229, 0x81, 0x83, 0,4,
0x91,73, 0x93,85, 0,229, 0x80, 0x82, 0x81, 0x83, 0,4, 0x90,37, 0x91,73, 0x92,44, 0x93,85, 0,229,
0x81, 0x83, 0x80, 0x82, 0,4, 0x90,73, 0x91,37, 0x92,85, 0x93,44, 0,229, 0x80, 0x82, 0,4, 0x90,73,
0x92,85, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,37, 0x91,73, 0x92,44, 0x93,85, 0,112, 0x81,
0x83, 0,4, 0x91,73, 0x93,85, 0,112, 0x80, 0x82, 0,4, 0x90,49, 0x92,56, 0,112, 0x83, 0x81,
0,4, 0x91,73, 0x93,85, 0,112, 0x82, 0x80, 0x81, 0x83, 0,4, 0x90,37, 0x91,73, 0x92,44, 0x93,85,
0,112, 0x81, 0x83, 0,117, 0x80, 0x82, 0,4, 0x90,35, 0x91,42, 0x92,47, 0,117, 0x93,73, 0,112,
0x83, 0,4, 0x93,73, 0,229, 0x80, 0x81, 0x82, 0x83, 0,4, 0x90,35, 0x91,73, 0x92,42, 0x93,85,
0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,73, 0x91,35, 0x92,85, 0x93,42, 0,229, 0x80, 0x82, 0,4,
0x90,73, 0x92,85, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,35, 0x91,73, 0x92,42, 0x93,85, 0,112,
0x81, 0x83, 0,4, 0x91,73, 0x93,85, 0,112, 0x80, 0x82, 0,4, 0x90,47, 0x92,54, 0,112, 0x83,
0x81, 0,4, 0x91,73, 0x93,85, 0,112, 0x82, 0x80, 0x81, 0x83, 0,4, 0x90,35, 0x91,73, 0x92,42,
0x93,85, 0,112, 0x81, 0x83, 0,117, 0x80, 0x82, 0,4, 0x90,73, 0x91,30, 0x92,85, 0x93,37, 0,229,
0x80, 0x82, 0,4, 0x90,73, 0x92,85, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,30, 0x91,73, 0x92,37,
0x93,85, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,73, 0x91,30, 0x92,85, 0x93,37, 0,229, 0x80,
0x82, 0,4, 0x90,73, 0x92,85, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,30, 0x91,73, 0x92,37,
0x93,85, 0,112, 0x81, 0x83, 0,4, 0x91,73, 0x93,85, 0,112, 0x80, 0x82, 0,4, 0x90,42, 0x92,49,
0,112, 0x83, 0x81, 0,4, 0x91,73, 0x93,85, 0,112, 0x82, 0x80, 0x81, 0x83, 0,4, 0x90,30, 0x91,73,
0x92,37, 0x93,85, 0,112, 0x81, 0x83, 0,117, 0x80, 0x82, 0,4, 0x90,30, 0x91,42, 1,207, 0x80,
0x81, 0,4, 0x90,66, 0x91,30, 0x92,78, 0x93,42, 0,229, 0x80, 0x82, 0,4, 0x90,64, 0x92,76,
0,229, 0x80, 0x82, 0,4, 0x90,68, 0x92,80, 1,207, 0x80, 0x82, 0,4, 0x90,61, 0x92,73, 1,207,
0x81, 0x83, 0x80, 0x82, 0,4, 0x90,37, 0x91,68, 0x92,44, 0x93,80, 0,229, 0x81, 0x83, 0,4, 0x91,68,
0x93,80, 0,229, 0x80, 0x82, 0x81, 0x83, 0,4, 0x90,37, 0x91,68, 0x92,44, 0x93,80, 0,229, 0x81,
0x83, 0x80, 0x82, 0,4, 0x90,68, 0x91,37, 0x92,80, 0x93,44, 0,229, 0x80, 0x82, 0,4, 0x90,68,
0x92,80, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,37, 0x91,68, 0x92,44, 0x93,80, 0,112, 0x81,
0x83, 0,4, 0x91,68, 0x93,80, 0,112, 0x80, 0x82, 0,4, 0x90,49, 0x92,56, 0,112, 0x83, 0x81,
0,117, 0x82, 0x80, 0,4, 0x90,37, 0x91,44, 0x92,49, 0,229, 0x80, 0x81, 0x82, 0,4, 0x90,35,
0x91,42, 0x92,47, 0,117, 0x93,68, 0,112, 0x83, 0,4, 0x93,68, 0,229, 0x80, 0x81, 0x82, 0x83,
0,4, 0x90,35, 0x91,68, 0x92,42, 0x93,80, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,68, 0x91,35,
0x92,80, 0x93,42, 0,229, 0x80, 0x82, 0,4, 0x90,68, 0x92,80, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4,
0x90,35, 0x91,68, 0x92,42, 0x93,80, 0,112, 0x81, 0x83, 0,4, 0x91,68, 0x93,80, 0,112, 0x80,
0x82, 0,4, 0x90,47, 0x92,54, 0,112, 0x83, 0x81, 0,117, 0x82, 0x80, 0,4, 0x90,35, 0x91,42,
0x92,47, 0,229, 0x80, 0x81, 0x82, 0,4, 0x90,68, 0x91,30, 0x92,80, 0x93,37, 0,229, 0x80, 0x82,
0,4, 0x90,68, 0x92,80, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,30, 0x91,68, 0x92,37, 0x93,80,
0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,68, 0x91,30, 0x92,80, 0x93,37, 0,229, 0x80, 0x82, 0,4,
0x90,68, 0x92,80, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,30, 0x91,68, 0x92,37, 0x93,80, 0,112,
0x81, 0x83, 0,4, 0x91,68, 0x93,80, 0,112, 0x80, 0x82, 0,4, 0x90,42, 0x92,49, 0,112, 0x83,
0x81, 0,117, 0x82, 0x80, 0,4, 0x90,30, 0x91,37, 0x92,42, 0,229, 0x80, 0x81, 0x82, 0,4, 0x90,30,
0x91,42, 1,207, 0x80, 0x81, 0,4, 0x90,66, 0x91,30, 0x92,78, 0x93,42, 0,229, 0x80, 0x82, 0,4,
0x90,64, 0x92,76, 0,229, 0x80, 0x82, 0,4, 0x90,68, 0x92,80, 1,207, 0x80, 0x82, 0,4, 0x90,61,
0x92,73, 1,207, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,37, 0x91,59, 0x92,44, 0x93,71, 0,229, 0x81,
0x83, 0,4, 0x91,61, 0x93,73, 0,229, 0x80, 0x82, 0x81, 0x83, 0,4, 0x90,37, 0x91,59, 0x92,44,
0x93,71, 0,229, 0x81, 0x83, 0x80, 0x82, 0,4, 0x90,61, 0x91,37, 0x92,73, 0x93,44, 0,229, 0x80,
0x82,
0xf0
};





void EeNoteOn(uint8_t no) {
    while (Busy2USART());
    Write2USART(0x90|CHANNEL);
    while (Busy2USART());
    Write2USART(no);
    while (Busy2USART());
    Write2USART(VELOCITY);
    __delay_ms(1);
}

void EeNoteOff(uint8_t no) {
    while (Busy2USART());
    Write2USART(0x80|CHANNEL);
    while (Busy2USART());
    Write2USART(no);
    while (Busy2USART());
    Write2USART(VELOCITY);
    __delay_ms(1);
}

void EeSendCC(uint8_t no, uint8_t v) {
    while (Busy2USART());
    Write2USART(0xB0|CHANNEL);
    while (Busy2USART());
    Write2USART(no);
    while (Busy2USART());
    Write2USART(v);
    __delay_ms(1);
}




void EeAllNotesOff(void) {
    uint8_t i;
    for (i=0; i<127; i++) {
        EeNoteOff(i);
    }
}


void EasterEgg(uint8_t mode) {
    uint8_t     i,j;
    uint8_t     tmps[20];
    uint16_t    noteCnt;
    uint8_t     eeChannelTone[16];
    uint8_t     b1,b2;
    uint16_t    ii, dly;
    uint8_t     *pMidi;


    // Step 1 - Silence all channels
    EeAllNotesOff();
    leds=0x00;
    disp[0]=0x00;
    disp[1]=0x00;
    disp[2]=0x00;

    // If mode is 1 display HTTP://HACKADAY.COM on 7-segs
    if (mode==1) {
        //           000111222333444555666777
        strcpy(tmps,"HTTP: // HACKADAY .  COM");
        for (i=0; i<8; i++) {
            disp[0]=charmap[tmps[0+((i)*3)]-32];
            disp[1]=charmap[tmps[1+((i)*3)]-32];
            disp[2]=charmap[tmps[2+((i)*3)]-32];
            for (j=0; j<40; j++) __delay_ms(10);
        }
    }

    // If mode is 2 display HTTP://HACKADAY.COM on the leds
    if (mode==2) {
        for (j=0; j<100; j++) __delay_ms(10);
        for (i=0; i<sizeof(hadLeds)/2; i++) {
            leds=hadLeds[i];
            for (j=0; j<40; j++) __delay_ms(10);
            leds=0;
            for (j=0; j<5; j++) __delay_ms(10);
        }
    }

    disp[0]=0x00;
    disp[1]=0x00;
    disp[2]=0x00;


    // Start playing tune
    if (mode==1) {
        EeSendCC(10,8); // Start with sound #8 plain sinus
        pMidi=eeMidiFox;// +821;
    } else {
        EeSendCC(10,16); // Start with sound #64
        pMidi=eeMidiNyan;
    }
    noteCnt=0;


    // Play the mididata
    for (;;) {
        b1=*pMidi;
        b2=*(pMidi+1);

        // End-Of-Song
        if ((b1&0xF0)==0xF0) {
            EeAllNotesOff();
            leds=0x00;
            disp[0]=0x00;
            disp[1]=0x00;
            disp[2]=0x00;
            return;
        }

        // Sound change
        if ((b1&0xF0)==0xA0) {
            EeSendCC(10,b2);
            pMidi+=2;
            continue;
        }


        // Note on
        if ((b1&0xF0)==0x90) {
            if (mode==2) b2=b2-12;  // Nyan is too high-pitched
            eeChannelTone[b1&0x0F]=b2;
            setbit(leds,b1&0xF);
            EeNoteOn(eeChannelTone[b1&0x0F]);
            pMidi+=2;
            noteCnt++;
            DispValue(noteCnt);
            continue;
        }

        // Note off
        if ((b1&0xF0)==0x80) {
            clrbit(leds,b1&0x0F);
            EeNoteOff(eeChannelTone[b1&0x0F]);
            pMidi+=1;
            continue;
        }

        // Delay
        if ((b1&0x80)==0x000) {
            dly=b1;
            dly=dly*256;
            dly=dly+b2;
            dly=dly/2;
            for (ii=0; ii<dly; ii++) __delay_ms(1);
            pMidi+=2;
            continue;
        }

    }
}