## docker
- 查看运行的容器 `docker ps -a`
- docker用ubuntu:15.04镜像跑进一个container里
```
sudo docker run -i -t -p 18080:8080 -v /home:/hostfs ubuntu:15.04 /bin/bash`
-p 18080:8080 将容器8080端口映射到主机18080端口
-i -t是进入这个container
-d 后台运行
-v 将主机的目录或者文件挂载为容器数据卷或者在容器中增加数据卷
```

## docker vnc
- From Docker Index `docker pull dorowu/ubuntu-desktop-lxde-vnc`
- Build yourself `git clone https://github.com/fcwu/docker-ubuntu-vnc-desktop.git`
- build `docker build --rm -t dorowu/ubuntu-desktop-lxde-vnc docker-ubuntu-vnc-desktop`
- run `docker run -i -t -p 6080:6080 dorowu/ubuntu-desktop-lxde-vnc`
- Browse [vnc.html](http://127.0.0.1:6080/vnc.html)
