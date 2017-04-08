
# 安装Gerrit
## 配置数据库
- 当前使用Mysql,也可以使用h2就不需要单独配置数据库,直接进入安装步骤
创建数据库表和帐户
```
# 登录mysql
sh> mysql -u root -p

# 在mysql中建立一个以项目名称命名的用户gerrit2,密码为secret
mysql> CREATE USER 'gerrit2'@'localhost' IDENTIFIED BY 'secret';

# 在mysql中建立一个名为reviewdb_[项目名]库
mysql> CREATE DATABASE reviewdb;

# 将所有权限给刚才建立的新的库
mysql>GRANT ALL ON reviewdb.*TO'gerrit2'@'localhost';

# 刷新权限表
mysql>FLUSH PRIVILEGES;

## tips:较新版本的mysql需要执行 http://www.jianshu.com/p/154960f71d11
mysql> set global explicit_defaults_for_timestamp=1
```
## 安装
### 创建并切换到gerrit2用户, 一个以项目名称命名的新用户
```
sh> sudo adduser gerrit2
sh> sudo su gerrit2
sh> java -jar gerrit-2.13.war init -d /home/gerrit2/gerrit_testsite
```
```
使用官方Docment方法: gerrit/Documentation/install-quick.html
java -jar gerrit-2.13.war init --batch -d ~/gerrit_testsite
```
## nginx作为http反向代理服务器,验证ok. gerrit-2.13, nginx/1.10.3
```
[ref1](http://www.tuicool.com/articles/iAFBvu7)
[ref2](https://my.oschina.net/vdroid/blog/387126)
htpasswd -cb /home/gerrit2/gerrit_testsite/htpasswd.conf gerrit-first-username password
htpasswd -m /home/gerrit2/gerrit_testsite/htpasswd.conf master
cat <<EOF >> /etc/nginx/conf.d/gerrit.conf
server {
    listen *:81;
    server_name gerrit.localhost.com;
    allow   all;
    deny    all;

    auth_basic "Welcomme to Gerrit Code Review Site!";
    auth_basic_user_file /home/gerrit2/gerrit_testsite/htpasswd.conf;

    location / {
        proxy_pass  http://127.0.0.1:10000;
        proxy_set_header X-Forwarded-For $remote_addr;
        proxy_set_header Host $host;
    }
}
EOF
```
### 查看gerrit占用的端口
netstat -ltpn | grep -i gerrit
### 配置
- ~/gerrit/etc/gerrit.config
- `apache2 enable proxy module -> a2enmod proxy`
### tips
- canonicalWebUrl 就是gerrit的主页地址

## Project creation
- ssh -p 29418 user@localhost gerrit create-project demo-project --empty-commit

# resources
- [gerrit 2.13](https://gerrit-releases.storage.googleapis.com/gerrit-2.13.war)
- [gerrit github mirror](https://github.com/gerrit-review/gerrit)
- [CI 系统搭建：Git、Gerrit与Jenkins](http://blog.csdn.net/williamwanglei/article/details/38498465/)
