# ubuntu 常用工具
####导读：
> [ubuntu]()目前最新版本是15.04
##1.ubuntu 15.04 install pkg
- 删除libreoffice
    - sudo apt-get remove libreoffice-common
- 删除Amazon的链接
    - sudo apt-get remove unity-webapps-common 
- 删掉基本不用的自带软件
    - sudo apt-get remove thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku landscape-client-ui-install onboard deja-dup
- 安装Vim
    - sudo apt-get install vim
- 设置时间使用UTC
    - sudo vim /etc/default/rcS | 将UTC=no改为UTC=yes 
- 安装Chrome
    - wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
    - sudo apt-get install libappindicator1 libindicator7
    - sudo dpkg -i google-chrome-stable_current_amd64.deb   
    - sudo apt-get -f install
- chromium-browser
    - sudo apt-get install chromium-browser
- 安装搜狗输入法
    - vim /etc/apt/sources.list.d/ubuntukylin.list文件，加入ubuntu kylin的apt源
    - deb http://archive.ubuntukylin.com:10006/ubuntukylin trusty main
    - sudo apt-get update  
    - sudo apt-get install sogoupinyin
- 安装fcitx-pinyin
    - sudo apt-get install fcitx-pinyin
    - [Ubuntu 14.04 安装小企鹅输入法 Fcitx](http://my.oschina.net/eechen/blog/224291)
- 安装WPS Office
    - sudo apt-get install wps-office
- 安装Oracle Java
    - sudo add-apt-repository ppa:webupd8team/java    
    - sudo apt-get update    
    - sudo apt-get install oracle-java8-installer
    - sudo update-alternatives --config java | install 
- 安装Sublime Text 3
    - sudo add-apt-repository ppa:webupd8team/sublime-text-3    
    - sudo apt-get update    
    - sudo apt-get install sublime-text 
- 安装经典菜单指示器
    - sudo add-apt-repository ppa:diesch/testing  
    - sudo apt-get update  
    - sudo apt-get install classicmenu-indicator 
- 安装系统指示器SysPeek
    - sudo add-apt-repository ppa:nilarimogard/webupd8    
    - sudo apt-get update    
    - sudo apt-get install syspeek    
- 自定义DHCP网络的DNS Server IP地址
    - sudo vim /etc/dhcp/dhclient.conf文件，在第21行#prepend domain-name-servers 127.0.0.1;下一行添加如下3行使用aliyun和Google的DNS
    - prepend domain-name-servers 8.8.8.8;  
    - prepend domain-name-servers 223.5.5.5; 
    - 这样可以优先使用aliyun的dns，次要使用Google的DNS。
- 安装git和vpnc
    - sudo apt-get install vpnc git  
- 安装CMake和Qt Creator
    - sudo apt-get install cmake qtcreator 
- [Ubuntu上让Firefox使用Chrome最新版PepperFlash插件](http://my.oschina.net/eechen/blog/365324)
- [Ubuntu 14.04 安装 Nvidia 私有驱动并进行双显卡切换](http://my.oschina.net/eechen/blog/227134)
 
## ubuntu apt update and install
- sudo apt-get update
- sudo apt-get install emacs vim git gitk retext qemu w3m w3m-el markdown tree
- sudo apt-cache search linux-source

# ubuntu misc
  gsettings set com.canonical.Unity.Launcher launcher-position Bottom