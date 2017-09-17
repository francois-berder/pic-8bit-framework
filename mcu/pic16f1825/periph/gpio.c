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
#include "periph/gpio.h"

#define GPIO_PORT(pin)      ((pin) >> 4)
#define GPIO_INDEX(pin)     ((pin) & 0xF)

#define ANSEL(PIN)      (*ports[GPIO_PORT(PIN)].ansel)
#define PORT(PIN)       (*ports[GPIO_PORT(PIN)].port)
#define TRIS(PIN)       (*ports[GPIO_PORT(PIN)].tris)
#define LAT(PIN)        (*ports[GPIO_PORT(PIN)].lat)

struct gpio_regs_t {
    volatile uint8_t *ansel;
    volatile uint8_t *port;
    volatile uint8_t *tris;
    volatile uint8_t *lat;
};

static struct gpio_regs_t ports[] = {
    {
        &ANSELA,
        &PORTA,
        &TRISA,
        &LATA
    },
    {
        0, 0, 0, 0
    },
    {
        &ANSELC,
        &PORTC,
        &TRISC,
        &LATC
    }
};

static uint8_t intr_registered = 0;
typedef void(*irq_callback_t)(void);
static volatile irq_callback_t callbacks[6];

static uint8_t gpio_irq_cond(void)
{
    return IOCAF && (INTCON & _INTCON_IOCIE_MASK);
}

static void gpio_irq_handler(void *arg)
{
    (void)arg;
    uint8_t i;
    uint8_t index = 0;
    for (i = 1; i < (1 << 6); i <<= 1, ++index) {
        if (IOCAF & i) {
            callbacks[index]();
            IOCAF &= ~i;
        }
    }
}

void gpio_init_out(uint8_t pin, uint8_t value)
{
    ANSEL(pin) &= ~(1 << GPIO_INDEX(pin));
    gpio_write(pin, value);
    TRIS(pin) &= ~(1 << GPIO_INDEX(pin));
}

void gpio_init_in(uint8_t pin)
{
    ANSEL(pin) &= ~(1 << GPIO_INDEX(pin));
    TRIS(pin) |= 1 << GPIO_INDEX(pin);
}

void gpio_init_irq(uint8_t pin, uint8_t trigger, void (*callback)(void))
{
    uint8_t ctx;

    /* Interrupt on Change only on port A */
    assert(GPIO_PORT(pin) == 0);

    uint8_t index = GPIO_INDEX(pin);

    gpio_init_in(pin);

    __HAL_DISABLE_INTERRUPTS(ctx);
    switch(trigger) {
    case GPIO_RISING:
        IOCAN &= ~(1U << index);
        IOCAP |= 1U << index;
        break;
    case GPIO_FALLING:
        IOCAN |= 1U << index;
        IOCAP &= ~(1U << index);
        break;
    case GPIO_EDGE:
        IOCAP |= 1U << index;
        IOCAN |= 1U << index;
        break;
    }

    callbacks[index] = callback;
    IOCAF &= ~(1U << index);
    if (intr_registered == 0) {
        intr_registered++;
        mcu_register_intr_handler(gpio_irq_cond, gpio_irq_handler, 0);
    }
    INTCON |= _INTCON_IOCIE_MASK;
    __HAL_ENABLE_INTERRUPTS(ctx);
}

uint8_t gpio_read(uint8_t pin)
{
    return PORT(pin) & (1 << GPIO_INDEX(pin)) ? 1 : 0;
}

void gpio_write(uint8_t pin, uint8_t value)
{
    if (value)
        LAT(pin) |= 1 << GPIO_INDEX(pin);
    else
        LAT(pin) &= ~(1 << GPIO_INDEX(pin));
}

void gpio_toggle(uint8_t pin)
{
    LAT(pin) ^= 1 << GPIO_INDEX(pin);
}
