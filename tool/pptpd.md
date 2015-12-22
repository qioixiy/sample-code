## vpn with pptpd

## install pkg
apt-get pptpd

## conf
vi /etc/pptpd.conf
localip 10.100.0.1
remoteip 10.100.0.2-10

vi /etc/ppp/pptpd-options
ms-dns 202.113.16.10
ms-dns 208.67.222.222

vi /etc/ppp/chap-secrets
qioixiy pptpd password *

## restart
/etc/init.d/pptpd restart

## conf2
vi /etc/sysctl.conf
net.ipv4.ip_forward=1
sysctl -p

## iptables nat
apt-get intall iptables
iptables -t nat -A POSTROUTING -s 10.100.0.0/24 -o eth0 -j MASQUERADE
iptables-save > /etc/iptables-rules

## conf3
vi /etc/network/interfaces
eth0 section append this line end
pre-up iptables-restore < /etc/iptables-rules

## issue
安装好 pptpd 并设置后，客户端还是无法建立到服务器的连接。造成的原因可能有以下几种：
1. 服务器端的防火墙设置：PPTP 服务需要使用 1723(tcp) 端口和 gre 协议，因此请确保您的防火墙设置允许这两者通行。
2. 如果服务器在路由器后面，请确保路由器上做好相应的设置和端口转发。
3. 如果服务器在路由器后面，那么请确保你的服务器支持 VPN Passthrough。
4. 如果客户端在路由器后面，那么客户端所使用的路由器也必须支持 VPN Passthrough。其实市面上稍微好点的路由器都是支持 VPN Passthrough 的，当然也不排除那些最最最便宜的便宜货确实不支持。当然，如果你的路由器可以刷 DD-Wrt 的话就刷上吧，DD-Wrt 是支持的。能建立链接，但“几乎”无法访问互联,这里我使用“几乎”这个词，是因为并不是完全不能访问互联网。症状为，打开 Google 搜索没问题，但其它网站均无法打开；SSH 可用，但 scp 不行；ftp 能握手，但传不了文件。我就遇到了这种情况，仔细 Google 后发现原来是 MTU 的问题，用 ping 探测了一下果然是包过大了。知道问题就好办了，我们可以通过 iptables 来修正这一问题。具体原理就不讲了，需要的自己 Google。这里只说解决方案，在 filter 表中添加下面的规则：
iptables -A FORWARD -s 10.100.0.0/24 -p tcp -m tcp --tcp-flags SYN,RST SYN -j TCPMSS --set-mss 1200
上面规则中的 1200 可以根据你的实际情况修改，为了保证最好的网络性能，这个值应该不断修改，直至能保证网络正常使用情况下的最大值。

## url
http://blog.csdn.net/xanxus46/article/details/15288777
