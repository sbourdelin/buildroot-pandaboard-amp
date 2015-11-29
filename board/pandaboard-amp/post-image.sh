#!/bin/bash
#
# Post image generation script.

set -e

IMAGE_DIR="$1"
BOARD_DIR="board/pandaboard-amp"


# Argument 1 is the images directory
if [ ! -d "$IMAGE_DIR" ]; then
	echo "Missing argument1 directory!"
	exit 1
fi

######################################
# u-boot environment script generation
######################################
echo "* Generating U-Boot script image (boot.scr)..."
mkimage -C none -A arm -T script \
	-d board/pandaboard-amp/uboot-boot.cmd \
	$IMAGE_DIR/boot.scr

######################################
# copy u-boot image and MLO into image
######################################
echo "* Copy U-Boot and MLO into final image..."
cp -f $BOARD_DIR/MLO \
        $IMAGE_DIR/MLO
cp -f $BOARD_DIR/u-boot.bin \
        $IMAGE_DIR/u-boot.bin

#########################################
# Final image generation (using genimage)
#########################################
# Prepare data for image
T=`mktemp -d`
mkdir -p $T/{root,tmp}

echo "* Generating sd-card image..."
genimage \
        --config $BOARD_DIR/genimage.cfg \
        --rootpath $T/root \
        --tmppath $T/tmp \
        --inputpath $IMAGE_DIR/ \
        --outputpath $IMAGE_DIR/ \

rm -rf $T $IMAGE_DIR/boot.vfat

