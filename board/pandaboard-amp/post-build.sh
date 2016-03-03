#!/bin/sh
#
# Post-build script.
TARGETDIR=$1

[ -d "$TARGETDIR" ] || exit 1

grep -qw "debugfs" $TARGETDIR/etc/fstab || cat >>$TARGETDIR/etc/fstab <<EOF
debugfs /sys/kernel/debug debugfs defaults 0  0
EOF
