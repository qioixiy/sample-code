## 设置运行level
1. sysV
```
#!/bin/sh
cat /etc/inittab
```
2. systemd
```
ls /etc/systemd/system/default.target
mv /etc/systemd/system/default.target /etc/systemd/system/default.target.bak
ln -s /usr/lib/systemd/system/runlevel3.target /etc/systemd/system/default.target
```
