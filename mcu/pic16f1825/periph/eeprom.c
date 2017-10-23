/*
 * Copyright (C) 2017  Francois Berder <fberder@outlook.fr>
 *
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
 *
 * You should have received a copy of the GNU General Public License
 * along with pic18-framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <xc.h>
#include "mcu.h"
#include "periph/eeprom.h"


void eeprom_read_bytes(uint16_t address, void *data, uint16_t count)
{
    uint8_t *buffer = (uint8_t *)data;
    while (count--) {
        EEADRL = address++;
        EECON1 &= ~(_EECON1_CFGS_MASK | _EECON1_EEPGD_MASK);
        EECON1 |= _EECON1_RD_MASK;
        *buffer++ = EEDATL;
    }
}

void eeprom_write_bytes(uint16_t address, const void *data, uint16_t count)
{
    const uint8_t *buffer = (const uint8_t *)data;
    while (count--) {
        EEADRL = address++;
        EEDATL = *buffer++;

        EECON1 &= ~(_EECON1_CFGS_MASK | _EECON1_EEPGD_MASK);
        EECON1 |= _EECON1_WREN_MASK;

        mcu_disable_interrupts();
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1 |= _EECON1_WR_MASK;
        mcu_enable_interrupts();

        EECON1 &= ~_EECON1_WREN_MASK;

        /* Wait until it finished writing a byte */
        while (EECON1 & _EECON1_WR_MASK) {}
    }
}
