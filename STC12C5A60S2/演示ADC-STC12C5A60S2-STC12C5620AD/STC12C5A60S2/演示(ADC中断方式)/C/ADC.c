/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU A/D Conversion Demo -----------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-755-82944243 ----------------------------------------*/
/* --- Tel: 86-755-82948412 ----------------------------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#include "reg51.h"
#include "intrins.h"

#define FOSC    18432000L
#define BAUD    9600

typedef unsigned char BYTE;
typedef unsigned int WORD;

/*Declare SFR associated with the ADC */
sfr ADC_CONTR   =   0xBC;           //ADC control register
sfr ADC_RES     =   0xBD;           //ADC hight 8-bit result register
sfr ADC_LOW2    =   0xBE;           //ADC low 2-bit result register
sfr P1ASF       =   0x9D;           //P1 secondary function control register

/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks

void InitUart();
void SendData(BYTE dat);
void Delay(WORD n);
void InitADC();

BYTE ch = 0;                        //ADC channel NO.

void main()
{
    InitUart();                     //Init UART, use to show ADC result
    InitADC();                      //Init ADC sfr
    IE = 0xa0;                      //Enable ADC interrupt and Open master interrupt switch
                                    //Start A/D conversion
    while (1);
}

/*----------------------------
ADC interrupt service routine
----------------------------*/
void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag

    SendData(ch);                   //Show Channel NO.
    SendData(ADC_RES);              //Get ADC high 8-bit result and Send to UART

//if you want show 10-bit result, uncomment next line
//    SendData(ADC_LOW2);             //Show ADC low 2-bit result
    
    if (++ch > 7) ch = 0;           //switch to next channel
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
}

/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC()
{
    P1ASF = 0xff;                   //Set all P1 as analog input port
    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    Delay(2);                       //ADC power-on delay and Start A/D conversion
}

/*----------------------------
Initial UART
----------------------------*/
void InitUart()
{
    SCON = 0x5a;                    //8 bit data ,no parity bit
    TMOD = 0x20;                    //T1 as 8-bit auto reload
    TH1 = TL1 = -(FOSC/12/32/BAUD); //Set Uart baudrate
    TR1 = 1;                        //T1 start running
}

/*----------------------------
Send one byte data to PC
Input: dat (UART data)
Output:-
----------------------------*/
void SendData(BYTE dat)
{
    while (!TI);                    //Wait for the previous data is sent
    TI = 0;                         //Clear TI flag
    SBUF = dat;                     //Send current data
}

/*----------------------------
Software delay function
----------------------------*/
void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

