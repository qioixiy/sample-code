## valgrind

#### valgrind for arm linux
1. download
wget http://valgrind.org/downloads/valgrind-3.10.1.tar.bz2

2. configure
./configure --host=armv7-linux CC=arm-linux-gnueabihf-gcc --prefix=/opt/valgrind

3. make and install
sudo make install
