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
