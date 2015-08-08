# Linux下更新firefox
1. download from http://www.firefox.com.cn/download/
2. 解压安装包: tar jxfv Firefox-latest.tar.bz2
3. 解压得 firefox 目录, 替换原来的firefox
    - $ cd /usr/lib
    - $ sudo mv firefox firefox-old  #将来的命名为firefox-old
    - $ sudo mv <解压路径>/firefox firefox-new  #将解压的firefox目录移动到/usr/lib路径下
    - $ sudo ln -s firefox-new firefox
4. 重新启动firefox生效
5. 说明：
    为什么我们只要一替换/usr/lib/firefox就可以生效？我们用type查看firefox命令
$ type firefox, firefox is /usr/bin/firefox, 打开/usr/bin/firefox文件可以分析得出，它就是调用了/usr/lib/firefox/目录中的 firefox，所以只要替换了/usr/lib/firefox目录就可达到替换版本的目的
