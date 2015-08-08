KERNEL!="sdf?", GOTO="automount_exit"
ACTION=="add", SUBSYSTEM=="block", RUN+="/bin/mkdir /media/usb5", RUN+="/bin/mount -o uid=1000,user,codepage=936,utf8 $root/%k /media/usb5"
ACTION=="remove", SUBSYSTEM=="block", RUN+="/bin/umount /media/usb5", RUN+="/bin/rmdir /media/usb5"
LABEL="automount_exit"