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
 |  Author: Mihai Baneu                           Last modified: 15.May.2020  |
 |                                                                            |
 |___________________________________________________________________________*/
 
#pragma once

#include <stdint.h>

/* initialization */
void gpio_init(void);

/* led control */
void gpio_set_blue_led(void);
void gpio_reset_blue_led(void);

void gpio_config_control_out(void);
void gpio_config_data_out(void);
void gpio_config_data_in(void);
void gpio_en_12v(void);
void gpio_dis_12v(void);

void gpio_cs_high(void);
void gpio_cs_low(void);
void gpio_res_high(void);
void gpio_res_low(void);
void gpio_dc_high(void);
void gpio_dc_low(void);
void gpio_wr_high(void);
void gpio_wr_low(void);
void gpio_rd_high(void);
void gpio_rd_low(void);
void gpio_cs_wr_high(void);
void gpio_cs_wr_low(void);
void gpio_cs_rd_high(void);
void gpio_cs_rd_low(void);
void gpio_dc_cs_wr_high(void);
void gpio_dc_cs_wr_low(void);
void gpio_data_wr(const uint8_t data);
uint8_t gpio_data_rd(void);
