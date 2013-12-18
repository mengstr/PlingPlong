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

const uint8_t charmap[]={
    0x00,0x82,0x21,0x00,0x00,0x00,0x00,0x02,0x39,0x0f,0x00,0x00,0x00,0x40,0x80,0x52,	//  !"#$%&'()*+,-./
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x09,0x00,0x00,0x48,0x00,0x53,	// 0123456789:;<=>?
    0x00,0x77,0x7c,0x39,0x5e,0x79,0x71,0x6f,0x76,0x06,0x1e,0x70,0x38,0x37,0x54,0x3f,	// @ABCDEFGHIJKLMNO
    0x73,0x67,0x50,0x6d,0x78,0x3e,0x00,0x00,0x00,0x6e,0x00,0x39,0x00,0x0f,0x00,0x08,	// PQRSTUVWXYZ[\]^
    0x63,0x5f,0x7c,0x58,0x5e,0x7b,0x71,0x6f,0x74,0x02,0x1e,0x00,0x06,0x00,0x54,0x5c,	// `abcdefghijklmno
    0x73,0x67,0x50,0x6d,0x78,0x1c,0x00,0x00,0x00,0x6e,0x00,0x39,0x30,0x0f,0x00,0x00, 	// pqrstuvwxyz{|}~
    };



void ShiftBit(bool v) {
    if (v) DATA595=1; else DATA595=0;
    NOP();
    CLK595=1;
    NOP();
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
    uint8_t dp0,dp1,dp2;
    t=value;

    dp0=0;
    dp1=0;
    dp2=0;
    if (t>3999) {
        t=0;
        dp0=0x80;
        dp1=0x80;
        dp2=0x80;
    } else if (t>2999) {
        dp0=0x80;
        t=t-3000;
    } else if (t>1999) {
        dp1=0x80;
        t=t-2000;
    } else if (t>999) {
        dp2=0x80;
        t=t-1000;
    }
    disp[2]=charmap[16+(t%10)] | dp2;
    t=t/10;
    disp[1]=charmap[16+(t%10)] | dp1;
    t=t/10;
    disp[0]=charmap[16+(t%10)] | dp0;
}
