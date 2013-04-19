#include "stm32f0xx_conf.h"
#include "common.h"
//#include <stdio.h>

void SysTick_Handler(void) {
  static uint16_t tick = 0;

  switch (tick++) {
  	case 100:
  		tick = 0;
  		//GPIOC->ODR ^= (1 << 8);
  		break;
  }
}

char msg[10];
int main(void)
{

	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 	// enable the clock to GPIOC
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	GPIOC->MODER = GPIO_MODER_MODER8_0;
    /* szybkosc */
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
    /* pullup */
   //GPIOC->PUPDR |= 
	GPIOC->ODR |= (1<<8);
	
	USART1_Init();
	usart_print("!\r\n");
	// Timer TIM3 - 32bit
	TIM3->PSC = 1000;
	TIM3->ARR = 10000;
	//TIM3->CR1 |= TIM_CR1_DIR; // down
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM3_IRQn);

	SysTick_Config(SystemCoreClock/100);

	while(1);

}
void TIM3_IRQHandler(void) {
	if (TIM3->SR & TIM_SR_UIF ) {
    // clear interrupt
    TIM3->SR &= ~TIM_SR_UIF;
    GPIOC->ODR ^= (1<<8);
	}

}
