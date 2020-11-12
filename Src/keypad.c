#include "keypad.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"

/// @ingroup Keypad
/// @{

struct Keypad {
  KeyState keystates[KeyButtons_SIZE];
  uint8_t timePressed[KeyButtons_SIZE];
};

Keypad g_Keypad;

Keypad* Keypad_Init() {
  // TODO! Init
	__HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_1;
  gpio.Mode = GPIO_MODE_IT_FALLING;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &gpio);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
  return &g_Keypad;
}

void EXTI1_IRQHandler(void){
	EXTI->PR = EXTI_PR_PR1;
	g_Keypad.keystates[KeyStartStop] = Clicked;
}

KeyState Keypad_GetState(Keypad* keypad, KeyButtons key) { 
	if (keypad->keystates[key] == Clicked && HAL_GetTick() - keypad->timePressed[key] >= 10000) {
		keypad->timePressed[KeyStartStop] = HAL_GetTick();
		keypad->keystates[key] = Unpressed;
		return Clicked;
	}
	return Unpressed;
}

/// @}
