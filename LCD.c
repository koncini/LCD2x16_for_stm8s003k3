 /********************************************************
 Company: Dinamica y Desarrollo								
 Designed by: Juan Sebastian Rinc�n Manrique
 Date: 13/09/2017
 Description: Este codigo incluye las funciones necesarias
              para operar un LCD de 16x2 mediante 4 lineas
              (D4,D5,D6,D7))de datos y 2 lineas de control
              (RS,E) 
 Dependencies: lcd2x16.h

 *********************************************************/

//////////////////////////////////////////////////////////////
//Libraries
//////////////////////////////////////////////////////////////

#include "lcd2x16.h"
#define BACKLIGTH

//////////////////////////////////////////////////////////////

//Functions: The following are avalaible functions
/* 
   LCD_Init()
   LCDGotoXY(uint8_t x,uint8_t y)
   LCDDisableBackLigth(void)
   LCDEnableBackLigth(void)
   LCDDisplayON(void)
   LCDDisplayOFF(void)
   LCDWriteChar(uint8_t ch)
   LCDWriteString(uint8_t x,uint8_t y, uint8_t *str)
   LCDWriteCommand(uint8_t cmd)
   LCDWrite4bits(uint8_t bdata)
   LCDToggleEN()
   LCDEnableCursor(uint8_t x,uint8_t y)
   LCDDisableCursor(void)
   LCDClearDisplay(void)
   LCDWaitShort(uint8_t w )
   LCDWaitLong(uint16_t w )
*/

//////////////////////////////////////////////////////////////

/*-------------------------------Start init-----------------------------------*/
void LCD_Init(void){
  
  PA_ODR = 0x00;
  PA_DDR = 0x00;
  PA_CR1 = 0x00;
  PA_CR2 = 0x00;
  
  PD_ODR = 0x00;
  PD_DDR = 0x00;
  PD_CR1 = 0x00;
  PD_CR2 = 0x00;
  
  LCDWaitLong(5);
  LCD_INIT_MACRO;
  PB_CR1=1<<5;
  PB_CR1_C15=1;	
  /* Initialize data port */
  LCD_DATA1 = 0;
  LCD_DATA2 = 0;
  LCD_DATA3 = 0;
  LCD_DATA4 = 0; 
  
  LCD_REG_SEL = 0;
  LCD_EN = 0;
  
  /* Send the reset sequence */
  LCDWrite4bits(0x30);
  LCDToggleEN();
  LCDWaitLong(5);
  LCDWrite4bits(0x30);
  LCDToggleEN();
  LCDWaitShort(2);
  LCDWrite4bits(0x30);
  LCDToggleEN();
  LCDWaitShort(2);
  LCDWrite4bits(0x20);
  LCDToggleEN();
  LCDWaitShort(1);
  
  /* Function, 4 bit data length */
  LCDWrite4bits(0x20);
  LCDToggleEN();
  LCDWaitShort(1);
  
  /*  2 lines, 5x7 dot format  */
  LCDWrite4bits(0x80);
  LCDToggleEN();
  LCDWaitShort(4);
  
  // Entry Mode Inc, No Shift
  LCDWrite4bits(0x00);
  LCDToggleEN();
  LCDWaitShort(1);
  LCDWrite4bits(0x60);
  LCDToggleEN();
  LCDWaitShort(5);
  
  // Display ON/OFF Control - Display On, Cursor Off, Blink Off
  LCDWrite4bits(0x00);
  LCDToggleEN();
  LCDWaitShort(1);
  LCDWrite4bits(0xC0);
  LCDToggleEN();
  LCDWaitShort(5);
  
  // Display Clear
  LCDClearDisplay();
}

/*---------------------------------End init-----------------------------------*/

/*------------------------LCD functions----------------------*/

void LCDGotoXY( uint8_t x,uint8_t y ){
  /*  Setup the R/W for writing (PTGD), Initialize EN and RS to 0 */
    uint8_t pos;
    
    if(y==2){
    pos=0xC0;
    } 
    else{
     pos=0x80;
    }
    pos=(uint8_t)(pos+x);
    LCD_REG_SEL = 0;     

    /* DD Ram Address Set - 1st Digit */
    LCDWrite4bits(pos);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits((uint8_t)(pos<<4));
    LCDToggleEN();
    LCDWaitShort(4);
}

