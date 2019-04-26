 /**********************************************************
 Company: Dinamica y Desarrollo
 Diseñado por: Juan Sebastian Rincon Manrique
 Fecha: 12/09/2017
 Descripcion: se crean las macros para una implementacion
              versatil en el uso de los pines para
              un LCD 16x2 YB1602A
 ***********************************************************

 *        __________________________________________________
 *       |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |    
 *       |Vss|Vdd|Vo|RS|RW|EN|D0|D1|D2|D3|D4|D5|D6|D7|A |K |
 *       |   |   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   
 *        \                                                /
 *          \                                            /
 *            \                                        /
 *              \____________________________________/__________________
 *             |  \ _______________________________/                    |
 *             |   | | | | | | | | | | | | | | | | |                    |
 *             |   |*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|                    |
 *             |   |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|                    |
 *             |   __________________________________________________   |
 *             |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |  | | || || || || || || || || || || || || || || || | |  |
 *             |  | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |  |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |  | | || || || || || || || || || || || || || || || | |  |
 *             |  | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |  |__________________________________________________|  |
 *             |________________________________________________________|
 *
 *              ____________________________________________________________
 *             |       __________________________________________________   |
 *             |      |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |      | | || || || || || || || || || || || || || || || | |  |
 *             |      | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |      |  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  |  |
 *             |      | | || || || || || || || || || || || || || || || | |  |
 *             |      | |_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_| |  |
 *             |      |__________________________________________________|  |
 *             |____________________________________________________________|
 *
 *
 * 
 */
 
/* File: LCD.h */
#ifndef _LCD_H
#define _LCD_H

#include <iostm8s003k3.h>
#include <DataType.h>

/***********************************************
LCD Settings
***********************************************/

//DATA
#define LCD_REG_SEL       PB_ODR_ODR7
#define LCD_EN            PB_ODR_ODR6

/* Data bits are 4-7 */
#define LCD_DATA1         PD_ODR_ODR0
#define LCD_DATA2         PD_ODR_ODR2
#define LCD_DATA3         PD_ODR_ODR3
#define LCD_DATA4         PD_ODR_ODR7
#define LCD_BACKLIGTH 	  PC_ODR_ODR7

//DATADIRECTION
#define LCD_REG_SELDD       PB_DDR_DDR7
#define LCD_ENDD            PB_DDR_DDR6
#define LCD_DATA1DD         PD_DDR_DDR0
#define LCD_DATA2DD         PD_DDR_DDR2
#define LCD_DATA3DD         PD_DDR_DDR3
#define LCD_DATA4DD         PD_DDR_DDR7
#define LCD_BACKLIGTHD 	    PC_DDR_DDR7

//CONTROL REGISTERS 1 (Push pull mode)
#define LCD_REG_SELCR1       PB_CR1_C17
#define LCD_ENCR1            PB_CR1_C16
#define LCD_DATA1CR1         PD_CR1_C10
#define LCD_DATA2CR1         PD_CR1_C12
#define LCD_DATA3CR1         PD_CR1_C13
#define LCD_DATA4CR1         PD_CR1_C17
#define LCD_BACKLIGTHCR1     PC_CR1_C17
                              
#define LCD_INIT_MACRO  LCD_REG_SELDD=1;LCD_ENDD=1;LCD_DATA1DD=1;LCD_DATA2DD=1;LCD_DATA3DD=1;LCD_DATA4DD=1; LCD_BACKLIGTHD=1; LCD_REG_SELCR1=1; LCD_ENCR1=1; LCD_DATA1CR1=1; LCD_DATA2CR1=1; LCD_DATA3CR1=1; LCD_DATA4CR1=1; LCD_BACKLIGTHCR1=1 

#define MAX_LCD_CHARS 16  


/**************************************************
* Function headers
**************************************************/

void LCDWaitLong(uint16_t w);
void LCDWaitShort(uint8_t w);
void LCDToggleEN(void);
void LCD_Init(void);
void LCDWrite4bits(uint8_t bdata);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDClearDisplay(void);
void LCDEnableCursor(uint8_t x,uint8_t y);
void LCDDisableCursor(void);
void LCDWriteString(uint8_t x,uint8_t y, uint8_t *str);
void LCDWriteChar(uint8_t ch);
void LCDDisableBackLigth(void);
void LCDEnableBackLigth(void);
void LCDClearDisplayON(void);
void LCDClearDisplayOFF(void);

#endif
