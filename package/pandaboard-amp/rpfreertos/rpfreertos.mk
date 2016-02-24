################################################################################
#
# rpfreertos
#
################################################################################

RPFREERTOS_VERSION = master
RPFREERTOS_SITE = $(call github,sbourdelin,freertos-pandaboard-amp,$(RPFREERTOS_VERSION))

define RPFREERTOS_BUILD_CMDS
	$(MAKE) CROSS_COMPILE=$(BR2_PACKAGE_RPFREERTOS_TOOLCHAIN) -C $(@D)
endef

define RPFREERTOS_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/omap4-ipu-fw.xem3 \
		$(TARGET_DIR)/lib/firmware/omap4-ipu-fw.xem3
endef

$(eval $(generic-package))
