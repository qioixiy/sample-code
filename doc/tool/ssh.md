## ssh proxy
- ssh -f -C2qTnN -D localport <username>@<remote SSH server>
- ssh -f -C2qTnN -D 8000 ubuntu@54.65.203.95 -i ubuntu-pem-key.pem
```
-f 后台运行
-C 压缩
-2 只支持版本2协议
-q 静默模式
-T 禁用伪终端分配
-n 阻止从标准输入读取。后台运行的话，必须使用
-N 不执行远程命令
-D [bind_address : ] port 本地动态应用级端口转发。没有指定address将监听在127.0.0.1上
```
## ssh gateway ports
```
/etc/ssh/sshd_config
GatewayPorts yes
```

## common
- tar -zc dir | ssh 10.0.2.2 "cat - > ~/dir"

## url
- [ssh user](https://www.fastssh.com/page/secure-shell-servers)
