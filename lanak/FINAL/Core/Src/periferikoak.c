/*
 * periferikoak.c
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 *
 *  Periferikoen funtzioak
 */

#include "global.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM16)
	    {
	        CRONOFLAG = 1;
	        tick++;
	    }
}

void Crono(void)
{
	if (CRONOFLAG)
	{
		sesioa.denbora_ms = tick * 20;
		CRONOFLAG = 0;
	}
}

void Disp_init(void)
{
	LCD_Init();
	LCD_SetCursor(0,0);
}

void Disp_update()
{
	char denb[16]; // "00:00"

	int seg = sesioa.denbora_ms / 1000;
	sprintf(denb, "%02d:%02d", seg / 60, seg % 60);
	//sprintf(denb, "%d",tick);
	LCD_SetCursor(0,0);
	LCD_PrintString(denb);

	char pal[16]; // "XX p/m"

	//sprintf(pal, "%d p/m", sesioa.paladak);
	//sprintf(pal, "v=%d       ", (int)paladak.val);
	sprintf(pal, "%d p/m kop=%lu p=%d", sesioa.paladak, paladak.paladaKop, paladak.prest);
	//sprintf(pal, "%d ds", sesioa.denbora_ms);
	LCD_SetCursor(0,1);
	LCD_PrintString(pal);
}

void Acc_Init()
{
	io_ctx.Init     = BSP_I2C2_Init;
	io_ctx.DeInit   = BSP_I2C2_DeInit;
	io_ctx.BusType  = LIS2DW12_I2C_BUS;
	io_ctx.Address  = 0x32;
	io_ctx.WriteReg = BSP_I2C2_WriteReg;
	io_ctx.ReadReg  = BSP_I2C2_ReadReg;
	io_ctx.GetTick  = HAL_GetTick;

	if (LIS2DW12_RegisterBusIO(&Acc, &io_ctx) != LIS2DW12_OK)
	{
		Error_Handler();
	}

	if (LIS2DW12_Init(&Acc) != LIS2DW12_OK)
	{
		Error_Handler();
	}

	LIS2DW12_ACC_Enable(&Acc);
}

void Azel()
{
	//	MAHAIAN GELDIRIK 4132 = 1G
	LIS2DW12_AxesRaw_t acc_raw;

	LIS2DW12_ACC_GetAxesRaw(&Acc, &acc_raw);	//lis2dw12.c

	float x = acc_raw.x;
	float y = acc_raw.y;
	float z = acc_raw.z;

	// ???
	static float filtr = 0.0;
	float alfa = 0.15; // Filtro de suavizado

	static float goiMuga = 1000.0; // muga neurtu gabe
	static float beheMuga = 700.0;
	static unsigned long denboraMin = 50; // 1s

	unsigned long orain;

	float mag = sqrt((float)x*(float)x + (float)y*(float)y + (float)z*(float)z); //magnitudea kalkulatu

	float bal = mag - 4132.0; // geldi dagoen balioa kendu

	filtr = (alfa * bal) + ((1.0 - alfa) * filtr);
	orain = tick;

	/*
	char a[20];
	LCD_SetCursor(0, 0);
	sprintf(a, " vs=%d      ", (int)valorSuavizado);
	//LCD_Clear();
	LCD_PrintString(a);
	*/

	if (paladak.prest) {
	    if (filtr > goiMuga && (orain - paladak.azkenPalada) > denboraMin) {

	    	if (paladak.azkenPalada != 0) sesioa.paladak = (3000) / (orain - paladak.azkenPalada);
	        paladak.paladaKop++;
	        paladak.azkenPalada = orain;
	        paladak.prest = 0;
	    }
	}
	else {
	    if (filtr < beheMuga) {
	        paladak.prest = 1;
	    }
	}
}
