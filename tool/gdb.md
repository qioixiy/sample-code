## build gdb server
- [BuildingCrossGDBandGDBserver](https://sourceware.org/gdb/wiki/BuildingCrossGDBandGDBserver)
- example `./configure --target=arm-linux-gnueabihf
cd gdb/gdbserver && ./configure --host=arm-linux-gnueabihf`

##net debug
- `./gdbserver 192.168.2.100:2345 hello
(gdb) target remote 192.168.2.223:2345
`

##UART debug
- 
`gdbserver /dev/ttyO0 ./simple-touch
(gdb) target remote /dev/ttyUSB0
`

## debug macro
-gcc -ggdb3
-info macro

## source dir
directory: set source dir
$ apt-get sourcecoreutils
$ sudoapt-get installcoreutils-dbgsym
$ gdb /bin/ls
GNU gdb (GDB) 7.1-ubuntu
(gdb) list main
1192    ls.c: No such fileor directory.
inls.c
(gdb) directory ~/src/coreutils-7.4/src/
Source directories searched: /home/hchen/src/coreutils-7.4:$cdir:$cwd
(gdb) list main
1192        }
1193    }
1194
1195    int
1196    main (int argc, char **argv)
1197    {
1198      int i;
1199      struct pending *thispend;
1200      int n_files;

## condition breakpoint
break  [where] if [condition]

## command params
gdb * –args *
(gdb) set args *
set varname value
(gdb) set$i = 0
(gdb) p a[$i++]

## x command
x: view memory
(gdb)help x
x/x: hex output
x/d 以十进制输出
x/c 以单字符输出
x/i  反汇编
x/10i $ip-20 来查看当前的汇编（$ip是指令寄存器）
x/s 以字符串输出

## command command
(gdb) breakfunc
Breakpoint 1 at 0x3475678: filetest.c, line 12.
(gdb) command1
Type commands forwhen breakpoint 1 is hit, one per line.
End with a line saying just "end".
>print arg1
>print arg2
>print arg3
>end
(gdb)
will be auto run command1 when touch current breakpoint

## core env
uname -a 查看机器参数
ulimit -a 查看默认参数
ulimit -c 1024  设置core文件大小为1024
ulimit -c unlimit 设置core文件大小为无限
ulimit -c unlimited

##multi thread debug
(gdb)info thread: view current threads in process, every thread will
be accloc a gdb-id, * was current thread id
(gdb)thread <tid>: switch to thread id as current thread
break file.c:100 thread all: set a breakpoint in file.c about all threads
(gdb)set scheduler-locking off|on|step, off:not lock any thread(default
value), on:only current thread can be running, step: step to step in current thread
(gdb)thread apply ID1 ID2 command
(gdb)thread apply all command
(gdb)set scheduler-locking off|on|step
(gdb) bt
(gdb) f 3
(gdb) i locals

## log
(gdb) set logging file /tmp/gdb.txt
(gdb) set logging on
(gdb) set logging off
(gdb) set logging overwrite on
(gdb) thread apply all bt [full] [10]
(gdb) symbol-file /usr/bin/hello

## run sync
(gdb) break gdk_x_error
(gdb) run --sync

## gdb batch
gdb -p $(pidof X) -batch -ex 'handle all nostop' -ex 'handle all pass' -ex 'handle 11 stop' -ex 'cont' -ex 'bt full' -ex 'cont'

## url
[x gdb debug](http://wiki.x.org/wiki/Development/Documentation/ServerDebugging/)
