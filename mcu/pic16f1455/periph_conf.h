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

enum TIMER2_PRESCALER {
    TIMER2_PRESCALER_1,
    TIMER2_PRESCALER_4,
    TIMER2_PRESCALER_16,
    TIMER2_PRESCALER_64
};

enum TIMER2_POSTCALER {
    TIMER2_POSTCALER_1,
    TIMER2_POSTCALER_2,
    TIMER2_POSTCALER_3,
    TIMER2_POSTCALER_4,
    TIMER2_POSTCALER_5,
    TIMER2_POSTCALER_6,
    TIMER2_POSTCALER_7,
    TIMER2_POSTCALER_8,
    TIMER2_POSTCALER_9,
    TIMER2_POSTCALER_10,
    TIMER2_POSTCALER_11,
    TIMER2_POSTCALER_12,
    TIMER2_POSTCALER_13,
    TIMER2_POSTCALER_14,
    TIMER2_POSTCALER_15,
    TIMER2_POSTCALER_16,
};

#endif
