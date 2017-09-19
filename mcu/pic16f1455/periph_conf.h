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

#ifndef __PERIPH_CONF_H
#define __PERIPH_CONF_H

#include "mcu.h"

#define __HAL_ENABLE_INTERRUPTS(__state) do {   \
    if (__state) mcu_enable_interrupts();       \
    } while (0)
#define __HAL_DISABLE_INTERRUPTS(__state) do {  \
    __state = mcu_get_interrupt_state();        \
    mcu_disable_interrupts();                   \
    } while(0)

enum MCU_PORT {
    PORT_A = 0,
    /* No port B on PIC16F1455 */
    PORT_C = 2
};

enum TIMER0_PRESCALER {
    TIMER0_PRESCALER_1,
    TIMER0_PRESCALER_2,
    TIMER0_PRESCALER_4,
    TIMER0_PRESCALER_8,
    TIMER0_PRESCALER_16,
    TIMER0_PRESCALER_32,
    TIMER0_PRESCALER_64,
    TIMER0_PRESCALER_128,
    TIMER0_PRESCALER_256
};

#endif
