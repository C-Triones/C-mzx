;/*------------------------------------------------------------------*/
;/* --- STC MCU International Limited -------------------------------*/
;/* --- STC 1T Series MCU A/D Conversion Demo -----------------------*/
;/* --- Mobile: (86)13922805190 -------------- ----------------------*/
;/* --- Fax: 86-755-82944243 ----------------------------------------*/
;/* --- Tel: 86-755-82948412 ----------------------------------------*/
;/* --- Web: www.STCMCU.com -----------------------------------------*/
;/* If you want to use the program or the program referenced in the  */
;/* article, please specify in which data and procedures from STC    */
;/*------------------------------------------------------------------*/

;/*Declare SFR associated with the ADC */
ADC_CONTR   EQU 0C5H            ;ADC control register
ADC_RES     EQU 0C6H            ;ADC high 8-bit result register
ADC_LOW2    EQU 0BEH            ;ADC low 2-bit result register
P1M0        EQU 091H            ;P1 mode control register0
P1M1        EQU 092H            ;P1 mode control register1

;/*Define ADC operation const for ADC_CONTR*/
ADC_POWER   EQU 80H             ;ADC power control bit
ADC_FLAG    EQU 10H             ;ADC complete flag
ADC_START   EQU 08H             ;ADC start control bit
ADC_SPEEDLL EQU 00H             ;420 clocks
ADC_SPEEDL  EQU 20H             ;280 clocks
ADC_SPEEDH  EQU 40H             ;140 clocks
ADC_SPEEDHH EQU 60H             ;70 clocks

ADCCH       DATA 20H            ;ADC channel NO.

;-----------------------------------------
    ORG   0000H
    LJMP  MAIN
    
    ORG   002BH
    LJMP  ADC_ISR
;-----------------------------------------
    ORG   0100H
MAIN:
    MOV   SP,#3FH
    MOV   ADCCH,#0
    LCALL INIT_UART             ;Init UART, use to show ADC result
    LCALL INIT_ADC              ;Init ADC sfr
    MOV   IE,#0A0H              ;Enable ADC interrupt and Open master interrupt switch
    SJMP  $

;/*----------------------------
;ADC interrupt service routine
;----------------------------*/
ADC_ISR:
    PUSH  ACC
    PUSH  PSW

    ANL   ADC_CONTR,#NOT ADC_FLAG;Clear ADC interrupt flag
    MOV   A,ADCCH
    LCALL SEND_DATA             ;Send channel NO.
    MOV   A,ADC_RES             ;Get ADC high 8-bit result
    LCALL SEND_DATA             ;Send to UART

;//if you want show 10-bit result, uncomment next 2 lines
;    MOV   A,ADC_LOW2            ;Get ADC low 2-bit result
;    LCALL SEND_DATA             ;Send to UART

    INC   ADCCH
    MOV   A,ADCCH
    ANL   A,#07H
    MOV   ADCCH,A
    ORL   A,#ADC_POWER | ADC_SPEEDLL | ADC_START
    MOV   ADC_CONTR,A           ;ADC power-on delay and re-start A/D conversion
    POP   PSW
    POP   ACC
    RETI

;/*----------------------------
;Initial ADC sfr
;----------------------------*/
INIT_ADC:
	MOV   A,#0FFH
	MOV   P1,A
	MOV   P1M0,A
	MOV   P1M1,A				;Set all P1 as Open-Drain mode
    MOV   ADC_RES,#0            ;Clear previous result
    MOV   A,ADCCH
    ORL   A,#ADC_POWER | ADC_SPEEDLL | ADC_START
    MOV   ADC_CONTR,A           ;ADC power-on delay and Start A/D conversion
    MOV   A,#2                  
    LCALL DELAY
    RET

;/*----------------------------
;Initial UART
;----------------------------*/
INIT_UART:
    MOV   SCON,#5AH             ;8 bit data ,no parity bit
    MOV   TMOD,#20H             ;T1 as 8-bit auto reload
    MOV   A,#-5                 ;Set Uart baudrate -(18432000/12/32/9600)
    MOV   TH1,A                 ;Set T1 reload value
    MOV   TL1,A
    SETB  TR1                   ;T1 start running
    RET

;/*----------------------------
;Send one byte data to PC
;Input: ACC (UART data)
;Output:-
;----------------------------*/
SEND_DATA:
    JNB   TI,$                  ;Wait for the previous data is sent
    CLR   TI                    ;Clear TI flag
    MOV   SBUF,A                ;Send current data
    RET

;/*----------------------------
;Software delay function
;----------------------------*/
DELAY:
    MOV   R2,A
    CLR   A
    MOV   R0,A
    MOV   R1,A
DELAY1:
    DJNZ  R0,DELAY1
    DJNZ  R1,DELAY1
    DJNZ  R2,DELAY1
    RET

    END