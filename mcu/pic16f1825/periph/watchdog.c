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

#include <xc.h>
#include "board.h"
#include "periph/watchdog.h"

/* By default, set watchdog timer period to 1 second */
#ifndef WATCHDOG_PRESCALER
#define WATCHDOG_PRESCALER  (0b01010)
#endif

void watchdog_configure(void)
{
    WDTCON &= ~ _WDTCON_WDTPS_MASK;
    WDTCON |= (WATCHDOG_PRESCALER << _WDTCON_WDTPS_POSITION);
}

void watchdog_enable(void)
{
    WDTCON |= _WDTCON_SWDTEN_MASK;
}

void watchdog_disable(void)
{
    WDTCON &= ~_WDTCON_SWDTEN_MASK;
}

void watchdog_kick(void)
{
    asm("clrwdt");
}
