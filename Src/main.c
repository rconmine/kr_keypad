#include "keypad.h"
#include "stm32f4xx_hal.h"

int main() {
  // Keypad init
  Keypad* keypad = Keypad_Init();
  if (!keypad) {
    while (1) {
      __NOP();
    }
  }

  // LED init
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_5;
  gpio.Mode = GPIO_MODE_OUTPUT_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &gpio);

  int pinState = 0;

  while (1) {
    if (Keypad_GetState(keypad, KeyStartStop) == Clicked) {
      if (pinState) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
      }
      pinState = !pinState;
    }
  }
}
