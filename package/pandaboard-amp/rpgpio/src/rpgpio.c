/*
 * rpgpio
 *
 * This module aims to request an IRQ on a GPIO an toggle an other GPIO in the
 * interrupt handler.
 *
 * Copyright (C) 2016 Savoir-faire Linux, Inc.
 *
 * Authors:
 *     Sebastien Bourdelin <sebastien.bourdelin@savoirfairelinux.com>
 *
 */
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/module.h>

#define GPIO_IN  33 /* pin 20 J6 */
#define GPIO_OUT 55 /* pin 23 J6 */

static int irq_num = 0;

irqreturn_t gpio_irq_handler(int irq, void *dev_id)
{
    static int value = 0;

    gpio_set_value(GPIO_OUT, value);
    value = 1 - value;

    return IRQ_HANDLED;
}

int __init rpgpio_init(void)
{
    int err;

    irq_num = gpio_to_irq(GPIO_IN);

    if ((err = gpio_request(GPIO_OUT, THIS_MODULE->name)) != 0)
        return err;
    if ((err = gpio_direction_output(GPIO_OUT, 0)) != 0)
        goto err_gpio_free_out;

    if ((err = gpio_request(GPIO_IN, THIS_MODULE->name)) != 0)
        goto err_gpio_free_out;
    if ((err = gpio_direction_input(GPIO_IN)) != 0)
        goto err_gpio_free_in;

    if ((err = request_irq(irq_num,
                           gpio_irq_handler,
                           IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                           THIS_MODULE->name,
                           THIS_MODULE->name)) != 0)
        goto err_gpio_free_in;

    return 0;

err_gpio_free_in:
    gpio_free(GPIO_IN);

err_gpio_free_out:
    gpio_free(GPIO_OUT);

    return err;
}

void __exit rpgpio_exit(void)
{
    free_irq(irq_num, THIS_MODULE->name);
    gpio_free(GPIO_IN);
    gpio_free(GPIO_OUT);
}

module_init(rpgpio_init);
module_exit(rpgpio_exit);

MODULE_AUTHOR("sebastien bourdelin <sebastien.bourdelin@savoirfairelinux.com>");
MODULE_DESCRIPTION("RP GPIO Test Module");
MODULE_LICENSE("GPL v2");
