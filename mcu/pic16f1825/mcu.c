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
#include "mcu.h"


void mcu_init(void)
{
    /* @todo Not implemented yet */
}

void mcu_delay(uint32_t nanoseconds)
{
    (void)nanoseconds;
    /* @todo Not implemented yet */
}

void mcu_reset(void)
{
    asm("reset");
}

void mcu_idle(void)
{
    /* @todo Not implemented yet */
}

void mcu_sleep(void)
{
    /* @todo Not implemented yet */
}

inline void mcu_enable_interrupts(void)
{
    /* Set GIE flag in INTCON register */
    asm("bsf INTCON, 7");
}

inline void mcu_disable_interrupts(void)
{
    /* Clear GIE flag in INTCON register */
    asm("bcf INTCON, 7");
}
