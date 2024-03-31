/*_____________________________________________________________________________
 │                                                                            |
 │ COPYRIGHT (C) 2021 Mihai Baneu                                             |
 │                                                                            |
 | Permission is hereby  granted,  free of charge,  to any person obtaining a |
 | copy of this software and associated documentation files (the "Software"), |
 | to deal in the Software without restriction,  including without limitation |
 | the rights to  use, copy, modify, merge, publish, distribute,  sublicense, |
 | and/or sell copies  of  the Software, and to permit  persons to  whom  the |
 | Software is furnished to do so, subject to the following conditions:       |
 |                                                                            |
 | The above  copyright notice  and this permission notice  shall be included |
 | in all copies or substantial portions of the Software.                     |
 |                                                                            |
 | THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS |
 | OR   IMPLIED,   INCLUDING   BUT   NOT   LIMITED   TO   THE  WARRANTIES  OF |
 | MERCHANTABILITY,  FITNESS FOR  A  PARTICULAR  PURPOSE AND NONINFRINGEMENT. |
 | IN NO  EVENT SHALL  THE AUTHORS  OR  COPYRIGHT  HOLDERS  BE LIABLE FOR ANY |
 | CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER IN AN ACTION OF CONTRACT, TORT |
 | OR OTHERWISE, ARISING FROM,  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR  |
 | THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                 |
 |____________________________________________________________________________|
 |                                                                            |
 |  Author: Mihai Baneu                           Last modified: 02.Jan.2021  |
 |                                                                            |
 |___________________________________________________________________________*/

// #include "stm32f4xx.h"
// #include "stm32f4xx_hal.h"
// #include "stm32rtos.h"

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/cm3/nvic.h>

#include "gpio.h"
#include "system.h"

void
uart_putc(char ch); 


static void fault_delay(void); 

void system_init()
{
    // nearly all of previous init code is taken care of by rcc_clock_setup_pll

    /* configure Flash prefetch, Instruction cache, Data cache */ 
    // SET_BIT(FLASH->ACR, FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN);

    /* configure the main internal regulator output voltage */
    // SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    // MODIFY_REG(PWR->CR, PWR_CR_VOS, PWR_REGULATOR_VOLTAGE_SCALE2);

    // SCALE 1 or 2 should enable 84MHz
    // performed by rcc_clock_setup_pll
    //pwr_set_vos_scale(PWR_SCALE2);

    /* enable the external High Speed Clock */
    // SET_BIT(RCC->CR, RCC_CR_HSEON);
    // do {
    // } while ((RCC->CR & RCC_CR_HSERDY_Msk) != RCC_CR_HSERDY);
    // Using HSI, could switch to clock from stlink

    /* configure the PLL */
    // MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_HSE);
    // MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_Msk, 25 << RCC_PLLCFGR_PLLM_Pos);
    // MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, 192 << RCC_PLLCFGR_PLLN_Pos);
    // MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk, 0);
    // MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk, 4 << RCC_PLLCFGR_PLLQ_Pos);
    
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

    /* enable PLL clock generation */
    // SET_BIT(RCC->CR, RCC_CR_PLLON);
    // do {
    // } while ((RCC->CR & RCC_CR_PLLRDY_Msk) != RCC_CR_PLLRDY);

    /* to correctly read data from FLASH memory, the number of wait states (LATENCY) 
       must be correctly programmed according to the frequency of the CPU clock 
       (HCLK) of the device. */
    // MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY_Msk, FLASH_ACR_LATENCY_3WS);

    /* set the highest APBx dividers in order to ensure that we do not go through
        a non-spec phase whatever we decrease or increase HCLK. */
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_DIV16);
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_DIV16);
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE_Msk, RCC_CFGR_HPRE_DIV1);

    /* set the SYSCLK to PLL */
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);
    // do {
    // } while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);

    /* disable HSI clock */
    // CLEAR_BIT(RCC->CR, RCC_CR_HSION);
    // do {
    // } while ((RCC->CR & RCC_CR_HSIRDY_Msk) == RCC_CR_HSIRDY);

    /* confgure the APB clocks */
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_DIV2);
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_DIV2);

   

    /* enable AHB1 ports clock */
    // SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    // SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
    // SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
    // SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    // rcc_periph_clock_enable(RCC_GPIOH);

    /* enable DWT */
    // CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;


}

 

/**
 * delay in us (blockig)
 */
void delay_us(const uint32_t us)
{
    // DWT->CYCCNT = 0;
    // do {
    // } while (DWT->CYCCNT < (us * (configCPU_CLOCK_HZ / 1000000)));

    // vtaskdelay for microseconds
    vTaskDelay(pdMS_TO_TICKS(us / 1000));
}

/**
 * blink the led in case of problems
 * This function can only be called after the initialization phase. It is used for
 * faults after RTOS start.
*/
void blink(const uint8_t n)
{
    for (;;) {
        for (int i = 0; i < n; i++) {
    		gpio_set(GPIOA,GPIO5);
            fault_delay();

    		gpio_clear(GPIOA,GPIO5);
            fault_delay();
        }
        fault_delay();
    }
}

static void fault_delay() {
    int i = 0;
    for (i = 0; i < 100000; i++) {
        __asm__("nop");
    }
}

int _write(int file, char *ptr, int len)
{
    (void)(file);
    for (int i = 0; i < len; i++) {
        // ITM_SendChar((*ptr++));
        uart_putc(*ptr++);
    }
    return len;
}

char* itoa(int val, char * buf, int base) {
    // static char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    return &buf[i+1];
}


/** Hard fault - blink four short flash every two seconds */
void hard_fault_handler(void)
{
    blink(4);
}

/** Bus fault - blink five short flashes every two seconds */
void bus_fault_handler(void)
{
    blink(5);
}

/** Usage fault - blink six short flashes every two seconds */
void usage_fault_handler(void)
{
    blink(6);
}
