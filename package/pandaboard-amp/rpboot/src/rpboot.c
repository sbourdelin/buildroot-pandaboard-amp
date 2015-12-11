/*
 * rpboot
 *
 * This module aims to disable in the Cortex A9 PIC the IRQ used by the freertos
 * amp demo firmware and boot the ducati processor.
 *
 * Copyright (C) 2016 Savoir-faire Linux, Inc.
 *
 * Authors:
 *     Sebastien Bourdelin <sebastien.bourdelin@savoirfairelinux.com>
 *
 */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/remoteproc.h>

#define MODULE_NAME "rpboot"

extern struct rproc *ducati_rproc;

static int irq = -1;
module_param(irq, int, 0);

static int __init rpboot_init(void)
{
	int ret;

	if (irq > 0) {
		disable_irq(irq);
		pr_info("%s: irq %d is now disabled\n", MODULE_NAME, irq);
	}

	/* power on and boot the ducati processor */
	if (!ducati_rproc) {
		pr_err("%s: failed to retrieve the ducati ipu rproc\n",
				MODULE_NAME);
		goto err_irq;
	}
	ret = rproc_boot(ducati_rproc);
	if (ret) {
		pr_err("%s: failed to boot the ducati processor", MODULE_NAME);
		goto err_irq;
	}

	return 0;

err_irq:
	if (irq > 0) {
		enable_irq(irq);
		pr_info("%s: irq %d is now enabled\n", MODULE_NAME, irq);
	}

	return -1;
}

static void __exit rpboot_exit(void)
{
	if (ducati_rproc)
		rproc_shutdown(ducati_rproc);

	if (irq > 0) {
		enable_irq(irq);
		pr_info("%s: irq %d is now enabled\n", MODULE_NAME, irq);
	}
}

module_init(rpboot_init);
module_exit(rpboot_exit);

MODULE_AUTHOR("sebastien bourdelin <sebastien.bourdelin@savoirfairelinux.com>");
MODULE_DESCRIPTION("RP Boot Module");
MODULE_LICENSE("GPL v2");
