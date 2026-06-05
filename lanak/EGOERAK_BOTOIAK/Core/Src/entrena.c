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
	sesioa.distantzia_m = 0.0;
	sesioa.bb_abiadura_km = 0.0;
	sesioa.split_s = 0.0;
	sesioa.paladak = 0;
	sesioa.geldi = 0;
	Disp_init();
	Entrena();
}

void entrena_pausa(void)
{

}

void Entrena(void)
{
	while (!PAUSA)
	{
		Crono();
		// GPS
		// Azel.
		Disp_update();
	}
}

void entrena_gorde(void)
{

}
