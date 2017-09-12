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

#ifndef __PERIPH_EEPROM_H
#define __PERIPH_EEPROM_H

#include <stdint.h>

/**
 * @defgroup eeprom EEPROM
 * @ingroup peripherals
 * @{
 */

void eeprom_read_bytes(uint16_t address, void *data, uint16_t count);

void eeprom_write_bytes(uint16_t address, const void *data, uint16_t count);


/** @} */

#endif
