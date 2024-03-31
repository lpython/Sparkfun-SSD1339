/*_____________________________________________________________________________
 │                                                                            |
 │ COPYRIGHT (C) 2020 Mihai Baneu                                             |
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
 |  Author: Mihai Baneu                           Last modified: 13.Dec.2020  |
 |                                                                            |
 |___________________________________________________________________________*/

// #include "stm32f4xx.h"
#include "gpio.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

/*_____________________________________________________________________________
 │                                                                            
 │     Data lines are SSD1339 D0-D7  ->  PC0-7                                 
 |                                          
 │     SSD1339  | 8080  | ACTIVE LOW      | ORIGINAL | MORPHO    
 |     ERD      | READ  |     ✓           |   B 9    |   B 2 
 |     R/W      | WRITE |     ✓           |   B 8    |   B 3                                   
 |     CS       |       |     ✓           |   B 5    |   B 4                                    
 |     D/C      |       | High for data   |   B 7    |   B 5                                   
 |     RES      |       |     ✓           |   B 6    |   B 6                                    
 |     EN       |       |     ✓           |   B 10   |   B 7                                           
 |
 |     EN is for +12V booster on sparkfun board
 |___________________________________________________________________________ */



void gpio_init()
{
    /* disable JTAG */
    // MODIFY_REG(GPIOA->MODER,    GPIO_MODER_MODER15_Msk,     0);                         /* JTDI disabled */
    // MODIFY_REG(GPIOB->MODER,    GPIO_MODER_MODER4_Msk,      0);                         /* NJTRST disabled */
    // MODIFY_REG(GPIOB->MODER,    GPIO_MODER_MODER3_Msk,      0);                         /* JTDO disabled */
    
    /* configure LED pin */
    // MODIFY_REG(GPIOC->MODER,    GPIO_MODER_MODER13_Msk,     GPIO_MODER_MODER13_0);      /* set the pin as output */
    // MODIFY_REG(GPIOC->OTYPER,   GPIO_OTYPER_OT13_Msk,       0);                         /* push pull */
    // MODIFY_REG(GPIOC->OSPEEDR,  GPIO_OSPEEDR_OSPEED13_Msk,  0);                         /* low speed */
    // MODIFY_REG(GPIOC->PUPDR,    GPIO_PUPDR_PUPD13_Msk,      0);                         /* no pull up, no pull down */

    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    
    // Nucleo LED
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

void gpio_set_blue_led()
{
    // GPIOC->BSRR = GPIO_BSRR_BR13;
    gpio_set(GPIOA, GPIO5);
}

// now green
void gpio_reset_blue_led()
{
    // GPIOC->BSRR = GPIO_BSRR_BS13;
    gpio_clear(GPIOA, GPIO5);
}

// enable +12 volt booster
void gpio_en_12v()
{
    // GPIOB->BSRR = GPIO_BSRR_BS7;
    gpio_set(GPIOB, GPIO7);
}

void gpio_dis_12v()
{
    // GPIOB->BSRR = GPIO_BSRR_BR7;
    gpio_clear(GPIOB, GPIO7);
}

void gpio_cs_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS4;
    gpio_set(GPIOB, GPIO4);
}

void gpio_cs_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR4;
    gpio_clear(GPIOB, GPIO4);
}

void gpio_res_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS6;
    gpio_set(GPIOB, GPIO6);
}

void gpio_res_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR6;
    gpio_clear(GPIOB, GPIO6);
}

void gpio_dc_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS5;
    gpio_set(GPIOB, GPIO5);
}

void gpio_dc_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR5;
    gpio_clear(GPIOB, GPIO5);
}

void gpio_wr_high() 
{
    // GPIOB->BSRR = GPIO_BSRR_BS3;  
    gpio_set(GPIOB, GPIO3);
}

void gpio_wr_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR3;
    gpio_clear(GPIOB, GPIO3);
}

void gpio_rd_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS2;
    gpio_set(GPIOB, GPIO2);
}

void gpio_rd_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR2;
    gpio_clear(GPIOB, GPIO2);
}

void gpio_cs_wr_high() 
{
    // GPIOB->BSRR = GPIO_BSRR_BS4 | GPIO_BSRR_BS3;  
    gpio_set(GPIOB, GPIO3 | GPIO4);
}

