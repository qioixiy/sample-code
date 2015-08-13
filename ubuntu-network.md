
## url
[Ubuntu中启用关闭Network-manager网络设置](http://blog.csdn.net/anhuidelinger/article/details/17584299)
[详解ubuntu的网络配置](http://blog.sina.com.cn/s/blog_5f43e5250102uxtc.html)

由于ubuntu使用了两条配置线路,/etc/network/interfaces这个配置文件主要用于便于服务器版本的ubuntu系统使用;
同时为了适应移动办公造成ip和网络环境不断变化，ubuntu在/etc/NetworkManager/NetworkManager.conf中进行了配置。
这两个文件是冲突的，采取的策略是，当interfaces文件被修改时，以此文件上的配置为准，除非NetworkManager/Net-
workManager.conf中managed参数为true(managed=true)，强制使用除非NetworkManager管理网络。

sudo /etc/init.d/networking restart #重启网络配置
sudo ifconfig #显示所有网卡的接口信息
sudo apt-update 
sudo apt-get remove --purge bcmwl-kernel-source   #卸载当前驱动 bcmwl-kernel-source 
sudo modprobe -r b43 ssb wl brcmfmac  #
sudo apt-get reinstall install bcmwl-kernel-source

## 安装新驱动，可以到ubuntu的软件中心安装 
sudo modprobe wl 加载新驱动模块到linux内核
到/etc/modprobe.d/中去删除 冗余的 .conf 配置，并检查文件 blacklist 中是否把新装的驱动在屏蔽范围内，如有则解除屏蔽。
sudo rm /etc/modprobe.d/blacklist-bcm43.conf
sudo rm /etc/modprobe.d/broadcom-sta-common.conf
sudo rm /etc/modprobe.d/broadcom-sta-dkms.conf
sudo sed -i "s/blacklist b43/#blacklist b43/g" $(egrep -lo 'blacklist b43' /etc/modprobe.d/*)
sudo sed -i "s/blacklist ssb/#blacklist ssb/g" $(egrep -lo 'blacklist ssb' /etc/modprobe.d/*)
sudo sed -i "s/blacklist bcma/#blacklist bcma/g" $(egrep -lo 'blacklist bcma' /etc/modprobe.d/*)

########################################################################################################
网卡的驱动属于外设驱动，可到 System > Administration > Hardware/Additional Drivers
查看网卡状态，ubuntu 14.04，是在  系统设置 > 软件和更新 > 附加驱动 查看
4: 网卡故障时，终端显示情况实例
sudo iwconfig 
lo
    no wireless extensions.
eth0
    no wireless extensions.
wlan0
    IEEE 802.11abgn  ESSID:off/any 
    Mode:Managed  Access Point: Not-Associated   Tx-Power=15 dBm
    Retry  long limit:7   RTS thr:off   Fragment thr:off
    Encryption key:off
    Power Management:off
wlan1
    IEEE 802.11bgn  ESSID:off/any
    Mode:Managed  Access Point: Not-Associated   Tx-Power=20 dBm
    Retry  long limit:7   RTS thr=2347 B   Fragment thr:off
    Encryption key:off
    Power Management:off
Not-Associated   表示没连接到路由，可能是密码错误造成，请检查输入格式。
########################################################################################################
sudo lshw -c network
  *-network
       description: Wireless interface
       product: BCM4313 802.11bgn Wireless Network Adapter
       vendor: Broadcom Corporation
       physical id: 0
       bus info: pci@0000:03:00.0
       logical name: wlan0
       version: 01
       serial: 0c:84:dc:cf:83:73
       width: 64 bits
       clock: 33MHz
       capabilities: pm msi pciexpress bus_master cap_list ethernet physical wireless
       configuration: broadcast=yes driver=wl0 driverversion=6.30.223.141 (r415941) ip=192.168.1.102 latency=0 multicast=yes wireless=IEEE 802.11abg
       resources: irq:17 memory:f1600000-f1603fff
  *-network
       description: Ethernet interface
       product: RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller
       vendor: Realtek Semiconductor Co., Ltd.
       physical id: 0
       bus info: pci@0000:09:00.0
       logical name: eth0
       version: 07
       serial: c4:54:44:00:15:a0
       size: 10Mbit/s
       capacity: 1Gbit/s
       width: 64 bits
       clock: 33MHz
       capabilities: pm msi pciexpress msix vpd bus_master cap_list ethernet physical tp mii 10bt 10bt-fd 100bt 100bt-fd 1000bt 1000bt-fd autonegotiation
       configuration: autonegotiation=on broadcast=yes driver=r8169 driverversion=2.3LK-NAPI duplex=half firmware=rtl8168e-3_0.0.4 03/27/12 latency=0 link=no multicast=yes port=MII speed=10Mbit/s
########################################################################################################
sudo lspci -vnn -d 14e4:
Network controller [0280]: Broadcom Corporation BCM4313 802.11bgn Wireless Network Adapter [14e4:4727] (rev 01)
    Subsystem: Broadcom Corporation Device [14e4:0608]
    Flags: bus master, fast devsel, latency 0, IRQ 17
    Memory at f1600000 (64-bit, non-prefetchable) [size=16K]
    Capabilities: [40] Power Management version 3
    Capabilities: [58] Vendor Specific Information: Len=78
    Capabilities: [48] MSI: Enable- Count=1/1 Maskable- 64bit+
    Capabilities: [160] Device Serial Number 00-00-dc-ff-ff-cf-0c-84
    Capabilities: [16c] Power Budgeting 
    Kernel driver in use: wl
