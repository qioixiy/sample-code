## google android mirror
`
mkdir /usr/local/android-mirror
cd /usr/local/android-mirror
repo init --mirror -u https://android.googlesource.com/mirror/manifest
repo sync
mkdir /usr/local/android-2.3.7
cd /usr/local/android-2.3.7
repo init -u /usr/local/mirror/platform/manifest.git -b android-2.3.7_r1
repo sync
repo init -u https://android.googlesource.com/platform/manifest
repo sync
`

##
curl https://dl-ssl.google.com/dl/googlesource/git-repo/repo > ~/bin/repo
chmod a+x ~/bin/repo
mkdir WORKING_DIRECTORY
cd WORKING_DIRECTORY
repo init -u git://git.omapzoom.org/platform/manifest
repo init -u git://git.omapzoom.org/platform/manifest -b android-2.3.5_r1
repo sync

## Android Dev Tools[url](http://www.androiddevtools.cn)

## Eclipse+ADT+SDK+NDK, need select Force https://...sources to be fetched using http://...
HTTP Proxy Server: mirrors.neusoft.edu.cn
HTTP Proxy port: 80
http://mirrors.neusoft.edu.cn/android/repository/

## android-studio-ide

## android mirror
https://mirrors.tuna.tsinghua.edu.cn/help/
https://wiki.cyanogenmod.org/w/Development
