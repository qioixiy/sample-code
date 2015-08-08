## 挂载在win xp下share的目录
```
#!/bin/sh
sudo mount -o dir_mode=01777,file_mode=01777,username=zxyuan,password=  //192.168.0.106/share /home/qioixiy/myspace/share-xp
```
