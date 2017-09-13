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

enum MCU_PORT {
    PORT_A = 0,
    /* No port B on PIC16F1825 */
    PORT_C = 2
};

enum WATCHDOG_PRESCALER {
    WATCHDOG_PERIOD_1MS,
    WATCHDOG_PERIOD_2MS,
    WATCHDOG_PERIOD_4MS,
    WATCHDOG_PERIOD_8MS,
    WATCHDOG_PERIOD_16MS,
    WATCHDOG_PERIOD_32MS,
    WATCHDOG_PERIOD_64MS,
    WATCHDOG_PERIOD_128MS,
    WATCHDOG_PERIOD_256MS,
    WATCHDOG_PERIOD_512MS,
    WATCHDOG_PERIOD_1S,
    WATCHDOG_PERIOD_2S,
    WATCHDOG_PERIOD_4S,
    WATCHDOG_PERIOD_8S,
    WATCHDOG_PERIOD_16S,
    WATCHDOG_PERIOD_32S,
    WATCHDOG_PERIOD_64S,
    WATCHDOG_PERIOD_128S,
    WATCHDOG_PERIOD_256S
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