void LCDDisableBackLigth(void){
#ifdef BACKLIGTH
	LCD_BACKLIGTH=0;
#endif
}

void LCDEnableBackLigth(void){
#ifdef BACKLIGTH
	LCD_BACKLIGTH=1;
#endif
}

void LCDDisplayON(void){
    /* Setup the R/W for writing , Initialize EN and RS to 0 */
    LCD_REG_SEL = 0;
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xC0);
    LCDToggleEN();
    LCDWaitLong(3);
}

void LCDDisplayOFF(void){
    /* Setup the R/W for writing , Initialize EN and RS to 0 */
    LCD_REG_SEL = 0; 
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0x80);
    LCDToggleEN();
    LCDWaitLong(3);
}

void LCDWriteChar(uint8_t ch){
  /*Write any specific char into LCD display*/
    LCD_EN = 0;
    LCD_REG_SEL = 1;
    LCDWrite4bits(ch);
    LCDToggleEN();
    LCDWrite4bits((uint8_t)(ch << 4));
    LCDToggleEN(); 
    LCDWaitShort(2);
}

void LCDWriteString(uint8_t x,uint8_t y, uint8_t *str){
    uint8_t len;
    uint8_t i;
    LCDGotoXY(x,y);
    len = (uint8_t)strlen(str);
    /* Check boundaries  */
    if (len > MAX_LCD_CHARS){
        len = MAX_LCD_CHARS;
    }
    for (i = 0; i < len; i++){
        LCDWriteChar(str[i]);
    }
    /* Clear the remaining unused line */
    //------------------------------
    for (; i < 16; i++){
        LCDWriteChar(' ');
    }
    //--------------------------------
}

void LCDWriteCommand(uint8_t cmd){
  /*It performs the erite command to be interoretated in LCD display*/
    LCD_REG_SEL = 0;
    LCD_EN = 0; 
    LCDWrite4bits(cmd);  /* cmd bits 4-7 */
    LCDToggleEN();
    LCDWrite4bits((uint8_t)(cmd << 4));  /* cmd bits 0-3 */
    LCDToggleEN();
    LCDWaitLong(5);
}

void LCDWrite4bits(uint8_t bdata){
  /**/
    if (bdata & 0x80){/*It allows to asign any pin into an specific port*/
        LCD_DATA4 = 1;//PTBD = PTBD | bdata; 
    }
    else{
        LCD_DATA4 = 0;//PTBD = PTBD & 0x7F; 
    }  
    if (bdata & 0x40){
        LCD_DATA3 = 1;//PTBD = PTBD | bdata; 
    }
      else{
        LCD_DATA3 = 0;//PTBD = PTBD & 0xBF; 
    }
    if (bdata & 0x20){
        LCD_DATA2 = 1;//PTBD = PTBD | bdata; 
    }
    else{
        LCD_DATA2 = 0;//PTBD = PTBD & 0xDF; 
    }
        
    if (bdata & 0x10){
        LCD_DATA1 = 1;//PTBD = PTBD | bdata; 
    }
    else{
        LCD_DATA1 = 0;//PTBD = PTBD & 0xEF; 
    }  
}

void LCDToggleEN(){
  /**/
  LCD_EN = 1;
  LCD_EN = 0;
}

void LCDEnableCursor(uint8_t x,uint8_t y){
  /**/
    LCDGotoXY(x,y);
    LCD_REG_SEL = 0;  
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xF0);
    LCDToggleEN();
    LCDWaitShort(5);
}

void LCDDisableCursor(void){
  /**/
    LCD_REG_SEL = 0;
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0xC0);
    LCDToggleEN();
    LCDWaitShort(5);
}

void LCDClearDisplay(void){
  /**/
    LCD_REG_SEL = 0;
    LCDWrite4bits(0x00);
    LCDToggleEN();
    LCDWaitShort(1);
    LCDWrite4bits(0x10);
    LCDToggleEN();
    LCDWaitLong(3);
}

void LCDWaitShort(uint8_t w ){
  /**/
    uint8_t x;
    uint8_t y;
    
    for ( y = 0; y < w; y++ ){
        for ( x = 0; x < 0xFF; x++ ){};
    }
}

void LCDWaitLong(uint16_t w){
  /**/
    uint16_t x;
    uint16_t y;
      
    for ( y = 0; y < w; y++ ){
        for ( x = 0; x < 0xFFF; x++ ){};
    }
}
