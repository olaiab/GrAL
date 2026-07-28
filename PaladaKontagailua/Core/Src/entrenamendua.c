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
	if (egoera == ENTRENA)
	{
		if (htim->Instance == TIM16)
		{
			TICKFLAG = 1;
			tick++;
			tKont++;
			if (tKont == 50)
			{
				SEGFLAG = 1;
				tKont = 0;
			}
		}
	}
}

void ENT_Init(void)
{
	tick = 0;
	tKont = 0;
	TICKFLAG = 0;
	SEGFLAG = 0;

	sesioa.denboraMs = 0;
	sesioa.paladakMin = 0.0;
	sesioa.paladaKop = 0;

	paladak.azkenPalada = 0;
	paladak.prest = 1;
	LCD_Clear();
	LCD_SetCursor(0,0);
	entrena();
}

void entrena(void)
{
	if (TICKFLAG)
	{
		AZ_Tratatu();
		sesioa.denboraMs = tick * 20;
		TICKFLAG = 0;
	}
	if (SEGFLAG)
	{
		LCD_Eguneratu();
		SEGFLAG = 0;
	}
}

void LCD_Eguneratu()
{
	char denb[16]; // "00:00"

	int seg = sesioa.denboraMs / 1000;
	sprintf(denb, "%02d:%02d", seg / 60, seg % 60);
	//sprintf(denb, "%d",tick);
	LCD_SetCursor(0,0);
	LCD_PrintString(denb);

	char pal[16]; // "XX.X p/m"

	sprintf(pal, "%.1f p/m K=%lu", sesioa.paladakMin, sesioa.paladaKop);
	LCD_SetCursor(0,1);
	LCD_PrintString(pal);
}

void AZ_Init()
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
		BSP_LED_On(LED_BLUE);
		Error_Handler();
	}


	if (LIS2DW12_Init(&Acc) != LIS2DW12_OK)
	{
		//BSP_LED_On(LED_RED);
		Error_Handler();
	}

	LIS2DW12_ACC_Enable(&Acc);
}

void AZ_Tratatu()
{
	//	MAHAIAN GELDIRIK 4132 = 1G
	LIS2DW12_AxesRaw_t acc_raw;

	LIS2DW12_ACC_GetAxesRaw(&Acc, &acc_raw);	//lis2dw12.c

	float x = acc_raw.x;
	float y = acc_raw.y;
	float z = acc_raw.z;

	static float filtr = 0.0;
	static float batazbeste = 0.0;
	float alfa = 0.15;

	static float goiMuga = 1000.0; // muga neurtu gabe
	static float beheMuga = 700.0;
	static unsigned long denboraMin = 50; // 1s

	unsigned long orain;

	float mag = sqrt((float)x*(float)x + (float)y*(float)y + (float)z*(float)z); //magnitudea kalkulatu

	float bal = mag - 4132.0; // geldi dagoen balioa kendu

	// y(k) = alfa*x[k]+(1-alfa)*y[k-1]
	// Filtro LTI pasa-baja (PDSI) (5. gaia)
	filtr = (alfa * bal) + ((1.0 - alfa) * filtr);

	if (batazbeste == 0.0f)
	{
	    batazbeste = fabsf(filtr);
	}
	else
	{
	    batazbeste = 0.98f * batazbeste + 0.02f * fabsf(filtr);
	}

	// muga dinamikoak
	batazbeste = 0.98f * batazbeste + 0.02f * fabsf(filtr);

	goiMuga  = 1.4f * batazbeste;
	beheMuga = 1.0f * batazbeste;

	orain = tick;

	if (paladak.prest) {
	    if (filtr > goiMuga && (orain - paladak.azkenPalada) > denboraMin) {

	    	if (paladak.azkenPalada != 0) sesioa.paladakMin = (3000.0f) / (orain - paladak.azkenPalada);
	        sesioa.paladaKop++;
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
