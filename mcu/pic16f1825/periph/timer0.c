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
#include "mcu.h"
#include "periph/timer0.h"

static uint32_t ticks;
static void(*timer_callback)(void);

static uint8_t timer0_cond(void)
{
    return INTCON & _INTCON_TMR0IE_MASK
        && INTCON & _INTCON_TMR0IF_MASK;
}

static uint8_t timer0_handler(void *arg)
{
    (void)arg;
    ++ticks;
    INTCON &= ~_INTCON_TMR0IF_MASK;
}

void timer0_configure(void)
{
    /* Disable interrupt */
    INTCON &= ~_INTCON_TMR0IE_MASK;

    /* Increase every Fosc/4 */
    OPTION_REG &= ~_OPTION_REG_TMR0CS_MASK;

    /* Configure timer prescaler */
#ifdef TIMER0_PRESCALER
    OPTION_REG &= ~_OPTION_REG_PS_MASK;
    OPTION_REG |= (TIMER0_PRESCALER << _OPTION_REG_PS_POSITION);
    OPTION_REG &= ~_OPTION_REG_PSA_MASK;
#elif
    OPTION_REG |= _OPTION_REG_PSA_MASK;
#endif

    ticks = 0;
    TMR0 = 0;

    /* Register interrupt handler */
    mcu_register_intr_handler(timer0_cond, timer0_handler, 0);

    /* Enable interrupt */
    INTCON &= ~_INTCON_TMR0IF_MASK;
    INTCON |= _INTCON_TMR0IE_MASK;
}

uint32_t timer0_get_tick_count(void)
{
    uint32_t t;
    mcu_disable_interrupts();
    t = ticks;
    mcu_enable_interrupts();
    return t;
}

void timer0_reset_tick_count(void)
{
    mcu_disable_interrupts();
    ticks = 0;
    mcu_enable_interrupts();
}