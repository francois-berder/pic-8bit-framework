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

#ifndef __PERIPH_UART_H
#define __PERIPH_UART_H

#include <stdint.h>

/**
 * @defgroup uart UART
 * @ingroup peripherals
 * @{
 */

 /**
  * @brief Configure UART module
  *
  * 8 bits, 1 stop, no parity bit
  * UART module is disabled after being configured.
  *
  * @param[in] num Index of the UART module
  * @param[in] baudrate
  */
void uart_configure(uint8_t num, uint32_t baudrate);

/**
 * @brief Send bytes over UART
 *
 * This function is blocking.
 *
 * @param[in] num Index of the UART module
 * @param[in] buffer
 * @param[in] count
 */
void uart_write(uint8_t num, const void *buffer, uint16_t count);

/**
 * @brief Read bytes from UART
 *
 * This function is blocking.
 *
 * @param[in] num Index of the UART module
 * @param[in] buffer
 * @param[in] count
 */
void uart_read(uint8_t num, void *buffer, uint16_t count);

/**
 * @brief Enable UART module
 *
 * @param[in] num Index of the UART module
 */
void uart_enable(uint8_t num);

/**
 * @brief Disable UART module
 *
 * @param[in] num Index of the UART module
 */
void uart_disable(uint8_t num);

/** @} */

#endif
