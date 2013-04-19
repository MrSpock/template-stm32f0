#include "stm32f0xx_conf.h"
#include "common.h"

USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
GPIO_InitTypeDef PORT;

void USART1_Init(void) {

	// enable USART1 clock
	RCC->APB2ENR |= RCC_APB2Periph_USART1;
	// enable GPIOA clock for USART output
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// enable alternate function (USART1 for PA9 & PA10)
	// PA9 & PA10 AF1 mode
	GPIOA->AFR[1] |= (1<<4 | 1<<8);
	// set mode type as alternate function
	GPIOA->MODER |= (GPIO_MODER_MODER9_1|GPIO_MODER_MODER10_1);
	// way to heavy to make this directly on registers :)
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStruct);

//	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPriority = 3;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStruct);
	NVIC_EnableIRQ(USART1_IRQn);
	//USART_Cmd(USART1,ENABLE);
	USART1->CR1 |= USART_CR1_UE;
}
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->ISR & USART_FLAG_TXE) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}

void usart_print(volatile char *s) {
	USART_puts(DEFAULT_USART,s);
}
