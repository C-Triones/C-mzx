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

;-----------------------------------------
    ORG   0000H
    LJMP  MAIN
;-----------------------------------------
    ORG   0100H
MAIN:
    LCALL INIT_UART             ;Init UART, use to show ADC result
    LCALL INIT_ADC              ;Init ADC sfr
;-------------------------------
NEXT:
    MOV   A,#0
    LCALL SHOW_RESULT           ;Show channel0 result
    MOV   A,#1
    LCALL SHOW_RESULT           ;Show channel1 result
    MOV   A,#2
    LCALL SHOW_RESULT           ;Show channel2 result
    MOV   A,#3
    LCALL SHOW_RESULT           ;Show channel3 result
    MOV   A,#4
    LCALL SHOW_RESULT           ;Show channel4 result
    MOV   A,#5
    LCALL SHOW_RESULT           ;Show channel5 result
    MOV   A,#6
    LCALL SHOW_RESULT           ;Show channel6 result
    MOV   A,#7
    LCALL SHOW_RESULT           ;Show channel7 result

    SJMP  NEXT

;/*----------------------------
;Send ADC result to UART
;Input: ACC (ADC channel NO.)
;Output:-
;----------------------------*/
SHOW_RESULT:
    LCALL SEND_DATA             ;Show Channel NO.
    LCALL GET_ADC_RESULT        ;Get high 8-bit ADC result
    LCALL SEND_DATA             ;Show result

;//if you want show 10-bit result, uncomment next 2 lines
;    MOV   A,ADC_LOW2            ;Get low 2-bit ADC result
;    LCALL SEND_DATA             ;Show result
    RET


;/*----------------------------
;Read ADC conversion result
;Input: ACC (ADC channel NO.)
;Output:ACC (ADC result)
;----------------------------*/
GET_ADC_RESULT:
    ORL   A,#ADC_POWER | ADC_SPEEDLL | ADC_START
    MOV   ADC_CONTR,A           ;Start A/D conversion
    NOP                         ;Must wait before inquiry
    NOP
    NOP
    NOP
WAIT:
    MOV   A,ADC_CONTR           ;Wait complete flag
    JNB   ACC.4,WAIT            ;ADC_FLAG(ADC_CONTR.4)
    ANL   ADC_CONTR,#NOT ADC_FLAG ;Clear ADC_FLAG
    MOV   A,ADC_RES             ;Return ADC result
    RET

;/*----------------------------
;Initial ADC sfr
;----------------------------*/
INIT_ADC:
	MOV   A,#0FFH
	MOV   P1,A
	MOV   P1M0,A
	MOV   P1M1,A				;Set all P1 as Open-Drain mode
    MOV   ADC_RES,#0            ;Clear previous result
    MOV   ADC_CONTR,#ADC_POWER | ADC_SPEEDLL
    MOV   A,#2                  ;ADC power-on and delay
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