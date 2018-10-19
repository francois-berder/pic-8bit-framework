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

#ifndef __PERIPH_PWM_H
#define __PERIPH_PWM_H

#include <stdint.h>

/**
 * @brief Configure PWM module
 *
 * It does not configure the pin and does not enable it.
 *
 * @param[in] num Index of PWM module
 * @param[in] timer_num
 * @param[in] timer_period
 * @param[in] timer_prescaler
 * @param[in] timer_postcaler
 * @param[in] active_high
 */
void pwm_configure(uint8_t num, uint8_t timer_num, uint8_t timer_period,
                   uint8_t timer_prescaler, uint8_t timer_postcaler,
                   uint8_t active_high);

/**
 * @brief Set duty cycle of PWM module
 *
 * @param[in] num Index of PWM module
 * @param[in] duty_cycle
 */
void pwm_set_duty_cycle(uint8_t num, uint16_t duty_cycle);

/**
 * @brief Enable PWM module
 *
 * @param[in] num Index of PWM module
 */
void pwm_enable(uint8_t num);

/**
 * @brief Disable PWM module
 *
 * @param[in] num Index of PWM module
 */
void pwm_disable(uint8_t num);

#endif
