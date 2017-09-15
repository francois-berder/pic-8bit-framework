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
#include "periph_conf.h"
#include "periph/timer.h"

static volatile uint32_t ticks[3];
static uint8_t intr_registered[3];
typedef void(*timer_callback_t)(void);
static volatile timer_callback_t callbacks[3];

static uint8_t timer2_cond(void)
{
    return PIE1 & _PIE1_TMR2IE_MASK
        && PIR1 & _PIR1_TMR2IF_MASK;
}

static uint8_t timer4_cond(void)
{
    return PIE3 & _PIE3_TMR4IE_MASK
        && PIR3 & _PIR3_TMR4IF_MASK;
}

static uint8_t timer6_cond(void)
{
    return PIE3 & _PIE3_TMR6IE_MASK
        && PIR3 & _PIR3_TMR6IF_MASK;
}

static void timer2_handler(void)
{
    ticks[0]++;
    if (callbacks[0])
        callbacks[0]();
    PIR1 &= ~_PIR1_TMR2IF_MASK;
}

static void timer4_handler(void)
{
    ticks[1]++;
    if (callbacks[1])
        callbacks[1]();
    PIR3 &= ~_PIR3_TMR4IF_MASK;
}

static void timer6_handler(void)
{
    ticks[2]++;
    if (callbacks[2])
        callbacks[2]();
    PIR3 &= ~_PIR3_TMR6IF_MASK;
}

void timer_configure(uint8_t num,
                     uint8_t prescaler, uint8_t postcaler,
                     uint8_t period,
                     void(*callback)(void))
{
    assert(num == 2 || num == 4 || num == 6);
    assert(prescaler <= TIMER2_PRESCALER_64);
    assert(postcaler <= TIMER2_POSTCALER_16);

    switch (num) {
    case 2:
        T2CON = prescaler & _T2CON_T2CKPS_MASK;
        T2CON |= (postcaler << _T2CON_T2OUTPS_POSITION) & _T2CON_T2OUTPS_MASK;
        PR2 = period;
        TMR2 = 0;
        callbacks[0] = callback;
        break;
    case 4:
        T4CON = prescaler & _T4CON_T4CKPS_MASK;
        T4CON |= (postcaler << _T4CON_T4OUTPS_POSITION) & _T4CON_T4OUTPS_MASK;
        PR4 = period;
        TMR4 = 0;
        callbacks[1] = callback;
        break;
    case 6:
        T6CON = prescaler & _T6CON_T6CKPS_MASK;
        T6CON |= (postcaler << _T6CON_T6OUTPS_POSITION) & _T6CON_T6OUTPS_MASK;
        PR6 = period;
        TMR6 = 0;
        callbacks[2] = callback;
        break;
    }

    switch (num) {
    case 2:
        if (intr_registered[0] == 0) {
            intr_registered[0]++;
            mcu_register_intr_handler(timer2_cond, timer2_handler, 0);
        }
        PIR1 &= ~_PIR1_TMR2IF_MASK;
        PIE1 |= _PIE1_TMR2IE_MASK;
        break;
    case 4:
        if (intr_registered[1] == 0) {
            intr_registered[1]++;
            mcu_register_intr_handler(timer4_cond, timer4_handler, 0);
        }
        PIR3 &= ~_PIR3_TMR4IF_MASK;
        PIE3 |= _PIE3_TMR4IE_MASK;
        break;
    case 6:
        if (intr_registered[2] == 0) {
            intr_registered[2]++;
            mcu_register_intr_handler(timer6_cond, timer6_handler, 0);
        }
        PIR3 &= ~_PIR3_TMR6IF_MASK;
        PIE3 |= _PIE3_TMR6IE_MASK;
        break;
    }
}

void timer_start(uint8_t num)
{
    switch (num) {
    case 2:
        T2CON |= _T2CON_TMR2ON_MASK;
        break;
    case 4:
        T4CON |= _T4CON_TMR4ON_MASK;
        break;
    case 6:
        T6CON |= _T6CON_TMR6ON_MASK;
        break;
    }
}

void timer_stop(uint8_t num)
{
    switch (num) {
    case 2:
        T2CON &= ~_T2CON_TMR2ON_MASK;
        break;
    case 4:
        T4CON &= ~_T4CON_TMR4ON_MASK;
        break;
    case 6:
        T6CON &= ~_T6CON_TMR6ON_MASK;
        break;
    }
}

uint32_t timer_get_tick_count(uint8_t num)
{
    uint32_t t;

    mcu_disable_interrupts();
    switch (num) {
    case 2:
        t = ticks[0];
        break;
    case 4:
        t = ticks[1];
        break;
    case 6:
        t = ticks[2];
        break;
    }
    mcu_enable_interrupts();

    return t;
}

void timer_reset_tick_count(uint8_t num)
{
    mcu_disable_interrupts();
    switch (num) {
    case 2:
        ticks[0] = 0;
        break;
    case 4:
        ticks[1] = 0;
        break;
    case 6:
        ticks[2] = 0;
        break;
    }
    mcu_enable_interrupts();
}
