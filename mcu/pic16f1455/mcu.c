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
#include "mcu.h"
#include "periph_conf.h"
#include "periph/timer0.h"

#ifndef MAX_INTERRUPT_COUNT
#define MAX_INTERRUPT_COUNT     (8U)
#endif

static uint32_t clock_freq = 0;
static uint8_t intr_count;

struct interrupt_entry_t {
    uint8_t (*cond)(void);
    void (*handler)(void);
};
static struct interrupt_entry_t entries[MAX_INTERRUPT_COUNT];

static void interrupt mcu_intr_handler(void)
{
    unsigned int i;
    for (i = 0; i < intr_count; ++i) {
        if (entries[i].cond())
            entries[i].handler();
    }
}

void mcu_init(void)
{
    /* Enable peripheral interrupts */
    asm("bsf INTCON, 6");

    mcu_enable_interrupts();
}

void mcu_register_intr_handler(void (*cond)(void), void(*handler)(void))
{
    uint8_t ctx;
    assert(intr_count < MAX_INTERRUPT_COUNT);

    __HAL_DISABLE_INTERRUPTS(ctx);
    entries[intr_count].cond = cond;
    entries[intr_count].handler = handler;
    ++intr_count;
    __HAL_ENABLE_INTERRUPTS(ctx);
}

void mcu_set_clock_frequency(uint32_t _clock_freq)
{
    clock_freq = _clock_freq;
}

uint32_t mcu_get_clock_frequency(void)
{
    return clock_freq;
}

void mcu_delay(uint32_t ticks)
{
    uint32_t now = timer0_get_tick_count();
    while (timer0_get_tick_count() - now < ticks) {}
}

void mcu_reset(void)
{
    asm("reset");
}

void mcu_idle(void)
{
    /* idle mode does not exist on this device */
    assert(0);
}

void mcu_sleep(void)
{
    asm("sleep");
}

inline void mcu_enable_interrupts(void)
{
    /* Set GIE flag in INTCON register */
    asm("bsf INTCON, 7");
}

inline void mcu_disable_interrupts(void)
{
    /* Clear GIE flag in INTCON register */
    asm("bcf INTCON, 7");
}

inline uint8_t mcu_get_interrupt_state(void)
{
    return INTCON & _INTCON_GIE_MASK;
}
