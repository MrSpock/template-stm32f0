/*
 * common.h
 *
 *  Created on: Apr 18, 2013
 *      Author: spock
 */

#ifndef COMMON_H_
#define COMMON_H_

#define DEFAULT_USART USART1


// function prototypes
void USART1_Init(void);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void usart_print(volatile char *s);

#endif /* COMMON_H_ */
