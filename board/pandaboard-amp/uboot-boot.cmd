setenv bootargs console=ttyO2,115200n8 noinitrd init=/sbin/init root=/dev/mmcblk0p2 rootwait rw loglevel=8
fatload mmc 0 0x80000000 uImage
bootm 0x80000000
