## qemu
- qemu -smp 4 -m 1024 -hda win2k.qemu -cdrom win2ksp4.iso -boot c 
	-localtime 
	-soundhw es1370 
	-smb /mail/qemu/share
	-net nic,vlan=1 -net user,vlan=1 -win2k-hack -redir tcp:3389::3389
	-usb
	-nographic -vnc :1
## vnc
- gvncviewer :1

## qemu-img, url=http://blog.csdn.net/gg296231363/article/details/6899533
- qemu-img info test.qcow2
- qemu-img snapshot -c snapshot01 test.qcow2
- qemu-img snapshot -a snapshot01 test.qcow2  
- qemu-img snapshot -l test.qcow2
- qemu-img snapshot -d snapshot01 test.qcow2 

## 利用libvirt使用快照
qemu-img info test.qcow2

## qemu usb
sudo kvm -m 1000M -hda disk-30G-win7.qcow2 -vga std -usb -usbdevice host:0451:16a2

## qemu savevm
- ctrl+alt+2
- savevm breakpoint
- sudo kvm -m 1000M -hda disk-30G-win7.qcow2 -vga std -usb -usbdevice host:0451:16a2 loadvm breakpoint

## urls
https://wiki.archlinux.org/index.php/QEMU
