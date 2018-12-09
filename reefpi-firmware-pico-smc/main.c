#include <atmel_start.h>

static struct io_descriptor *io;

#define STATUS_BYTE_BEEP (1<<0)
static volatile uint8_t last_status_byte;

static void I2C_0_rx_complete(const struct i2c_s_async_descriptor *const descr)
{
	uint8_t c;
	io_read(io, &c, 1);
	last_status_byte = c;
}

void init_i2c(void)
{
	i2c_s_async_get_io_descriptor(&I2C_0, &io);
	i2c_s_async_register_callback(&I2C_0, I2C_S_RX_COMPLETE, I2C_0_rx_complete);
	i2c_s_async_enable(&I2C_0);
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */

	system_init();
	
	gpio_set_pin_level(LB, true);
	gpio_set_pin_level(LG, true);
	pwm_set_parameters(&PWM_0, 30, 15);
	pwm_enable(&PWM_0);
	delay_ms(100);
	pwm_disable(&PWM_0);
	delay_ms(1000);
	gpio_set_pin_level(LR, true);
	

	// Turn on the system / RPI load switch	

	gpio_set_pin_level(VEN, true);
	gpio_set_pin_level(LG, false);
	init_i2c();

	while (1) {
		if (last_status_byte & STATUS_BYTE_BEEP) {
			pwm_enable(&PWM_0);
		} else {
			pwm_disable(&PWM_0);
		}
	}
}
