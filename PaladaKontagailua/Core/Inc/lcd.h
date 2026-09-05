#ifndef LCD_H
#define LCD_H

#include "stm32wlxx_hal.h"


#define LCD_RS_PORT   GPIOB
#define LCD_RS_PIN    GPIO_PIN_12

#define LCD_EN_PORT   GPIOB
#define LCD_EN_PIN    GPIO_PIN_3

#define LCD_D4_PORT   GPIOB
#define LCD_D4_PIN    GPIO_PIN_5

#define LCD_D5_PORT   GPIOB
#define LCD_D5_PIN    GPIO_PIN_8

#define LCD_D6_PORT   GPIOB
#define LCD_D6_PIN    GPIO_PIN_10

#define LCD_D7_PORT   GPIOC
#define LCD_D7_PIN    GPIO_PIN_1

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_PrintString(const char *str);
void LCD_PrintChar(char c);

#endif /* LCD_H */
