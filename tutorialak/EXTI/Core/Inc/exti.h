/*
 * exti.h
 *
 *  Created on: 02 may 2026
 *      Author: olaia
 */

#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

//Erregistroak
#define RCC			0x58000000 //p74
#define SYSCFG		0X40010000 //p75
#define EXTI0		0x58000800 //p75
#define NVIC_ISER0  (*(volatile uint32_t *)(0xE000E100))	//beste manuala, cortex-m4
//ABP2
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC + 0x060)) //p328

//SYSCFG
#define SYSCFG_EXTICR1 	(*(volatile uint32_t *)(SYSCFG + 0x008)) //p436 eta p427
#define EXTI_CnIMR1		(*(volatile uint32_t *)(EXTI + 0x080)) //p512
#define EXTI_RTSR1		(*(volatile uint32_t *)(EXTI + 0x000)) //P506
#define EXTI_PR1		(*(volatile uint32_t *)(EXTI + 0x00C)) //P509

#define RCC_AHB2ENR		(*(volatile uint32_t *)(EXTI + 0x04C))

#endif /* EXTI_H_ */
