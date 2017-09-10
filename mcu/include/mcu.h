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

#ifndef __MCU_H__
#define __MCU_H__

#include <stdint.h>

/**
 * @defgroup mcu MCU
 * @{
 */

/**
 * @brief Initialise the MCU
 */
void mcu_init(void);

/**
 * @brief Busy loop MCU
 *
 * @param[in] nanoseconds
 */
void mcu_delay(uint32_t nanoseconds);

/**
 * @brief Reset MCU
 */
void mcu_reset(void);

/**
 * @brief Set MCU to idle mode
 */
void mcu_idle(void);

/**
 * @brief Set MCU to sleep mode
 */
void mcu_sleep(void);

/** @} */

#endif
