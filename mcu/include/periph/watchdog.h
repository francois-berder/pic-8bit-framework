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

#ifndef __PERIPH_WATCHDOG_H
#define __PERIPH_WATCHDOG_H

#include <stdint.h>

/**
 * @defgroup wdt Watchdog
 * @ingroup peripherals
 * @{
 */

/**
 * @brief Configure watchdog prescaler
 *
 * This function does not enable the watchdog.
 *
 * @param[in] period
 */
void watchdog_configure(uint8_t period);

/**
 * @brief Enable watchdog
 */
void watchdog_enable(void);

/**
 * @brief Disable watchdog
 */
void watchdog_disable(void);

/**
 * @brief Kick watchdog
 */
void watchdog_kick(void);

/** @} */

#endif
