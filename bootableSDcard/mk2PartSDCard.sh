#! /bin/sh
# mk2PartSDCard.sh v0.1
# Licensed under terms of GPLv2
#original SRC ti.com
#usage mk2PartSDCard.sh /dev/sdb

DRIVE=$1

dd if=/dev/zero of=$DRIVE bs=1024 count=1024

SIZE=`fdisk -l $DRIVE | grep Disk | awk '{print $5}'`

echo DISK SIZE - $SIZE bytes

CYLINDERS=`echo $SIZE/255/63/512 | bc`

sfdisk -D -H 255 -S 63 -C $CYLINDERS $DRIVE << EOF
,9,0x0C,*
10,114,,,
EOF

mkfs.vfat -F 32 -n "boot" ${DRIVE}1
umount ${DRIVE}1
mkfs.ext3 -L "rootfs" ${DRIVE}2
