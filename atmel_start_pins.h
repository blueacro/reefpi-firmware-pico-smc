/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD10 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define VINSENSE GPIO(GPIO_PORTA, 5)
#define BUTTON GPIO(GPIO_PORTA, 8)
#define VEN GPIO(GPIO_PORTA, 10)
#define PA14 GPIO(GPIO_PORTA, 14)
#define PA15 GPIO(GPIO_PORTA, 15)
#define PWM0 GPIO(GPIO_PORTA, 16)
#define PWM1 GPIO(GPIO_PORTA, 17)
#define LR GPIO(GPIO_PORTA, 22)
#define LB GPIO(GPIO_PORTA, 23)
#define LG GPIO(GPIO_PORTA, 27)

#endif // ATMEL_START_PINS_H_INCLUDED
