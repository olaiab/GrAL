/*
 * Botoien konfugurazioa
 */

#include "buttons.h"
#include "main.h"
#include "lcd.h"
#include "global.h"

#include "stm32wlxx_nucleo.h"

void BSP_PB_Callback(Button_TypeDef Button)
{
	switch (Button)
	{
		case BUTTON_SW1:
			B1FLAG = 1;
			break;

		case BUTTON_SW2:
			if (BSP_PB_GetState(Button) == 0) // Sakatuta
			{
				noizsakatu = HAL_GetTick();
				sakatutadago = 1;
			}

			else
			{
				if ((HAL_GetTick() - noizsakatu) < MUGA)
				{
					B2FLAG = 2;
					sakatutadago = 0;
				}
			}
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
	if (B1FLAG)
	{
		B1FLAG = 0;
		B1Sakatu();
	}

	static uint8_t botoiatratatuta = 0; //igual botoia tratatu ondoren mantenduta jarraitzen du
	if (sakatutadago && B2FLAG == 0 && !botoiatratatuta)
	{
		if ((HAL_GetTick() - noizsakatu) >= MUGA) // Asko sakatu
		{
			B2FLAG = 1;
			botoiatratatuta = 1;
		}
	}

	if (B2FLAG == 1) // Botoia mantendu
	{
		B2FLAG = 0;
		B2Mantendu();
	}

	if (B2FLAG == 2) // Botoia sakatu
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

void B1Sakatu(void)
{
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_PrintString("B1 sakatuta");
}

void B2Mantendu(void)
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

void B2Sakatu(void)
{
    switch (egoera)
    {
        case IDLE:
            //entrena_hasi();
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
