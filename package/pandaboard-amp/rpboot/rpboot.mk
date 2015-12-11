RPBOOT_SITE = $(TOPDIR)/package/pandaboard-amp/rpboot/src
RPBOOT_SITE_METHOD = local
RPBOOT_DEPENDENCIES = linux

define RPBOOT_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define RPBOOT_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
endef

$(eval $(generic-package))
