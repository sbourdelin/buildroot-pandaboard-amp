RPGPIO_SITE = $(TOPDIR)/package/pandaboard-amp/rpgpio/src
RPGPIO_SITE_METHOD = local
RPGPIO_DEPENDENCIES = linux

define RPGPIO_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define RPGPIO_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
endef

$(eval $(generic-package))
