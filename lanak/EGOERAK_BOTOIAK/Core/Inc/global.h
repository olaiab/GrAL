/*
 * defines.h
 *
 *  Created on: 23 may 2026
 *      Author: olaia
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stdint.h"

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

extern volatile uint8_t B1FLAG;
extern volatile uint8_t B2FLAG;
extern volatile uint8_t B3FLAG;



#endif /* INC_GLOBAL_H_ */
