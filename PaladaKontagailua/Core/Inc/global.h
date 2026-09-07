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
#include "stm32wlxx_hal_i2c.h"

#include "entrenamendua.h"
#include "main.h"
#include "botoiak.h"
#include "lcd.h"

#define MUGA 2000 // 2seg

// Egoerak
typedef enum{
    IDLE = 0,
    ENTRENA,
    PAUSA
} egoerak;

extern volatile egoerak egoera;

extern const char *egoerak_str[];

// Botoiak
extern volatile uint8_t sakatutaDago;
extern volatile uint32_t noizSakatu;
extern volatile uint32_t noizAskatu;

extern volatile uint8_t B1FLAG;
extern volatile uint8_t B2FLAG;
extern volatile uint8_t B3FLAG;

// Datuak gordetzeko (pausa -> berrezarri)
typedef struct{
    uint32_t denboraMs;
    float paladakMin;
	uint32_t paladaKop;
} SesioDatuak;

extern SesioDatuak sesioa;

// Timerrak
extern volatile uint8_t TICKFLAG;
extern volatile uint8_t SEGFLAG;
extern volatile uint32_t tick;
extern volatile uint32_t tKont;

// Azel
extern LIS2DW12_IO_t io_ctx;
extern LIS2DW12_Object_t Acc;

typedef struct{
	uint32_t azkenPalada;
	int prest;
	float filtr;
	float batazbeste;
	float goiMuga;
	float beheMuga;
}Paladak;

extern Paladak paladak;

extern UART_HandleTypeDef huart2;

#endif /* INC_GLOBAL_H_ */
