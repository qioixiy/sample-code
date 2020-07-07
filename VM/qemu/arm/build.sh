#!/bin/sh

URL=https://sourcery.mentor.com/sgpp/lite/arm/portal/package8734/public/arm-none-eabi/arm-2011.03-42-arm-none-eabi-i686-pc-linux-gnu.tar.bz2
FILE=`basename $URL`

[ -f $FILE ] || wget $URL
