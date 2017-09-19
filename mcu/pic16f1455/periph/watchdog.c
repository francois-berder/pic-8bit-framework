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
#include "periph_conf.h"
#include "periph/watchdog.h"


void watchdog_configure(uint8_t period)
{
    assert(period <= WATCHDOG_PERIOD_256S);

    WDTCON &= ~ _WDTCON_WDTPS_MASK;
    WDTCON |= (period << _WDTCON_WDTPS_POSITION);
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
