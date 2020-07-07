#!/bin/sh -ex

pushd busybox

CC=arm-linux-gnueabihf-

CROSS_COMPILE=$CC make defconfig
# Want static build
sed 's/^.*CONFIG_STATIC.*$/CONFIG_STATIC=y/' -i .config
CROSS_COMPILE=$CC make all -j8
CROSS_COMPILE=$CC make install

popd
