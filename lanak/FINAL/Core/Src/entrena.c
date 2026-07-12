/*
 * entrena.c
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 */

#include "global.h"
#include "periferikoak.h"

void entrena_init(void)
{
	sesioa.denbora_ms = 0;
	sesioa.split_s = 0.0;
	sesioa.paladak = 0;
	sesioa.geldi = 0;
	Disp_init();
	Acc_Init();
	Entrena();
}

void Entrena(void)
{
	LCD_Clear();
	Crono();
	Azel();
	Disp_update();

}

