#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <xc.h>
#include "dispbut.h"

#define KEY1            PORTAbits.RA7
#define KEY2            PORTEbits.RE1
#define KEY3            PORTEbits.RE2

#define LATCH595        LATAbits.LA6
#define CLK595          LATBbits.LB6
#define DATA595         LATBbits.LB7


volatile uint8_t    disp[3];
volatile uint16_t   leds;
volatile uint16_t   keys;
volatile uint8_t    butt;



void ShiftBit(bool v) {
    if (v) DATA595=1; else DATA595=0;
    CLK595=1;
    CLK595=0;
}

void ShiftByte(uint8_t v) {
    ShiftBit(v&0x80);
    ShiftBit(v&0x40);
    ShiftBit(v&0x20);
    ShiftBit(v&0x10);
    ShiftBit(v&0x08);
    ShiftBit(v&0x04);
    ShiftBit(v&0x02);
    ShiftBit(v&0x01);
}



void RefreshDisp(void) {
    static uint8_t cath=0;
    uint8_t v;
    uint8_t no;

    cath++;
    if (cath==6) {
        cath=0;
    }

    if (cath==0) {
        keys=0;
        butt=0;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x20);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY1==0) keys|=0x0001;
        if (KEY2==0) keys|=0x0020;
        if (KEY3==0) keys|=0x0400;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x08);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY1==0) keys|=0x0002;
        if (KEY2==0) keys|=0x0040;
        if (KEY3==0) keys|=0x0800;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x04);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY1==0) keys|=0x0004;
        if (KEY2==0) keys|=0x0080;
        if (KEY3==0) keys|=0x1000;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x02);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY1==0) keys|=0x0008;
        if (KEY2==0) keys|=0x0100;
        if (KEY3==0) keys|=0x2000;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x40);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY1==0) keys|=0x0010;
        if (KEY2==0) keys|=0x0200;
        if (KEY3==0) keys|=0x4000;

        LATCH595=0;
        ShiftByte(0x00);
        ShiftByte(~0x01);
        LATCH595=1;
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        if (KEY2==0) butt=1;

        return;
    }

    v=0;
    if (cath==1) {
        if (leds&0x0100) v|=0x80;
        if (leds&0x0200) v|=0x40;
        if (leds&0x0400) v|=0x20;
        if (leds&0x0800) v|=0x08;
        if (leds&0x1000) v|=0x10;
        if (leds&0x2000) v|=0x02;
        if (leds&0x4000) v|=0x01;
    }
    if (cath==2) {
        if (leds&0x0001) v|=0x80;
        if (leds&0x0002) v|=0x40;
        if (leds&0x0004) v|=0x20;
        if (leds&0x0008) v|=0x08;
        if (leds&0x0010) v|=0x10;
        if (leds&0x0020) v|=0x02;
        if (leds&0x0040) v|=0x01;
        if (leds&0x0080) v|=0x04;
    }
    if (cath==3 || cath==4 || cath==5) {
        no=cath-3;
        if (disp[no]&0x01) v|=0x40;     // SEG_A ~
        if (disp[no]&0x02) v|=0x10;     // SEG_B ~
        if (disp[no]&0x04) v|=0x04;     // SEG_C ~
        if (disp[no]&0x08) v|=0x02;     // SEG_D ~
        if (disp[no]&0x10) v|=0x08;     // SEG_E
        if (disp[no]&0x20) v|=0x20;     // SEG_F
        if (disp[no]&0x40) v|=0x80;     // SEG_G
        if (disp[no]&0x80) v|=0x01;     // SEG_H
    }

    LATCH595=0;
    ShiftBit(cath==3);
    ShiftBit(cath==5);
    ShiftBit(cath==4);
    ShiftBit(false);
    ShiftBit(false);
    ShiftBit(cath==1);
    ShiftBit(cath==2);
    ShiftBit(false);
    ShiftByte(v);
    LATCH595=1;
}


void DispValue(uint16_t value) {
    uint16_t t;
    t=value;
    if (t>999) {
        disp[2]=0x80;
        disp[1]=0x80;
        disp[0]=0x80;
    } else {
        disp[2]=charmap[16+(t%10)];
        t=t/10;
        disp[1]=charmap[16+(t%10)];
        t=t/10;
        disp[0]=charmap[16+(t%10)];
    }
}
