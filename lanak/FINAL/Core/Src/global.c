/*
 * global.c
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 */

#include "global.h"

// Botoiak

volatile uint8_t B1FLAG = 0;
volatile uint8_t B2FLAG = 0;
volatile uint8_t B3FLAG = 0;

volatile uint8_t sakatutaDago = 0;
volatile uint32_t noizSakatu = 0;
volatile uint32_t noizAskatu = 0;

volatile egoerak egoera = IDLE;

const char *egoerak_str[] = {
    "IDLE",
    "ENTRENA",
    "PAUSA"
};

volatile uint8_t TICKFLAG = 0;
volatile uint8_t SEGFLAG = 0;

volatile uint32_t tick = 0;
volatile uint32_t tKont = 0;

SesioDatuak sesioa;

Paladak paladak;

LIS2DW12_IO_t io_ctx;
LIS2DW12_Object_t Acc;
