#include "stm32f7xx.h"

void led_on(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}


void led_off(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void gpio_init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init_struct = {
		.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_PULLUP,
		.Speed = GPIO_SPEED_HIGH
	};

	HAL_GPIO_Init(GPIOB, &gpio_init_struct);

	led_off();
}

void delay(uint32_t count)
{
        while(count--) {
		__asm volatile("nop");
	}
}

int main(void)
{
	gpio_init();

	int state = 1;

	while(1) {
		if(state == 1) {
			led_on();
		} else {
			led_off();
		}

		delay(1000000);

		state = (state + 1) % 2;
	}

	return 0;
}
