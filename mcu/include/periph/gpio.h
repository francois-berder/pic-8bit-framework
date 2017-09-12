/**
 * This file is part of pic18-framework.
 *
 * pic18-framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pic18-framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with pic18-framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __PERIPH_GPIO_H
#define __PERIPH_GPIO_H

#include <stdint.h>

/**
 * @defgroup gpio GPIO
 * @ingroup peripherals
 * @{
 */

 /** Define a pin from its port and index */
#define GPIO_PIN(PORT,INDEX)    (((PORT) << 4) | ((INDEX) & 0xF))

enum GPIO_TRIGGER {
    GPIO_RISING = 0x1,
    GPIO_FALLING = 0x2,
    GPIO_EDGE = 0x3
};

/**
 * @brief Configure a gpio as a digital output
 *
 * @param[in] pin
 * @param[in] value Initial value of the gpio
 */
void gpio_init_out(uint8_t pin, uint8_t value);

/**
 * @brief Configure a gpio as a digital input
 *
 * @param[in] pin
 */
void gpio_init_in(uint8_t pin);

/**
 * @brief Configure a IRQ on a gpio
 *
 * @param[in] pin
 * @param[in] trigger
 * @param[in] callback
 */
void gpio_init_irq(uint8_t pin, uint8_t trigger, void (*callback)(void));

/**
 * @brief Read value of gpio
 *
 * @param[in] pin
 *
 * @retval 0 if pin is low
 * @retval 1 if pin is high
 */
uint8_t gpio_read(uint8_t pin);

/**
 * @brief Write value to gpio
 *
 * @param[in] pin
 * @param[in] value 0 to set it low, any other value to set it high
 */
void gpio_write(uint8_t pin, uint8_t value);

/**
 * @brief Toggle gpio
 *
 * If the pin is invalid, nothing is done.
 *
 * @param[in] pin
 */
void gpio_toggle(uint8_t pin);

/** @} */

#endif
