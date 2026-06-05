/*
 * sentsoreak.c
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 *
 *  Periferikoen funtzioak
 */

#include "global.h"
#include "lcd.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM16)
	    {
	        CRONOFLAG = 1;
	    }
}

void Crono(void)
{
	if (CRONOFLAG)
	{
		sesioa.denbora_ms += 10;
		CRONOFLAG = 0;
	}
}

void Disp_init(void)
{
	LCD_Init();
	LCD_SetCursor(0,8);
	LCD_PrintChar("s");
}

void Disp_update()
{
	char denb[10]; // "00:00.00"

	sprintf(denb, "%02lu:%02lu.%02lu",
			sesioa.denbora_ms/60000, (sesioa.denbora_ms / 1000) % 60, sesioa.denbora_ms % 1000);
	LCD_SetCursor(0,0);
	LCD_PrintString(denb);

}
