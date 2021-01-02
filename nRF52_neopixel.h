/******************************************************************************
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ******************************************************************************/

// Link collection:
// https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/

#ifndef NRF52_NEOPIXEL_H
 #define NRF52_NEOPIXEL_H


#include <stdbool.h>
#include <stdint.h>
#include "delay.h"
#include "nrf_gpio.h"
#include <stdlib.h>
#include <Arduino.h>

#define nrf_delay_us(us_time) NRFX_DELAY_US(us_time)


class nRF52_neopixel {

public:


	typedef union {
			struct {
				uint8_t g, r, b;
			}simple;
	    uint8_t grb[3];
	} color_t;
	typedef struct {
		uint8_t pin_num;
		uint16_t num_leds;
		color_t *leds;
	} neopixel_strip_t;

	nRF52_neopixel();
	~nRF52_neopixel();
	void neopixel_init(uint8_t pin_num, uint16_t num_leds);
	void neopixel_clear();
	void neopixel_show();
	void neopixel_set_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue );
	void neopixel_set_color_and_show(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
	void neopixel_destroy();

	//cRGB get_crgb_at(uint16_t pixelIdx);
	//uint8_t set_crgb_at(uint16_t pixelIdx, cRGB px_value);
	void sync();

//These defines are timed specific to a series of if statements and will need to be changed
//to compensate for different writing algorithms than the one in neopixel.c

#define NEOPIXEL_SEND_ONE nrf_gpio_pin_set(PIN); \
__ASM ( \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t" \
); \
nrf_gpio_pin_clear(PIN); \
__ASM ( \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
); //Logic "1" 52x1 + 50x0 * 15.625ns = 812.5ns H + 781.25ns L

#define NEOPIXEL_SEND_ZERO nrf_gpio_pin_set(PIN); \
__ASM ( \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
); \
nrf_gpio_pin_clear(PIN); \
__ASM ( \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
" NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t NOP\n\t" \
); //Logic "0" 2x1 + 40x0 * 15.625ns = 30.25+overhead ns H + 781.25ns L
// nRF51 timing
/*
#define NEOPIXEL_SEND_ONE	NRF_GPIO->OUTSET = (1UL << PIN); \
		__ASM ( \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
			); \
		NRF_GPIO->OUTCLR = (1UL << PIN); \

#define NEOPIXEL_SEND_ZERO NRF_GPIO->OUTSET = (1UL << PIN); \
		__ASM (  \
				" NOP\n\t"  \
			);  \
		NRF_GPIO->OUTCLR = (1UL << PIN);  \
		__ASM ( \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
				" NOP\n\t" \
			);
*/

protected:
	uint8_t mPIXEL_DATA_PIN;
	neopixel_strip_t m_strip;

};

#endif