void gpio_cs_wr_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR4 | GPIO_BSRR_BR3;
    gpio_clear(GPIOB, GPIO3 | GPIO4);
}

void gpio_cs_rd_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS4 | GPIO_BSRR_BS2;
    gpio_set(GPIOB, GPIO2 | GPIO4);
}

void gpio_cs_rd_low() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BR4 | GPIO_BSRR_BR2;
    gpio_clear(GPIOB, GPIO2 | GPIO4);
}

void gpio_dc_cs_wr_high() 
{  
    // GPIOB->BSRR = GPIO_BSRR_BS5 | GPIO_BSRR_BS4 | GPIO_BSRR_BS3;
    gpio_set(GPIOB, GPIO3 | GPIO4 | GPIO5);
}

void gpio_dc_cs_wr_low() 
{
    // GPIOB->BSRR = GPIO_BSRR_BR5 | GPIO_BSRR_BR4 | GPIO_BSRR_BR3;   
    gpio_clear(GPIOB, GPIO3 | GPIO4 | GPIO5);
}

void gpio_data_wr(const uint8_t data)
{
    // GPIOC->ODR = 0xFF & data;
    gpio_port_write(GPIOC, 0xFF & data);
}

uint8_t gpio_data_rd()
{
    // return GPIOC->IDR & 0xFF;
    return gpio_port_read(GPIOC) & 0xFF;
}

void gpio_config_data_out()
{
    // /* set the pin as output */
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER0_Msk, GPIO_MODER_MODER0_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER1_Msk, GPIO_MODER_MODER1_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER2_Msk, GPIO_MODER_MODER2_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER3_Msk, GPIO_MODER_MODER3_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER4_Msk, GPIO_MODER_MODER4_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER5_Msk, GPIO_MODER_MODER5_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER6_Msk, GPIO_MODER_MODER6_0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER7_Msk, GPIO_MODER_MODER7_0);

    // /* push pull */
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT0_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT1_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT2_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT3_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT4_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT5_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT6_Msk, 0);
    // MODIFY_REG(GPIOA->OTYPER, GPIO_OTYPER_OT7_Msk, 0);

    // /* high speed */
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED0_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED1_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED2_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED3_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED4_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED6_Msk, 2);
    // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED7_Msk, 2);

    // /* no pull up, no pull down */
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD0_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD1_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD2_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD3_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD4_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD5_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD6_Msk, 0);
    // MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPD7_Msk, 0);

    // rcc_periph_clock_enable(RCC_GPIOC);
    
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);

    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO0);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO1);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO2);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO3);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO4);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO5);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO6);
    gpio_set_output_options(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO7);
}

void gpio_config_data_in()
{
    /* set the pin as input */
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER0_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER1_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER2_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER3_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER4_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER5_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER6_Msk, 0);
    // MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER7_Msk, 0);

    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO3);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO4);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO5);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO7);
}

void gpio_config_control_out()
{
    // /* set the pin as output */
    // MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER5_Msk, GPIO_MODER_MODER5_0);
    // MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER6_Msk, GPIO_MODER_MODER6_0);
    // MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER7_Msk, GPIO_MODER_MODER7_0);
    // MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER8_Msk, GPIO_MODER_MODER8_0);
    // MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER9_Msk, GPIO_MODER_MODER9_0);

    // /* push pull */
    // MODIFY_REG(GPIOB->OTYPER, GPIO_OTYPER_OT5_Msk, 0);
    // MODIFY_REG(GPIOB->OTYPER, GPIO_OTYPER_OT6_Msk, 0);
    // MODIFY_REG(GPIOB->OTYPER, GPIO_OTYPER_OT7_Msk, 0);
    // MODIFY_REG(GPIOB->OTYPER, GPIO_OTYPER_OT8_Msk, 0);
    // MODIFY_REG(GPIOB->OTYPER, GPIO_OTYPER_OT9_Msk, 0);

    // /* high speed */
    // MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED5_Msk, 2);
    // MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED6_Msk, 2);
    // MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED7_Msk, 2);
    // MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED8_Msk, 2);
    // MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED9_Msk, 2);

    // /* no pull up, no pull down */
    // MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD5_Msk, 0);
    // MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD6_Msk, 0);
    // MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD7_Msk, 0);
    // MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD8_Msk, 0);
    // MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD9_Msk, 0);


    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
}
