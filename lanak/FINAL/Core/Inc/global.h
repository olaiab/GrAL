/*
 * defines.h
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stdint.h"
#include "stdio.h"
#include "lis2dw12.h"
#include "stm32wlxx_nucleo_bus.h"
#include "math.h"

#include "main.h"
#include "botoiak.h"
#include "entrena.h"
#include "lcd.h"
#include "periferikoak.h"

#define MUGA 2000 // 2seg

// Egoerak
typedef enum{
    IDLE = 0,
    ENTRENA,
    PAUSA,
    GORDE
} egoerak;

extern volatile egoerak egoera;

extern const char *egoerak_str[];

// Botoiak
extern volatile uint8_t sakatutadago;
extern volatile uint32_t noizsakatu;
extern volatile uint32_t noizaskatu;

extern volatile uint8_t B1FLAG;
extern volatile uint8_t B2FLAG;
extern volatile uint8_t B3FLAG;

// Datuak gordetzeko (pausa -> berrezarri)
typedef struct{
    uint32_t denbora_ms;
    float split_s;
    int paladak;
    uint8_t geldi;
} SesioDatuak;

extern SesioDatuak sesioa;

// Timerrak
extern volatile uint8_t CRONOFLAG;
extern volatile uint8_t ENTRENAFLAG;
extern volatile uint32_t tick;

// Azel
extern LIS2DW12_IO_t io_ctx;
extern LIS2DW12_Object_t Acc;

typedef struct{
	uint32_t azkenPalada;
	int prest;
	uint32_t paladaKop;
	float val;
}Paladak;

extern Paladak paladak;

#endif /* INC_GLOBAL_H_ */
