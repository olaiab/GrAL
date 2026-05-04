/*
 * timers.h
 *
 *  Created on: 27 mar 2026
 *      Author: olaia
 */

#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

//Erregistroak
#define RCC		0x58000000 //p74
#define TIM17	0x40014800 //p75

//ABP2
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC + 0x060)) //p328

//TIM17
#define TIM17_PSC 	(*(volatile uint32_t *)(TIM17 + 0x28)) //p922
#define TIM17_ARR	(*(volatile uint32_t *)(TIM17 + 0x2C)) //p922
#define TIM17_CR1	(*(volatile uint32_t *)(TIM17 + 0x00)) //p911
#define TIM17_DIER 	(*(volatile uint32_t *)(TIM17 + 0x0C)) //p913
#define TIM17_EGR 	(*(volatile uint32_t *)(TIM17 + 0x14)) //p915
#define TIM17_SR	(*(volatile uint32_t *)(TIM17 + 0x10)) //p914

#endif /* TIMERS_H_ */
