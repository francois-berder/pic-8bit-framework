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

#ifndef __PERIPH_TIMER_H
#define __PERIPH_TIMER_H

#include <stdint.h>

/**
 * @brief Configure a timer
 *
 * @param[in] num Index of timer to configure
 * @param[in] prescaler
 * @param[in] postcaler
 * @param[in] period
 * @param[in] callback
 */
void timer_configure(uint8_t num,
                     uint8_t prescaler, uint8_t postcaler,
                     uint8_t period,
                     void(*callback)(void));

/**
 * @brief Start timer
 *
 * @param[in] num
 */
void timer_start(uint8_t num);

/**
 * @brief Stop timer
 *
 * @param[in] num
 */
void timer_stop(uint8_t num);

/**
 * @return Tick count of a timer
 *
 * @param[in] num
 */
uint32_t timer_get_tick_count(uint8_t num);

/**
 * @brief Reset tick count to 0
 *
 * @param[in] num
 */
void timer_reset_tick_count(uint8_t num);

#endif
