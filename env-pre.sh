#!/bin/bash

# refs: https://github.com/arut/nginx-rtmp-module/wiki/Getting-started-with-nginx-rtmp

WORK_DIR=`pwd`/out
NGINX_VERSION=nginx-1.14.1.tar.gz
NGINX_URL=http://nginx.org/download/$NGINX_VERSION
NGINX_DIR=`basename $NGINX_VERSION .tar.gz`

function get_cpu_num()
{
    echo `cat /proc/cpuinfo |grep "processor"|sort -u| wc -l`
}

#download nginx
[ -f $NGINX_VERSION ] || wget $NGINX_URL
tar xzf $NGINX_VERSION

# download nginx-rtmp-module
[ -d nginx-rtmp-module ] || git clone git://github.com/arut/nginx-rtmp-module.git

# build nginx with rtmp module
[ -f $WORK_DIR/sbin/nginx ] || {
pushd $NGINX_DIR
./configure --prefix=$WORK_DIR --with-http_ssl_module --add-module=../nginx-rtmp-module
make -j$get_cpu_num
make install
popd
}
cp nginx.conf $WORK_DIR/conf/nginx.conf

# get test 264 file
[ -f test.264 ] || wget http://www.live555.com/liveMedia/public/264/test.264

# run
sudo $WORK_DIR/sbin/nginx -s stop
sudo $WORK_DIR/sbin/nginx
