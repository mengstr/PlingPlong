#include <stdint.h>         // uint8_t definitions
#include <xc.h>
#include "config.h"
#include "touch.h"

const uint8_t PADMAP[PADS]={14,15,20,21,22,23,16,17,18,19,24,25,12,10,8,9,11,13,0,1,2,3,4,5};
volatile int16_t padBase[PADS];



int16_t GetPadBaseValue(uint8_t no) {
    return padBase[no];
}


/**************************************************************************/
/*Set up CTMU *****************************************************************/
/**************************************************************************/
void SetupCTMU(void) {
    //CTMUCONH/1 - CTMU Control registers
    CTMUCONH = 0x00; //make sure CTMU is disabled
    CTMUCONL = 0x90;
    //CTMU continues to run when emulator is stopped,CTMU continues
    //to run in idle mode,Time Generation mode disabled, Edges are blocked
    //No edge sequence order, Analog current source not grounded, trigger
    //output disabled, Edge2 polarity = positive level, Edge2 source =
    //source 0, Edge1 polarity = positive level, Edge1 source = source 0,
    //CTMUICON - CTMU Current Control Register
    CTMUICON = 0x03; //0.55uA*100=55uA, Nominal - No Adjustment
    /**************************************************************************/
    //Set up AD converter;
    /**************************************************************************/
    // ADCON2
    ADCON2bits.ADFM=1; // Results format 1= Right justified
    ADCON2bits.ACQT=1; // Acquition time 7 = 20TAD 2 = 4TAD 1=2TAD
    ADCON2bits.ADCS=2; // Clock conversion bits 6= FOSC/64 2=FOSC/32
    // ADCON1
    ADCON1bits.PVCFG0 =0; // Vref+ = AVdd
    ADCON1bits.NVCFG1 =0; // Vref- = AVss
    // ADCON0
    ADCON0bits.ADON=1; // Turn on ADC
}





uint16_t ReadPad(uint8_t no) {
    uint32_t v;
    uint8_t i;

    v=0;
    for (i=0; i<TOUCHOVERSAMPLE; i++) {
        ADCON0bits.CHS=PADMAP[no];      // Select ADC channel
        CTMUCONHbits.CTMUEN = 1;        // Enable the CTMU
        CTMUCONLbits.EDG1STAT = 0;      // Set Edge status bits to zero
        CTMUCONLbits.EDG2STAT = 0;
        CTMUCONHbits.IDISSEN = 1;       //drain charge on the circuit
        __delay_us(DISCHARGETIME);
        CTMUCONHbits.IDISSEN = 0;       //end drain of circuit
        di();
        CTMUCONLbits.EDG1STAT = 1;      //Begin charging the circuit using CTMU current source
        __delay_us(CHARGETIME);
        CTMUCONLbits.EDG1STAT = 0;      //Stop charging circuit
        PIR1bits.ADIF = 0;              //make sure A/D Int not set
        ADCON0bits.GO=1;                //and begin A/D conv.
        while(!PIR1bits.ADIF);          //Wait for A/D convert complete
        ei();
        v+=ADRES;                        //Get the value from the A/D
    }
    return v/TOUCHOVERSAMPLE;
}



void CalibratePads(void) {
    uint8_t i,j;
    uint16_t avg;

    for (i=0; i<PADS; i++) {
        avg=0;
        for (j=0; j<CALIBRATEOVERSAMPLE; j++) {
            __delay_ms(1);
            avg+=ReadPad(i);
        }
        avg=avg/CALIBRATEOVERSAMPLE;
        padBase[i]=avg;
    }
}

