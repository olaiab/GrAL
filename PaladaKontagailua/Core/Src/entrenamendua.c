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
	paladak.filtr = 0.0;
	paladak.batazbeste = 0.0;
	paladak.goiMuga = 1000.0; // muga neurtu gabe
	paladak.beheMuga = 400.0;

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

	sprintf(pal, "%04.1f p/m K=%lu", sesioa.paladakMin, sesioa.paladaKop);
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

 	float INDAR_MIN = 500.0f;
	float x = acc_raw.x;
	float y = acc_raw.y;
	float z = acc_raw.z;

	float alfa = 0.15;
	unsigned long denboraMin = 50; // 1s
	unsigned long orain;

	float mag = sqrt((float)x*(float)x + (float)y*(float)y + (float)z*(float)z); //magnitudea kalkulatu

	float bal = mag - 4152.0; // geldi dagoen balioa kendu

	// y(k) = alfa*x[k]+(1-alfa)*y[k-1]
	// Filtro LTI pasa-baja (PDSI) (5. gaia)
	paladak.filtr = (alfa * bal) + ((1.0 - alfa) * paladak.filtr);

	if (paladak.batazbeste == 0.0f)
	{
		paladak.batazbeste = fabsf(paladak.filtr);
	}
	else
	{
		paladak.batazbeste = 0.98f * paladak.batazbeste + 0.02f * fabsf(paladak.filtr);
	}

	paladak.goiMuga  = 1.4f * paladak.batazbeste;
	paladak.beheMuga = 1.0f * paladak.batazbeste;

	orain = tick;

	/*
	char msg[64];
	int len = snprintf(msg, sizeof(msg), "F = %.2f\r\n", paladak.batazbeste);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, len, 100);
	*/
	if (paladak.prest) {
	    if (paladak.filtr > INDAR_MIN && paladak.filtr > paladak.goiMuga && (orain - paladak.azkenPalada) > denboraMin) {
	    	if (paladak.azkenPalada != 0) sesioa.paladakMin = (3000.0f) / (orain - paladak.azkenPalada);
	        sesioa.paladaKop++;
	        paladak.azkenPalada = orain;
	        paladak.prest = 0;
	    }
	}
	else {
	    if (paladak.filtr < paladak.beheMuga) {
	        paladak.prest = 1;
	    }
	}
}
