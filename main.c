/* Task based USART demo:
 * Warren Gay VE3WWG
 *
 * This simple demonstration runs from task1, writing 012...XYZ lines
 * one after the other, at a rate of 5 characters/second. This demo
 * uses usart_send_blocking() to write characters.
 *
 * STM32F103C8T6:
 *	TX:	A9  <====> RX of TTL serial
 *	RX:	A10 <====> TX of TTL serial
 *	CTS:	A11 (not used)
 *	RTS:	A12 (not used)
 *	Config:	8N1
 *	Baud:	38400
 * Caution:
 *	Not all GPIO pins are 5V tolerant, so be careful to
 *	get the wiring correct.
 */

#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/usart.h>

#include <libopencm3/cm3/dwt.h>

//#include "main.h"		// <-- adopt from bdmihai code, TODO: change name
#include "system.h"
#include "gpio.h"

void vTaskLED(void *pvParameters);
void vTaskDisplay(void *pvParameters);
void v_task_GPIO_test(void *pvParameters);

// void FullTestRoutine(void);

static void uart_setup(void);

void uart_putc(char ch);
void uart_println(const char *str, size_t len);

/*********************************************************************
 * Setup the UART
 *********************************************************************/
static void
uart_setup(void) {

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART2);

	// UART TX on PA9 (GPIO_USART2_TX)
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	usart_set_baudrate(USART2,38400);
	usart_set_databits(USART2,8);
	usart_set_stopbits(USART2,USART_STOPBITS_1);
	usart_set_mode(USART2,USART_MODE_TX);
	usart_set_parity(USART2,USART_PARITY_NONE);
	usart_set_flow_control(USART2,USART_FLOWCONTROL_NONE);
	usart_enable(USART2);
}

/*********************************************************************
 * Send one character to the UART
 *********************************************************************/
void
uart_putc(char ch) {
	usart_send_blocking(USART2,ch);
}

void uart_println(const char *str, size_t len) {
	for (size_t i = 0; i < len; i++) {
		uart_putc(str[i]);
	}
	uart_putc('\r');
	uart_putc('\n');
}

/*********************************************************************
 * Send characters to the UART, slowly
 *********************************************************************/
static void
task1(void *args __attribute__((unused))) {
	int c = '0' - 1;
	uint8_t b = 92;

	// char szBuf[32];
	// snprintf(szBuf, sizeof(szBuf), "cur: %x", b);
	// uart_print((szBuf), sizeof(szBuf));

	for (;;) {
		// gpio_toggle(GPIOA,GPIO5);
		vTaskDelay(pdMS_TO_TICKS(1000));
		if ( ++c >= '9' ) {
			uart_putc(c);
			uart_putc('\r');
			uart_putc('\n');
			c = '0' - 1;
		} else	{
			uart_putc(c);
		}
	}
}

// static void sys_tick_setup(void)
// {
// 	/* 84MHz / 8 => 10500000 counts per second. */
// 	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
 
// 	systick_set_reload(10500000 / 2 );

// 	systick_interrupt_enable();

// 	/* Start counting. */
// 	systick_counter_enable();
// }


/*********************************************************************
 * Main program
 *********************************************************************/
int
main(void) {

	// rcc_clock_setup_in_hse_8mhz_out_72mhz(); // Blue pill
	// rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

	system_init();

	// LED on PA5
	// rcc_periph_clock_enable(RCC_GPIOA);
	// gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

	dwt_enable_cycle_counter();

	gpio_init();

	uart_setup();
	// sys_tick_setup();

	// xTaskCreate(task1,"uart check",1000,NULL,configMAX_PRIORITIES-1,NULL);
	xTaskCreate(vTaskLED,"LED",100,NULL,3,NULL);
	xTaskCreate(vTaskDisplay,"Display", 2000,NULL,2,NULL);
	// xTaskCreate(v_task_GPIO_test,"gpio_test",1000,NULL,configMAX_PRIORITIES-1,NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}

//     /* initialize the system */
//     system_init();

//     /* initialize the gpio */
//     gpio_init();

//     /* create the tasks specific to this application. */
//     xTaskCreate(vTaskLED, "vTaskLED", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
//     xTaskCreate(vTaskDisplay, "vTaskDisplay", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

//     /* start the scheduler. */
//     vTaskStartScheduler();

//     /* should never get here ... */
//     blink(10);
//     return 0;

// End
