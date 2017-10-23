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

#ifndef __MCU_H__
#define __MCU_H__

#include <stdint.h>

/**
 * @defgroup mcu MCU
 * @{
 */

/**
 * @brief Initialise the MCU
 */
void mcu_init(void);

/**
 * @brief Register an interrupt handler
 *
 * @param[in] cond
 * @param[in] handler
 * @param[in] arg
 */
void mcu_register_intr_handler(void (*cond)(void), void (*handler)(void));

/**
 * @brief Set the clock frequency of the MCU
 *
 * Beware that this function does not change the clock frequency. It is
 * assumed that the clock has already been changed before calling this
 * function.
 * This function is there to store the clock frequency such that any
 * subsequent calls to mcu_get_clock_frequency in peripherals will
 * return @p clock_freq.
 *
 * @param[in] clock_freq
 */
void mcu_set_clock_frequency(uint32_t clock_freq);

/**
 * @return Clock frequency of the MCU. If frequency is unknown  0 is returned.
 */
uint32_t mcu_get_clock_frequency(void);

/**
 * @brief Busy loop MCU
 *
 * @param[in] ticks Number of timer0 ticks to wait
 */
void mcu_delay(uint32_t ticks);

/**
 * @brief Reset MCU
 */
void mcu_reset(void);

/**
 * @brief Set MCU to idle mode
 */
void mcu_idle(void);

/**
 * @brief Set MCU to sleep mode
 */
void mcu_sleep(void);

/**
 * @brief Enable interrupts
 */
inline void mcu_enable_interrupts(void);

/**
 * @brief Disable interrupts
 */
inline void mcu_disable_interrupts(void);

/**
 * @return Interrupt state
 */
inline uint8_t mcu_get_interrupt_state(void);

/** @} */

#endif
