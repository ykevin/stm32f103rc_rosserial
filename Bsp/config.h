#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "ring_buffer.h"
#include "millisecondtimer.h"

/** --------Serial Config-------- **/
typedef enum {
	SERIAL1 = 0,
	SERIAL2 = 1,
	SERIAL3 = 2,
	SERIAL_END = 3
}Serial_TypeDef; 

#define SERIALn							3

#define RIKI_SERIAL1					USART1
#define RIKI_SERIAL1_IRQ				USART1_IRQn
#define RIKI_SERIAL1_CLK             	RCC_APB2Periph_USART1
#define RIKI_SERIAL1_GPIO_CLK           RCC_APB2Periph_GPIOA
#define RIKI_SERIAL1_GPIO_PORT          GPIOA
#define RIKI_SERIAL1_TX_PIN            	GPIO_Pin_9
#define RIKI_SERIAL1_RX_PIN             GPIO_Pin_10
#define RIKI_SERIAL1_NVIC				1

#define RIKI_SERIAL2					USART2
#define RIKI_SERIAL2_IRQ				USART2_IRQn
#define RIKI_SERIAL2_CLK             	RCC_APB1Periph_USART2
#define RIKI_SERIAL2_GPIO_CLK        	RCC_APB2Periph_GPIOA
#define RIKI_SERIAL2_GPIO_PORT      	GPIOA
#define RIKI_SERIAL2_TX_PIN            	GPIO_Pin_2
#define RIKI_SERIAL2_RX_PIN             GPIO_Pin_3
#define RIKI_SERIAL2_NVIC				2

#define RIKI_SERIAL3					USART3
#define RIKI_SERIAL3_IRQ				USART3_IRQn
#define RIKI_SERIAL3_CLK             	RCC_APB1Periph_USART3
#define RIKI_SERIAL3_GPIO_CLK        	RCC_APB2Periph_GPIOB
#define RIKI_SERIAL3_GPIO_PORT      	GPIOB
#define RIKI_SERIAL3_TX_PIN            	GPIO_Pin_10
#define RIKI_SERIAL3_RX_PIN             GPIO_Pin_11
#define RIKI_SERIAL3_NVIC				3

#define TXBUF_SIZE        1024                     
#define RXBUF_SIZE        1024


/** LED config **/
typedef enum {
	ON = 0,
	OFF = 1,
	END = 2,
}Status_TypeDef;

#define RIKI_LED_PIN				GPIO_Pin_1
#define RIKI_LED_GPIO_PORT			GPIOC
#define RIKI_LED_GPIO_CLK			RCC_APB2Periph_GPIOC


/** volt adc config **/
#define ADC1_DR_ADDRESS 			((u32)0x4001244C)
#define RIKI_BATTERY_PIN			GPIO_Pin_0
#define RIKI_BATTERY_GPIO_PORT		GPIOC
#define RIKI_BATTERY_GPIO_CLK		RCC_APB2Periph_GPIOC
#define RIKI_BATTERY_ADC_CLK		RCC_APB2Periph_ADC1
#define RIKI_BATTERY_DMA_CLK		RCC_AHBPeriph_DMA1

#endif // _CONFIG_H_

#ifdef __cplusplus
}
#endif
