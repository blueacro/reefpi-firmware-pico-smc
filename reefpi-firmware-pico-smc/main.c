#include <atmel_start.h>

static struct io_descriptor *io;

#define STATUS_BYTE_BEEP (1<<0)
static volatile uint8_t last_status_byte;


static volatile bool countdown_enabled = false;
static volatile uint32_t countdown_secs = 0;
static volatile uint32_t countdown_reset = 0;

static void I2C_0_rx_complete(const struct i2c_s_async_descriptor *const descr)
{
	uint8_t c;
	io_read(io, &c, 1);
	last_status_byte = c;
	
	if (last_status_byte & STATUS_BYTE_BEEP) {
		pwm_enable(&PWM_0);
	} else {
		pwm_disable(&PWM_0);
	}
	
	if (last_status_byte >> 1) {
		uint32_t countdown = (last_status_byte >> 1) * 30; // 30 second increments
		if ((last_status_byte >> 1) == (0xFF >> 1)) {
			// Max value - disable)
			countdown_enabled = false;
		} else {
			countdown_reset = countdown;
			countdown_secs = countdown;
			countdown_enabled = true;
		}
	}
}

void init_i2c(void)
{
	i2c_s_async_get_io_descriptor(&I2C_0, &io);
	i2c_s_async_register_callback(&I2C_0, I2C_S_RX_COMPLETE, I2C_0_rx_complete);
	i2c_s_async_enable(&I2C_0);
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
	if (countdown_secs > 0) {
		countdown_secs--;
	}
}

void tmr_init(void)
{
	TIMER_0_task1.interval = 32;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;


	timer_add_task(&TIMER_0, &TIMER_0_task1);

	timer_start(&TIMER_0);
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */

	system_init();
	tmr_init();
	
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

		sleep(1);
		
		if (countdown_enabled) {
			gpio_set_pin_level(LB, false);
		} else {
			gpio_set_pin_level(LB, true);
		}
		
		if (countdown_enabled && countdown_secs < 60) {
			gpio_set_pin_level(LR, false);
		} else {
			gpio_set_pin_level(LR, true);
		}
		
		if (countdown_enabled && countdown_secs == 0) {
			pwm_enable(&PWM_0);
			gpio_set_pin_level(VEN, false);
			gpio_set_pin_level(LG, true);
			delay_ms(5000);
			pwm_disable(&PWM_0);
			gpio_set_pin_level(VEN, true);
			gpio_set_pin_level(LG, false);
			countdown_secs = countdown_reset;
		}
	}
}
