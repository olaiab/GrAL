/*
 * Botoien konfugurazioa
 */

#include <botoiak.h>
#include "main.h"
#include "lcd.h"
#include "global.h"

#include "stm32wlxx_nucleo.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_Pin)
	{
		if (HAL_GPIO_ReadPin(GPIOA, B1_Pin) == GPIO_PIN_RESET)
		{
			noizsakatu = HAL_GetTick();
		}

		else
		{
			noizaskatu = HAL_GetTick();

			if (noizaskatu - noizsakatu < MUGA)
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

void tratatuBotoiak(void)
{
	if (B1FLAG == 1) // Botoia mantendu
	{
		B1FLAG = 0;
		B1Mantendu();
	}

	if (B1FLAG == 2) // Botoia sakatu
	{
		B1FLAG = 0;
		B1Sakatu();
	}

	if (B2FLAG)
	{
		B2FLAG = 0;
		B2Sakatu();
	}

	if (B3FLAG)
	{
		B3FLAG = 0;
		B3Sakatu();
	}
}

void B2Sakatu(void)
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_PrintString("B2 sakatuta");
}

void B1Mantendu(void)
{
    switch (egoera)
    {
        case PAUSA:
            //gorde_pantaila();
            egoera = GORDE;
            break;
        default:
            break;
    }
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_PrintString(egoerak_str[egoera]);
}

void B1Sakatu(void)
{
    switch (egoera)
    {
        case IDLE:
            entrena_init();
            egoera = ENTRENA;
            break;
        case ENTRENA:
            //entrena_pausa();
            egoera = PAUSA;
            break;
        case PAUSA:
            //entrena(sesioa);
            egoera = ENTRENA;
            break;
        case GORDE:
            //entrena_gorde();
            egoera = IDLE;
            break;
        default:
            break;
    }
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_PrintString(egoerak_str[egoera]);
}

void B3Sakatu(void)
{
	/*
	if (!ARGIA)
	{
		//argia_piztu();
	}
	else argia_itzali();
	*/
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_PrintString("B3 sakatuta");
}
