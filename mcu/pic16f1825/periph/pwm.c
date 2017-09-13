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
#include "periph/pwm.h"
#include "periph/timer.h"

static uint8_t pwm_timer[4];

void pwm_configure(uint8_t num, uint8_t timer_num, uint8_t timer_period,
                   uint8_t timer_prescaler, uint8_t timer_postcaler)
{
    assert(num != 0 && num <= 4);

    switch (num) {
    case 1:
        CCPR1L = 0;
        CCP1CON &= ~_CCP1CON_DC1B_MASK;
        CCP1CON &= ~_CCP1CON_CCP1M_MASK;
        CCP1CON |= 0b1100 << _CCP1CON_CCP1M_POSITION;
        CCPTMRS &= ~_CCPTMRS_C1TSEL_MASK;
        if (timer_num == 4)
            CCPTMRS |= 0b01 << _CCPTMRS_C1TSEL_POSITION;
        else if (timer_num == 6)
            CCPTMRS |= 0b10 << _CCPTMRS_C1TSEL_POSITION;
        break;
    case 2:
        CCPR2L = 0;
        CCP2CON &= ~_CCP2CON_DC2B_MASK;
        CCP2CON &= ~_CCP2CON_CCP2M_MASK;
        CCP2CON |= 0b1100 << _CCP2CON_CCP2M_POSITION;
        CCPTMRS &= ~_CCPTMRS_C2TSEL_MASK;
        if (timer_num == 4)
            CCPTMRS |= 0b01 << _CCPTMRS_C2TSEL_POSITION;
        else if (timer_num == 6)
            CCPTMRS |= 0b10 << _CCPTMRS_C2TSEL_POSITION;

        break;
    case 3:
        CCPR3L = 0;
        CCP3CON &= ~_CCP3CON_DC3B_MASK;
        CCP3CON &= ~_CCP3CON_CCP3M_MASK;
        CCP3CON |= 0b1100 << _CCP3CON_CCP3M_POSITION;
        CCPTMRS &= ~_CCPTMRS_C3TSEL_MASK;
        if (timer_num == 4)
            CCPTMRS |= 0b01 << _CCPTMRS_C3TSEL_POSITION;
        else if (timer_num == 6)
            CCPTMRS |= 0b10 << _CCPTMRS_C3TSEL_POSITION;

        break;
    case 4:
        CCPR4L = 0;
        CCP4CON &= ~_CCP4CON_DC4B_MASK;
        CCP4CON &= ~_CCP4CON_CCP4M_MASK;
        CCP4CON |= 0b1100 << _CCP4CON_CCP4M_POSITION;
        CCPTMRS &= ~_CCPTMRS_C4TSEL_MASK;
        if (timer_num == 4)
            CCPTMRS |= 0b01 << _CCPTMRS_C4TSEL_POSITION;
        else if (timer_num == 6)
            CCPTMRS |= 0b10 << _CCPTMRS_C4TSEL_POSITION;
        break;
    }

    pwm_timer[num - 1] = timer_num;
    timer_configure(timer_num, timer_prescaler, timer_postcaler, timer_period, 0);
}

void pwm_set_duty_cycle(uint8_t num, uint16_t duty_cycle)
{
    assert(num != 0 && num <= 4);

    uint8_t lsb = duty_cycle & 0x2;
    uint8_t msb = duty_cycle >> 2;
    switch (num) {
    case 1:
        CCP1CON &= ~_CCP1CON_DC1B_MASK;
        CCP1CON |= lsb << _CCP1CON_DC1B_POSITION;
        CCPR1L = msb;
        break;
    case 2:
        CCP2CON &= ~_CCP2CON_DC2B_MASK;
        CCP2CON |= lsb << _CCP2CON_DC2B_POSITION;
        CCPR2L = msb;
        break;
    case 3:
        CCP3CON &= ~_CCP3CON_DC3B_MASK;
        CCP3CON |= lsb << _CCP3CON_DC3B_POSITION;
        CCPR3L = msb;
        break;
    case 4:
        CCP4CON &= ~_CCP4CON_DC4B_MASK;
        CCP4CON |= lsb << _CCP4CON_DC4B_POSITION;
        CCPR4L = msb;
        break;
    }
}

void pwm_enable(uint8_t num)
{
    assert(num != 0 && num <= 4);

    timer_start(pwm_timer[num - 1]);
}

void pwm_disable(uint8_t num)
{
    assert(num != 0 && num <= 4);

    timer_stop(pwm_timer[num - 1]);
}
