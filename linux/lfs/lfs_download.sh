#!/bin/sh

function get_date_string()
{
    #date -v -1d "+%Y%m%d%n"
    #date -d "1 day ago" +"%y%m%d"
    case "`uname`" in
        Linux) date -d "${time} day ago" +"%y%m%d" ;;
        Darwin) date -v -${time}d "+%Y%m%d%n" ;;
        *) echo "unsupport" ;;
    esac
}

function lfs_download()
{
    time=$1
    URL_PATH="http://www.linuxfromscratch.org/lfs/downloads/systemd/"
    url=${URL_PATH}${PREFIX}

    PREFIX=$(get_date_string $time)
    PREFIX_DATE=${PREFIX}
    NAMES="
LFS-BOOK-${PREFIX_DATE}-systemd-NOCHUNKS.html
LFS-BOOK-${PREFIX_DATE}-systemd-NOCHUNKS.html.bz2
LFS-BOOK-${PREFIX_DATE}-systemd.pdf
LFS-BOOK-${PREFIX_DATE}-systemd.tar.bz2
"
    LAST_DIR=$PWD

    if [ -d $PREFIX ]; then
        return 0
    fi

    mkdir -p $PREFIX
    pushd $PREFIX 2>&1 > /dev/null

    ret=0
    for NAME in ${NAMES};
    do
        wget ${URL_PATH}${NAME}
        if [ "$?" != "0" ]; then
            ret=1
            rm -rvf $LAST_DIR/$PREFIX
            break;
        fi
    done
    popd

    return $ret
}

time=0
while [ true ];
do
    lfs_download $time
    if [ "$?" == "0" ]; then
        echo done
        break
    fi

    time=$((time+1))
    echo "try $time"
done
