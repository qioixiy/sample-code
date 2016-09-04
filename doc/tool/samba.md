## install
- sudo apt-get install samba

## configure
- mkdir /home/share
- chmod -R 777 /home/share # 若不更改权限，windows下不能写入（适用于只读共享）
- cp /etc/samba/smb.conf /etc/samba/smb.conf.bak   # 备份samba的配置文件
- gedit /etc/samba/smb.conf
- 在配置文件的最后加入以下内容(不包含行末注释说明部份)
[share]                        # 共享文件名，可自定义，与共享目录名可不一致
    comment=VMware Ubuntu Share    # 共享说明，可自定义
    path=/home/share               # 共享目录，应与之前创建的一致，必须为绝对路径
    public=yes                     # 允许所有人都能够看到此目录
    writable=yes                   # 允许用户在此目录下可写
    browseable = yes            # 允许浏览

最后因为没有使用用户验证，所以建议在配置文件中新增 hosts allow = 127. 192.168.122.
以增加授权IP访问。这样就很安全了

## restart
sudo /etc/init.d/smbd restart
\\192.168.128.128\share

## url
http://www.526net.com/blog/xitong/562.html
