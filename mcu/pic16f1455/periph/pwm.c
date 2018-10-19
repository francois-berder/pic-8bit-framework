/*
 * Copyright (C) 2017  Francois Berder <fberder@outlook.fr>
 *
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
 *
 * You should have received a copy of the GNU General Public License
 * along with pic18-framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <xc.h>
#include "periph/pwm.h"
#include "periph/timer.h"

void pwm_configure(uint8_t num, uint8_t timer_num, uint8_t timer_period,
                   uint8_t timer_prescaler, uint8_t timer_postcaler,
                   uint8_t active_high)
{
    assert(num == 1 || num == 2);
    assert(timer_num == 2);

    (void)active_high;

    switch (num) {
    case 1:
        PWM1DCL = 0;
        PWM1DCH = 0;
        PWM1CON = 0;
        break;
    case 2:
        PWM1DCL = 0;
        PWM1DCH = 0;
        PWM2CON = 0;
        break;
    }

    timer_configure(2, timer_prescaler, timer_postcaler, timer_period, 0);
}

void pwm_set_duty_cycle(uint8_t num, uint16_t duty_cycle)
{
    assert(num == 1 || num == 2);

    uint8_t lsb = duty_cycle & 0x2;
    uint8_t msb = duty_cycle >> 2;
    switch (num) {
    case 1:
        PWM1DCL &= ~_PWM1DCL_PWM1DCL_MASK;
        PWM1DCL = lsb << _PWM1DCL_PWM1DCL_POSITION;
        PWM1DCH = msb;
        break;
    case 2:
        PWM2DCL &= ~_PWM2DCL_PWM2DCL_MASK;
        PWM2DCL = lsb << _PWM2DCL_PWM2DCL_POSITION;
        PWM2DCH = msb;
    break;
    }
}

void pwm_enable(uint8_t num)
{
    assert(num == 1 || num == 2);

    switch (num) {
    case 1:
        PWM1CON |= _PWM1CON_PWM1EN_MASK;
        PWM1CON |= _PWM1CON_PWM1OE_MASK;
        break;
    case 2:
        PWM2CON |= _PWM2CON_PWM2EN_MASK;
        PWM2CON |= _PWM2CON_PWM2OE_MASK;
        break;
    }
    timer_start(2);
}

void pwm_disable(uint8_t num)
{
    assert(num == 1 || num == 2);

    switch (num) {
    case 1:
        PWM1CON &= ~_PWM1CON_PWM1EN_MASK;
        PWM1CON &= ~_PWM1CON_PWM1OE_MASK;
        break;
    case 2:
        PWM2CON &= ~_PWM2CON_PWM2EN_MASK;
        PWM2CON &= ~_PWM2CON_PWM2OE_MASK;
        break;
    }
    timer_stop(2);
}
