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

#ifndef __PERIPH_TIMER0_H
#define __PERIPH_TIMER0_H

#include <stdint.h>

/**
 * @defgroup timer0 TIMER0
 * @ingroup peripherals
 * @{
 */

/**
 * @brief Configure timer0
 *
 * @param[in] prescaler
 */
void timer0_configure(uint8_t prescaler);

/**
 * @return Number of overflows
 */
uint32_t timer0_get_tick_count(void);

/**
 * @brief Set tick count to 0
 */
void timer0_reset_tick_count(void);

/** @} */

#endif
