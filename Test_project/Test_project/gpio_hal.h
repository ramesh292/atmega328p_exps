/*
 * gpio_hal.h
 *
 * Created: 30-06-2023 14:12:19
 *  Author: ramesh
 */ 


#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

typedef enum{
	e_input,
	e_output,
}pin_mode_t;


typedef enum{
	e_low,
	e_high,
}pin_state_t;

void init_pin(uint8_t pin, pin_mode_t mode);

void set_pin(uint8_t pin, pin_state_t state);

pin_state_t get_pin(uint8_t pin);



#endif /* GPIO_HAL_H_ */