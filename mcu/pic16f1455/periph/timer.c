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

static volatile uint32_t ticks;
static uint8_t intr_registered;
typedef void(*timer_callback_t)(void);
static volatile timer_callback_t callback;

static uint8_t timer2_cond(void)
{
    return PIE1 & _PIE1_TMR2IE_MASK
        && PIR1 & _PIR1_TMR2IF_MASK;
}

static void timer2_handler(void)
{
    ticks++;
    if (callback)
        callback();
    PIR1 &= ~_PIR1_TMR2IF_MASK;
}

void timer_configure(uint8_t num,
                     uint8_t prescaler, uint8_t postcaler,
                     uint8_t period,
                     void(*_callback)(void))
{
    assert(num == 2);
    assert(prescaler <= TIMER2_PRESCALER_64);
    assert(postcaler <= TIMER2_POSTCALER_16);

    T2CON = prescaler & _T2CON_T2CKPS_MASK;
    T2CON |= (postcaler << _T2CON_T2OUTPS_POSITION) & _T2CON_T2OUTPS_MASK;
    PR2 = period;
    TMR2 = 0;
    callback = _callback;

    if (callback != 0) {
        if (intr_registered == 0) {
            intr_registered++;
            mcu_register_intr_handler(timer2_cond, timer2_handler);
        }
        PIR1 &= ~_PIR1_TMR2IF_MASK;
        PIE1 |= _PIE1_TMR2IE_MASK;
    } else {
        PIR1 &= ~_PIR1_TMR2IF_MASK;
        PIE1 &= ~_PIE1_TMR2IE_MASK;
    }
}

void timer_start(uint8_t num)
{
    assert(num == 2);

    T2CON |= _T2CON_TMR2ON_MASK;
}

void timer_stop(uint8_t num)
{
    assert(num == 2);

    T2CON &= ~_T2CON_TMR2ON_MASK;
}

uint32_t timer_get_tick_count(uint8_t num)
{
    uint32_t t;
    uint8_t ctx;
    assert(num == 2);

    __HAL_DISABLE_INTERRUPTS(ctx);
    t = ticks;
    __HAL_ENABLE_INTERRUPTS(ctx);

    return t;
}

void timer_reset_tick_count(uint8_t num)
{
    uint8_t ctx;
    assert(num == 2);

    __HAL_DISABLE_INTERRUPTS(ctx);
    ticks = 0;
    __HAL_ENABLE_INTERRUPTS(ctx);
}
