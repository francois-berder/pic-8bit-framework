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

#ifndef __PERIPH_TIMER1_H
#define __PERIPH_TIMER1_H

/**
 * @brief Configure timer 1
 *
 * This function does not start the timer.
 *
 * @param[in] prescaler
 * @param[in] callback
 */
void timer1_configure(uint8_t prescaler, void(*callback)(void));

/**
 * @brief Start timer 1
 */
void timer1_start(void);

/**
 * @brief Stop timer 1
 */
void timer1_stop(void);

#endif
