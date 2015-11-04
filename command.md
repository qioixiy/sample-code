## lsof
* `lsof -Pnl -i[4|6]`: This will list all open ports, the programs that opened the ports

## netstat
* `netstat -tunpl`: list all local ports that have listening programs

## nethogs
- Net top tool grouping bandwidth per process

## 恢复打开后但意外删除文件
* ps -ef | grep exe | grep -v grep
* ls -rtl /proc/9554/fd
* cp /proc//9554/fd/268 ./file.bak

## find
* `find . -type f -name *.c -exec mv {} {}pp \;`
* `find . -type f -name *.cpp | xargs -n 1 rename 's/\.cpp$/.c/' \;`

## media,yuv rgb
* vooya

## sed
*  字符串替换: `sed "s/\.c$/\.cpp/g" service/CMakeLists.txt -i`

## dpkg
* list pkg file:`dpkg -L *`
* search * 所在的包:`apt-file search *`

## xargs
* `ls *.bz2 | xargs -t -i sudo tar jxf {} -C /`
* -t 显示每一条执行的命令
* -i 将输入的每一行在{}处出现

## bash
* bash内置函数: [url](http://blog.csdn.net/hejinjing_tom_com/article/details/16116455)
* 执行前打印: `bash -x`
* 只运行不执行: `bash -n`
* Linux文本工具简化数据提取: [url](http://www.ibm.com/developerworks/cn/linux/l-textutils.html)

## cut
- 以空格为列的分隔符,提取第二列: `cut -d" " -f2 filename`

## awk
- awk默认以空格为分隔符,打印第二列: `awk '{print $2}' filename`

## nc
- 远程拷贝文件
- `server: nc -lp 1234 > install.log`
- `client: nc -w 1 192.168.228.222 1234 < install.log`

## nmon
- nmob is is a systems administrator, tuner, benchmark tool.
It can display the CPU, memory, network, disks (mini graphs or numbers),
file systems, NFS, top processes, resources (Linux version & processors) and on Power micro-partition information.

## route|tunctl
- `sudo route add default gw 192.168.1.1`
- tunctl

## uuidgen|tune2fs
- Linux生成分区UUID
- uuidgen会返回一个合法的uuid，结合tune2fs可以新生成一个uuid并写入ext[234]分区中
- `uuidgen | xargs tune2fs /dev/sda[0-9] -U`
- 也可以把 fstab 里找到的原 uuid 写回分区: `tune2fs -U $UUID /dev/sda[0-9]`

## replase string
- 把/test下所有包含abc的文件中的abc替换为def，执行命令：
- ``sed -n "s/abc/def/g" `grep abc -rl /test``
- -i 生成备份文件
- -n quit print
- `grep "abc" * -r | awk -F: '{print $1}' | sort | uniq | xargs sed -i 's/abc/abcde/g'`

## git
* 压合提交，将多次dev提交merge到master分支为一个提交记录
`
git checkout master
git merge --squash dev
git commit –m "commit"
`
* 拣选合并
`
git checkout master
git cherry-pick 321d76f [git cherry-pick –n 321d76f 需要多次拣选]
git commit –m "commit"
`

## shell expr
- echo mothed: `echo "2+1-5*1.111" | bc`
- here-doc mothed: `bc <<< "1+2+3+3.3333"`
- awk mothed: ```var=`echo "$var 5"|awk '{printf("%g",$1+$2)}'```

## system monitor
- `iostat`: Report Central Processing Unit (CPU) statistics and input/output statistics for devices and partitions)
- `vmstat 1 10`: vmstat - Report virtual memory statistics
- buffer回收: `echo 3 >/proc/sys/vm/drop_caches`

## linux memory
- `cat /proc/$pid/smaps  | awk '/Size|Rss|Pss|Shared|Private|Referenced|Swap/{val_name=gensub(/([a-zA-Z_]*).*/,"\\1",1,$1); list[val_name]+=$2; }END{for(val in list)print val,list[val];}''`
- `cat /proc/$pid/maps`
- `cat /proc/$pid/statm`

## linux /proc/sys/vm
- /proc/sys/vm/block_dump
> 该文件表示是否打开Block Debug模式，用于记录所有的读写及Dirty Block写回动作。
> 缺省设置：0，禁用Block Debug模式
- /proc/sys/vm/dirty_background_ratio
> 该文件表示脏数据到达系统整体内存的百分比，此时触发pdflush进程把脏数据写回磁盘。
> 缺省设置：10
- /proc/sys/vm/dirty_expire_centisecs
> 该文件表示如果脏数据在内存中驻留时间超过该值，pdflush进程在下一次将把这些数据写回磁盘。
> 缺省设置：3000（1/100秒）
- /proc/sys/vm/dirty_ratio
> 该文件表示如果进程产生的脏数据到达系统整体内存的百分比，此时进程自行把脏数据写回磁盘。
> 缺省设置：40
- /proc/sys/vm/dirty_writeback_centisecs
> 该文件表示pdflush进程周期性间隔多久把脏数据写回磁盘。
> 缺省设置：500（1/100秒）
- /proc/sys/vm/vfs_cache_pressure
> 该文件表示内核回收用于directory和inode cache内存的倾向；缺省值100表示内核将根据pagecache和swapcache，
> 把directory和inode cache保持在一个合理的百分比；降低该值低于100，将导致内核倾向于保留directory和inode cache；
> 增加该值超过100，将导致内核倾向于回收directory和inode cache
> 缺省设置：100
- /proc/sys/vm/min_free_kbytes
> 该文件表示强制Linux VM最低保留多少空闲内存（Kbytes）。
> 缺省设置：724（512M物理内存）
- /proc/sys/vm/nr_pdflush_threads
> 该文件表示当前正在运行的pdflush进程数量，在I/O负载高的情况下，内核会自动增加更多的pdflush进程。
> 缺省设置：2（只读）
- /proc/sys/vm/overcommit_memory
> 该文件指定了内核针对内存分配的策略，其值可以是0、1、2。
> 0， 表示内核将检查是否有足够的可用内存供应用进程使用；如果有足够的可用内存，内存申请允许；否则，内存申请失败，并把错误返回给应用进程。
> 1， 表示内核允许分配所有的物理内存，而不管当前的内存状态如何。
> 2， 表示内核允许分配超过所有物理内存和交换空间总和的内存（参照overcommit_ratio）。
> 缺省设置：0
- /proc/sys/vm/overcommit_ratio
> 该文件表示，如果overcommit_memory=2，可以过载内存的百分比，通过以下公式来计算系统整体可用内存。
> 系统可分配内存=交换空间+物理内存*overcommit_ratio/100
> 缺省设置：50（%）
- /proc/sys/vm/page-cluster
> 该文件表示在写一次到swap区的时候写入的页面数量，0表示1页，1表示2页，2表示4页。
> 缺省设置：3（2的3次方，8页）
- /proc/sys/vm/swapiness
> 该文件表示系统进行交换行为的程度，数值（0-100）越高，越可能发生磁盘交换。
- MSGMNB: 每个消息队列的最大字节限制。
- MSGMNI: 整个系统的最大数量的消息队列。
- MSGGSZ: 消息片断的大小（字节）。大于该值的消息被分割成多个片断。
- MSGSEG: 在单个队列里能存在的最大数量的消息片断。
- MSGTQL: 整个系统的最大数量的消息。
- MSGMAX: 单个消息的最大size。在某些操作系统例如BSD中，你不必设置这个。BSD自动设置它为MSGSSZ * MSGSEG。其他操作系统中，你也许需要改变这个参数的默认值，你可以设置它与MSGMNB相同。
- SHMSEG: 每个进程的最大数量的共享内存片断。
- SHMMNI: 共享内存片断数量的系统级的限制。
- SHMMAX: 单个共享内存片断的最大size。
- SHMALL: 可分配的共享内存数量的系统级限制。在某些系统上，SHMALL可能表示成页数量，而不是字节数量。
- 在Linux上配置消息队列，增加下列行到/etc/sysctl.conf：
```
kernel.msgmnb=8192
kernel.msgmni=40
kernel.msgmax=8192
kernel.shmall=2097152
kernel.shmmni=32
kernel.shmmax=16777216
```
- 运行:
`insserv boot.sysctl`
`boot.sysctl start`

## /proc/sys/kernel/ 优化
- /proc/sys/kernel/ctrl-alt-del
> 该文件有一个二进制值，该值控制系统在接收到ctrl+alt+delete按键组合时如何反应。这两个值分别是：
> 0 表示捕获ctrl+alt+delete，并将其送至 init 程序；这将允许系统可以安全地关闭和重启，就好象输入shutdown命令一样。
> 1 表示不捕获ctrl+alt+delete，将执行非正常的关闭，就好象直接关闭电源一样。
> 缺省设置：0
> 建议设置：1，防止意外按下ctrl+alt+delete导致系统非正常重启。
- proc/sys/kernel/msgmax
> 该文件指定了从一个进程发送到另一个进程的消息的最大长度（bytes）。进程间的消息传递是在内核的内存中进行的，不会交换到磁盘上，所以如果增加该值，则将增加操作系统所使用的内存数量。
> 缺省设置：8192
- /proc/sys/kernel/msgmnb
> 该文件指定一个消息队列的最大长度（bytes）。
> 缺省设置：16384
- /proc/sys/kernel/msgmni
> 该文件指定消息队列标识的最大数目，即系统范围内最大多少个消息队列。
> 缺省设置：16
- /proc/sys/kernel/panic
> 该文件表示如果发生“内核严重错误（kernel panic）”，则内核在重新引导之前等待的时间（以秒为单位）。
> 0 表示在发生内核严重错误时将禁止自动重新引导。
> 缺省设置：0
- proc/sys/kernel/shmall
> 该文件表示在任何给定时刻，系统上可以使用的共享内存的总量（bytes）。
> 缺省设置：2097152
- /proc/sys/kernel/shmmax
> 该文件表示内核所允许的最大共享内存段的大小（bytes）。
> 缺省设置：33554432
> 建议设置：物理内存 * 50%
> 实际可用最大共享内存段大小=shmmax * 98%，其中大约2%用于共享内存结构。
> 可以通过设置shmmax，然后执行ipcs -l来验证。
- /proc/sys/kernel/shmmni
> 该文件表示用于整个系统的共享内存段的最大数目（个）。
> 缺省设置：4096
- /proc/sys/kernel/threads-max
> 该文件表示内核所能使用的线程的最大数目。
> 缺省设置：2048
- /proc/sys/kernel/sem
> 该文件用于控制内核信号量，信号量是System VIPC用于进程间通讯的方法。
> 建议设置：250 32000 100 128
> 第一列，表示每个信号集中的最大信号量数目。
> 第二列，表示系统范围内的最大信号量总数目。
> 第三列，表示每个信号发生时的最大系统操作数目。
> 第四列，表示系统范围内的最大信号集总数目。
> 所以，（第一列）*（第四列）=（第二列）
> 以上设置，可以通过执行ipcs -l来验证。

## /proc/sys/vm/优化
- /proc/sys/vm/block_dump
> 该文件表示是否打开Block Debug模式，用于记录所有的读写及Dirty Block写回动作。
> 缺省设置：0，禁用Block Debug模式
- /proc/sys/vm/dirty_background_ratio
> 该文件表示脏数据到达系统整体内存的百分比，此时触发pdflush进程把脏数据写回磁盘。
> 缺省设置：10
- /proc/sys/vm/dirty_expire_centisecs
> 该文件表示如果脏数据在内存中驻留时间超过该值，pdflush进程在下一次将把这些数据写回磁盘。
> 缺省设置：3000（1/100秒）
- /proc/sys/vm/dirty_ratio
> 该文件表示如果进程产生的脏数据到达系统整体内存的百分比，此时进程自行把脏数据写回磁盘。
> 缺省设置：40
- /proc/sys/vm/dirty_writeback_centisecs
> 该文件表示pdflush进程周期性间隔多久把脏数据写回磁盘。
> 缺省设置：500（1/100秒）
- /proc/sys/vm/vfs_cache_pressure
> 该文件表示内核回收用 于directory和inode cache内存的倾向；缺省值100表示内核将根据pagecache和swapcache，把directory和inode cache保持在一个合理的百分比；降低该值低于100，将导致内核倾向于保留directory和inode cache；增加该值超过100，将导致内核倾向于回收directory和inode cache。
> 缺省设置：100
- /proc/sys/vm/min_free_kbytes
> 该文件表示强制Linux VM最低保留多少空闲内存（Kbytes）。
> 缺省设置：724（512M物理内存）
- /proc/sys/vm/nr_pdflush_threads
> 该文件表示当前正在运行的pdflush进程数量，在I/O负载高的情况下，内核会自动增加更多的pdflush进程。
> 缺省设置：2（只读）
- /proc/sys/vm/overcommit_memory
> 该文件指定了内核针对内存分配的策略，其值可以是0、1、2。
> 0， 表示内核将检查是否有足够的可用内存供应用进程使用；如果有足够的可用内存，内存申请允许；否则，内存申请失败，并把错误返回给应用进程。
> 1， 表示内核允许分配所有的物理内存，而不管当前的内存状态如何。
> 2， 表示内核允许分配超过所有物理内存和交换空间总和的内存（参照overcommit_ratio）。
> 缺省设置：0
- /proc/sys/vm/overcommit_ratio
> 该文件表示，如果overcommit_memory=2，可以过载内存的百分比，通过以下公式来计算系统整体可用内存。
> 系统可分配内存=交换空间+物理内存*overcommit_ratio/100
> 缺省设置：50（%）
- /proc/sys/vm/page-cluster
> 该文件表示在写一次到swap区的时候写入的页面数量，0表示1页，1表示2页，2表示4页。
> 缺省设置：3（2的3次方，8页）
- /proc/sys/vm/swapiness
> 该文件表示系统进行交换行为的程度，数值（0-100）越高，越可能发生磁盘交换。
> 缺省设置：60
- legacy_va_layout
> 该文件表示是否使用最新的32位共享内存mmap()系统调用，Linux支持的共享内存分配方式包括mmap()，Posix，System VIPC。
> 0， 使用最新32位mmap()系统调用。
> 1， 使用2.4内核提供的系统调用。
> 缺省设置：0
- nr_hugepages
> 该文件表示系统保留的hugetlb页数。
- hugetlb_shm_group
> 该文件表示允许使用hugetlb页创建System VIPC共享内存段的系统组ID。

## /proc/sys/fs/优化
- /proc/sys/fs/file-max
> 该文件指定了可以分配的文件句柄的最大数目。如果用户得到的错误消息声明由于打开
> 文件数已经达到了最大值，从而他们不能打开更多文件，则可能需要增加该值。
> 缺省设置：4096
> 建议设置：65536
- /proc/sys/fs/file-nr
> 该文件与 file-max 相关，它有三个值：
> 已分配文件句柄的数目
> 已使用文件句柄的数目
> 文件句柄的最大数目
> 该文件是只读的，仅用于显示信息。

## /proc/sys/net/core/ 优化
- 该目录下的配置文件主要用来控制内核和网络层之间的交互行为。
- /proc/sys/net/core/message_burst
> 写新的警告消息所需的时间（以 1/10 秒为单位）；在这个时间内系统接收到的其它警告消息会被丢弃。这用于防止某些企图用消息“淹没”系统的人所使用的拒绝服务（Denial of Service）攻击。
> 缺省设置：50（5秒）
- /proc/sys/net/core/message_cost
> 该文件表示写每个警告消息相关的成本值。该值越大，越有可能忽略警告消息。
> 缺省设置：5
- /proc/sys/net/core/netdev_max_backlog
> 该文件表示在每个网络接口接收数据包的速率比内核处理这些包的速率快时，允许送到队列的数据包的最大数目。
> 缺省设置：300
- /proc/sys/net/core/optmem_max
> 该文件表示每个套接字所允许的最大缓冲区的大小。
> 缺省设置：10240
- /proc/sys/net/core/rmem_default
> 该文件指定了接收套接字缓冲区大小的缺省值（以字节为单位）。
> 缺省设置：110592
- /proc/sys/net/core/rmem_max
> 该文件指定了接收套接字缓冲区大小的最大值（以字节为单位）。
> 缺省设置：131071
- /proc/sys/net/core/wmem_default
> 该文件指定了发送套接字缓冲区大小的缺省值（以字节为单位）。
> 缺省设置：110592
- /proc/sys/net/core/wmem_max
> 该文件指定了发送套接字缓冲区大小的最大值（以字节为单位）。
> 缺省设置：131071

## /proc/sys/net/ipv4/ 优化
- /proc/sys/net/ipv4/ip_forward
> 该文件表示是否打开IP转发。
> 0，禁止
> 1，转发
> 缺省设置：0
- /proc/sys/net/ipv4/ip_default_ttl
> 该文件表示一个数据报的生存周期（Time To Live），即最多经过多少路由器。
> 缺省设置：64
> 增加该值会降低系统性能。
- /proc/sys/net/ipv4/ip_no_pmtu_disc
> 该文件表示在全局范围内关闭路径MTU探测功能。
> 缺省设置：0
- /proc/sys/net/ipv4/route/min_pmtu
> 该文件表示最小路径MTU的大小。
> 缺省设置：552
- /proc/sys/net/ipv4/route/mtu_expires
> 该文件表示PMTU信息缓存多长时间（秒）。
> 缺省设置：600（秒）
- /proc/sys/net/ipv4/route/min_adv_mss
> 该文件表示最小的MSS（Maximum Segment Size）大小，取决于第一跳的路由器MTU。
> 缺省设置：256（bytes）

## IP Fragmentation
- /proc/sys/net/ipv4/ipfrag_low_thresh/proc/sys/net/ipv4/ipfrag_low_thresh
> 两个文件分别表示用于重组IP分段的内存分配最低值和最高值，一旦达到最高内存分配值，其它分段将被丢弃，直到达到最低内存分配值。
> 缺省设置：196608（ipfrag_low_thresh）
> 　　　　　262144（ipfrag_high_thresh）
- /proc/sys/net/ipv4/ipfrag_time
> 该文件表示一个IP分段在内存中保留多少秒。
> 缺省设置：30（秒）

## INET Peer Storage
- /proc/sys/net/ipv4/inet_peer_threshold
> INET对端存储器某个合适值，当超过该阀值条目将被丢弃。该阀值同样决定生存时间以及废物收集通过的时间间隔。条目越多，存活期越低，GC 间隔越短.
> 缺省设置：65664
- /proc/sys/net/ipv4/inet_peer_minttl
> 条目的最低存活期。在重组端必须要有足够的碎片(fragment)存活期。这个最低存活期必须保证缓冲池容积是否少于 inet_peer_threshold。该值以 jiffies为单位测量。
> 缺省设置：120
- /proc/sys/net/ipv4/inet_peer_maxttl
> 条目的最大存活期。在此期限到达之后，如果缓冲池没有耗尽压力的话(例如：缓冲池中的条目数目非常少)，不使用的条目将会超时。该值以 jiffies为单位测量。
> 缺省设置：600
- /proc/sys/net/ipv4/inet_peer_gc_mintime
> 废物收集(GC)通过的最短间隔。这个间隔会影响到缓冲池中内存的高压力。 该值以 jiffies为单位测量。
> 缺省设置：10

## 2>&1使用
1. 默认地，标准的输入为键盘，但是也可以来自文件或管道（pipe |）。
2. 默认地，标准的输出为终端（terminal)，但是也可以重定向到文件，管道或后引号（backquotes \`）。
3. 默认地，标准的错误输出到终端，但是也可以重定向到文件。
4. 标准的输入，输出和错误输出分别表示为STDIN,STDOUT,STDERR，也可以用0，1，2来表示。
5. 其实除了以上常用的3中文件描述符，还有3~9也可以作为文件描述符。3~9你可以认为是执行某个地方的文件描述符，常被用来作为临时的中间描述符。
- 实例
1. command 2>errfile : command的错误重定向到文件errfile。
2. command 2>&1 | ...: command的错误重定向到标准输出，错误和标准输出都通过管道传给下个命令。
3. var=`command 2>&1`: command的错误重定向到标准输出，错误和标准输出都赋值给var。
4. command 3>&2 2>&1 1>&3 | ...:实现标准输出和错误输出的交换。
5. var=`command 3>&2 2>&1 1>&3`:实现标准输出和错误输出的交换。
6. command 2>&1 1>&2 | ...     (wrong...) :这个不能实现标准输出和错误输出的交换。因为shell从左到右执行命令，当执行完2>&1后，错误输出已经和标准输出一样的，再执行1>&2也没有意义。
#### "2>&1 file"和 "> file 2>&1"区别
1. cat food 2>&1 >file ：错误输出到终端，标准输出被重定向到文件file。
2. cat food >file 2>&1 ：标准输出被重定向到文件file，然后错误输出也重定向到和标准输出一样，所以也错误输出到文件file。
- 通常打开的文件在进程推出的时候自动的关闭，但是更好的办法是当你使用完以后立即关闭。用m<&-来关闭输入文件描述符m，用m>&-来关闭输出文件描述符m。如果你需要关闭标准输入用<&-; >&- 被用来关闭标准输出。
- 同时输出到终端和文件 copy source dest | tee.exe copyerror.txt

## Clam AntiVirus
- Clam AntiVirus is a GPL antivirus toolkit for UNIX

## urls
[Linux命令大全](http://man.linuxde.net/)
[unix comand](http://www.ugrad.cs.ubc.ca/~cs219/CourseNotes/Unix/intro.html)
