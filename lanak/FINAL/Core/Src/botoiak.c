/*
 * Botoien konfugurazioa
 */

#include "global.h"

#include "stm32wlxx_nucleo.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_Pin)
	{
		if (HAL_GPIO_ReadPin(GPIOA, B1_Pin) == GPIO_PIN_RESET)
		{
			noizSakatu = HAL_GetTick();
		}

		else
		{
			noizAskatu = HAL_GetTick();

			if (noizAskatu - noizSakatu < MUGA)
			{
				B1FLAG = 2;
			}
			else B1FLAG = 1;
		}
	}
}

void BSP_PB_Callback(Button_TypeDef Button)
{
	switch (Button)
	{
		case BUTTON_SW2:
			B2FLAG = 1;
			break;

		case BUTTON_SW3:
			B3FLAG = 1;
			break;

		default:
			break;
	}
}

void BTK_Tratatu(void)
{
	if (B1FLAG == 1) // Botoia mantendu
	{
		B1FLAG = 0;
		B1_Mantendu();
	}

	if (B1FLAG == 2) // Botoia sakatu
	{
		B1FLAG = 0;
		B1_Sakatu();
	}

	if (B2FLAG)
	{
		B2FLAG = 0;
		B2_Sakatu();
	}

	if (B3FLAG)
	{
		B3FLAG = 0;
		B3_Sakatu();
	}
}

void B2_Sakatu(void)
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_PrintString("B2 sakatuta");
}

void B1_Mantendu(void)
{
    if (egoera == PAUSA)
    {
    	egoera = IDLE;
    }
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_PrintString(egoerak_str[egoera]);
}

void B1_Sakatu(void)
{
    switch (egoera)
    {
        case IDLE:
        	ENT_Init();
            egoera = ENTRENA;
            break;
        case ENTRENA:
            egoera = PAUSA;
            break;
        case PAUSA:
            egoera = ENTRENA;
            break;
        default:
            break;
    }
    LCD_Clear();
    LCD_SetCursor(0,0);
    if (egoera != ENTRENA) LCD_PrintString(egoerak_str[egoera]);
}

void B3_Sakatu(void)
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_PrintString("B3 sakatuta");
}
