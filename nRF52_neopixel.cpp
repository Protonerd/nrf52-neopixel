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
/* Protonerd 2020
 * 
 * WS2812B Tricolor LED (neopixel) controller
 *
 *
 */

#include "nRF52_neopixel.h"

nRF52_neopixel::nRF52_neopixel() {

}

nRF52_neopixel::~nRF52_neopixel(){

}

void nRF52_neopixel::neopixel_init(uint8_t pin_num, uint16_t num_leds)
{
	mPIXEL_DATA_PIN=pin_num;
	nrf_gpio_cfg_output(mPIXEL_DATA_PIN);
	NRF_GPIO->OUTCLR = (1UL << mPIXEL_DATA_PIN);
	nrf_gpio_pin_clear(mPIXEL_DATA_PIN);
	m_strip.leds = (color_t*) malloc(sizeof(color_t) * num_leds);
	m_strip.pin_num = mPIXEL_DATA_PIN;
	m_strip.num_leds = num_leds;
	nrf_gpio_cfg_output(mPIXEL_DATA_PIN);
	NRF_GPIO->OUTCLR = (1UL << mPIXEL_DATA_PIN);
	nrf_gpio_pin_set(mPIXEL_DATA_PIN);
	for (int i = 0; i < num_leds; i++)
	{	
		m_strip.leds[i].simple.g = 0;
		m_strip.leds[i].simple.r = 0;
		m_strip.leds[i].simple.b = 0;
	}
}

void nRF52_neopixel::neopixel_clear()
{
		for (int i = 0; i < m_strip.num_leds; i++)
		{
			m_strip.leds[i].simple.g = 0;
			m_strip.leds[i].simple.r = 0;
			m_strip.leds[i].simple.b = 0;
		}
			neopixel_show();
}

void nRF52_neopixel::neopixel_show()
{

	const uint8_t PIN =  m_strip.pin_num;

	NRF_GPIO->OUTCLR = (1UL << PIN);
	nrf_gpio_pin_clear(PIN);
	//nrf_gpio_pin_set(PIN);
	//nrf_delay_us(50);
	__disable_irq();
			for (int i = 0; i < m_strip.num_leds; i++)
			{
				//Serial.print(" Red: ");Serial.print(m_strip.leds[i].grb[0]);Serial.print(" Green: ");Serial.print(m_strip.leds[i].grb[1]);Serial.print(" Blue: ");Serial.println(m_strip.leds[i].grb[2]);
				for (int j = 0; j < 3; j++)
				{
					if ((m_strip.leds[i].grb[j] & 128) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 64) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 32) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 16) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 8) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 4) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 2) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((m_strip.leds[i].grb[j] & 1) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
				}
			}

			nrf_delay_us(50);
			//nrf_gpio_pin_set(PIN);
			__enable_irq();
}

void nRF52_neopixel::neopixel_set_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue )
{
			m_strip.leds[index].simple.r = red;
			m_strip.leds[index].simple.g = green;
			m_strip.leds[index].simple.b = blue;

}

void nRF52_neopixel::neopixel_set_color_and_show(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{

			m_strip.leds[index].simple.r = red;
			m_strip.leds[index].simple.g = green;
			m_strip.leds[index].simple.b = blue;
			neopixel_show();


}

void nRF52_neopixel::neopixel_destroy()
{
	free(m_strip.leds);
	m_strip.num_leds = 0;
	m_strip.pin_num = 0;
}
