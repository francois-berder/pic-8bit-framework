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

#include <assert.h>
#include <xc.h>
#include "mcu.h"
#include "periph/uart.h"


void uart_configure(uint8_t num, uint32_t baudrate)
{
    assert(num == 0);
    uart_disable(num);

    /*
     *                  Fosc
     * baudrate = ----------------
     *              4 * (BRG + 1)
     */
    uint32_t divisor = mcu_get_clock_frequency();
    divisor >>= 2;
    divisor /= baudrate;
    --divisor;

    SPBRGH = divisor >> 8;
    SPBRGL = divisor;
    BAUDCON |= _BAUDCON_BRG16_MASK;
    TXSTA |= _TXSTA_BRGH_MASK;

    TXSTA &= ~(_TXSTA_SYNC_MASK | _TXSTA_TX9_MASK);
    RCSTA &= ~_RCSTA_RX9_MASK;
    BAUDCON &= ~(_BAUDCON_SCKP_MASK | _BAUDCON_WUE_MASK | _BAUDCON_ABDEN_MASK);
}

void uart_write(uint8_t num, const void *data, uint16_t count)
{
    assert(num == 0);
    const uint8_t *buffer = (const uint8_t *)data;
    while (count) {
        TXREG = *buffer++;

        /* TRMT flag is one Tcy after a write to TXREG */
        asm ("nop");

        /* Wait until the byte is fully transmitted */
        while (!(TXSTA & _TXSTA_TRMT_MASK)) {}

        --count;
    }
}

void uart_read(uint8_t num, void *data, uint16_t count)
{
    assert(num == 0);
    uint8_t *buffer = (uint8_t *)data;

    while (count) {
        /* Wait until a character has been received */
        while (!(PIR1 & _PIR1_RCIF_MASK)) {}

        *buffer++ = RCREG;
        --count;
    }
}

void uart_enable(uint8_t num)
{
    assert(num == 0);

    RCSTA |= _RCSTA_CREN_MASK | _RCSTA_SPEN_MASK;
    TXSTA |= _TXSTA_TXEN_MASK;
}

void uart_disable(uint8_t num)
{
    assert(num == 0);

    RCSTA &= ~(_RCSTA_CREN_MASK | _RCSTA_SPEN_MASK);
    TXSTA &= ~_TXSTA_TXEN_MASK;
}
