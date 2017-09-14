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
#include "periph/timer1.h"

static uint8_t intr_registered;
typedef void(*timer_callback_t)(void);
static volatile timer_callback_t timer_callback;

static uint8_t timer1_cond(void)
{
    return PIE1 & _PIE1_TMR1IE_MASK
        && PIR1 & _PIR1_TMR1IF_MASK;
}

static void timer1_handler(void *arg)
{
    (void)arg;
    timer_callback();
    PIR1 &= ~_PIR1_TMR1IF_MASK;
}

void timer1_configure(uint8_t prescaler, void(*callback)(void))
{
    assert(prescaler <= TIMER1_PRESCALER_8);

    T1CON = (prescaler << _T1CON_T1CKPS_POSITION) & _T1CON_T1CKPS_MASK;
    timer_callback = callback;
    TMR1L = 0;
    TMR1H = 0;
    if (callback) {
        if (intr_registered == 0) {
            intr_registered++;
            mcu_register_intr_handler(timer1_cond, timer1_handler, 0);
        }
        PIR1 &= ~_PIR1_TMR1IF_MASK;
        PIE1 |= _PIE1_TMR1IE_MASK;
    } else {
        PIE1 &= ~_PIE1_TMR1IE_MASK;
    }

}

void timer1_start(void)
{
    T1CON |= _T1CON_TMR1ON_MASK;
}

void timer1_stop(void)
{
    T1CON &= ~_T1CON_TMR1ON_MASK;
}
