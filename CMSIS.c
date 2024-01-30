#include "stm32f1xx.h"


void Delay(uint32_t ms) {
    // Ch? theo th?i gian ms s? d?ng Systick
    uint32_t ticks =(SystemCoreClock / 1000);
    SysTick->LOAD = ticks - 1;
    SysTick->VAL = 0;
		SysTick->CTRL = 0x5;
    while (ms)
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0)
    {
      ms--;
    }
}
	SysTick->CTRL = 0;
	}

int main(void) {
    // Enable clock for GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure GPIOC Pin 13 as output push-pull (LED)
    GPIOC->CRH |= GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0;

    // Configure SysTick for 1ms interrupts
    SysTick_Config(SystemCoreClock / 1000);

    while (1) {
        // Your main application code here
GPIOC->ODR ^= GPIO_ODR_ODR13;
        // To create a delay of 1 second
        Delay(1000);
    }
}
