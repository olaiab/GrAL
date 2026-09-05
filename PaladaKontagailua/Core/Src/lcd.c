/* lcd.c */
#include "lcd.h"
#include <string.h>

static void lcd_pulse_enable(void)
{
	HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET); //Enable
    HAL_Delay(1); //Irakurtzeko denbora
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET); //Disable
    HAL_Delay(1);
}

static void lcd_send_halfbyte(uint8_t info)
{
	// Bita 0 bada GPIO_PIN_RESET, besteña _SET
	// (info >> 0) & 1 bita konprobatzen du, ?_:_ if else da
	if (((info >> 0) & 1) == 1) HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, GPIO_PIN_RESET);

	if (((info >> 1) & 1) == 1) HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, GPIO_PIN_RESET);

	if (((info >> 2) & 1) == 1) HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, GPIO_PIN_RESET);

	if (((info >> 3) & 1) == 1) HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, GPIO_PIN_RESET);

    lcd_pulse_enable();
}

// byte bat bidali; lau bit ditugunez, bi alditab bidali
static void lcd_send_byte(uint8_t byte, uint8_t rs)
{
	if (rs == 1) HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);

	lcd_send_halfbyte(byte >> 4);   // lehenengo erdia
	lcd_send_halfbyte(byte & 0x0F); // bigarren erdia
}

#define lcd_cmd(c)  lcd_send_byte((c), 0)
#define lcd_data(d) lcd_send_byte((d), 1)

// hd44780.pdf p46
void LCD_Init(void)
{
    HAL_Delay(50); // "Wait for more than 40 ms after VCC rises to 2.7 V"

    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

    lcd_send_halfbyte(0x3); HAL_Delay(5); //"Wait for more than 4.1 ms"
    lcd_send_halfbyte(0x3); HAL_Delay(1); //"Wait for more than 100 μs"
    lcd_send_halfbyte(0x3); HAL_Delay(1);

    lcd_send_halfbyte(0x2); HAL_Delay(1);

    lcd_cmd(0x28);	//"function set (Set interface to be 4 bits long."

    lcd_cmd(0x08);	//"Display off"

    lcd_cmd(0x01); HAL_Delay(3);// "Display clear"

    lcd_cmd(0x06); // "Entry mode set"

    lcd_cmd(0x0C); //p23
}

void LCD_Clear(void)
{
    lcd_cmd(0x01);
    HAL_Delay(3);
}

/*
 * col: 0-15
 * row: 0-1 (0x00 edo 0x40)
 * 0x80 komandoa kurtsorea mugitzeko +
 */
void LCD_SetCursor(uint8_t col, uint8_t row)
{
    static const uint8_t row_offsets[] = { 0x00, 0x40 };
    lcd_cmd(0x80 | (col + row_offsets[row & 0x01]));
}

void LCD_PrintChar(char c)
{
    lcd_data((uint8_t)c);
}

void LCD_PrintString(const char *str)
{
    while (*str)
        lcd_data((uint8_t)*str++);
}

