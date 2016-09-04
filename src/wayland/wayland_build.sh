#!/bin/sh

function export_env()
{
    export WLD=$HOME/install   # change this to another location if you prefer
    export LD_LIBRARY_PATH=$WLD/lib
    export PKG_CONFIG_PATH=$WLD/lib/pkgconfig/:$WLD/share/pkgconfig/
    export PATH=$WLD/bin:$PATH
    export ACLOCAL_PATH=$WLD/share/aclocal
    export ACLOCAL="aclocal -I $ACLOCAL_PATH"

    echo $WLD

    mkdir -p $WLD/share/aclocal # needed by autotools
}

function xorg_macros_build()
{
    # needed by libxcb:
    git clone git://anongit.freedesktop.org/xorg/util/macros
    cd macros
    ./autogen.sh --prefix=$WLD
    make && make install
    cd ..
}

function build_drm()
{
    # sudo apt-get install libpciaccess-dev # needed by drm
    # git clone git://anongit.freedesktop.org/git/mesa/drm
    cd drm
    ./autogen.sh --prefix=$WLD
    make && sudo make install
    cd ..
}

function build_wayland()
{
    # wayland
    # git clone git://anongit.freedesktop.org/wayland/wayland
    cd wayland
    ./autogen.sh --prefix=$WLD
    make && make install
    cd ..
}

function build_mesa()
{
    # mesa
    # git clone git://anongit.freedesktop.org/mesa/mesa
    cd mesa
    ./autogen.sh --prefix=$WLD --enable-gles2 --disable-gallium-egl \
                 --with-egl-platforms=x11,wayland,drm --enable-gbm --enable-shared-glapi \
                 --with-gallium-drivers=r300,r600,swrast,nouveau
    make && make install
    cd ..
}

function build_libunwind()
{
    # libunwind
    # git clone git://git.sv.gnu.org/libunwind
    cd libunwind
    autoreconf -i
    ./configure --prefix=$WLD
    make && make install
    cd ..
}

function build_libinput()
{
    # libinput
    # git clone git://anongit.freedesktop.org/wayland/libinput
    cd libinput
    ./autogen.sh --prefix=$WLD
    make && make install
    cd ..
}

function build_weston()
{
    # git clone git://anongit.freedesktop.org/wayland/weston
    cd weston
    ./autogen.sh --prefix=$WLD
    make
    sudo make install
    cd ..
}

function run()
{
    # run
    if test -z "${XDG_RUNTIME_DIR}"; then
        export XDG_RUNTIME_DIR=/tmp/${UID}-runtime-dir
        if ! test -d "${XDG_RUNTIME_DIR}"; then
            mkdir "${XDG_RUNTIME_DIR}"
            chmod 0700 "${XDG_RUNTIME_DIR}"
        fi
    fi
    mkdir -p ~/.config
    cp weston/weston.ini ~/.config
    #$EDITOR ~/.config/weston.ini

    weston
}

function debug()
{
    export MESA_DEBUG=1
    export EGL_LOG_LEVEL=debug
    export LIBGL_DEBUG=verbose
    export WAYLAND_DEBUG=1
}

## main
# debug
export_env
xorg_macros_build
build_drm
build_wayland
build_mesa
build_libunwind
build_libinput
build_weston
run
