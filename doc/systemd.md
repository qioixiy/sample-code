## systemd
- systemctl sleep
- systemctl hibernate
- systemctl reboot
- systemctl suspend
- systemctl poweroff
- systemctl daemon-reload
- systemctl list-unit-files --type=service --all
- systemctl list-dependencies httpd.service
- systemctl reload httpd.service

## systemd journalctl
- journalctl --disk-usage : disk usage
- journalctl --all : 显示系统的完整日志及其所有用户
- journalctl -f : 显示系统日志的实时视图（相当于“tail -f /var/log/messages”）
- journalctl --list-boots : Show a tabular list of boot numbers
- journalctl -b : 显示上一次启动以来的日志
- journalctl -k -b -1 : 显示来自上一次启动前（-b -1）的所有内核日志
- journalctl -b -p err : 显示上一次启动的日志，仅限于优先级“ERROR”
- journalctl --since=yesterday : 由于Linux用户通常不经常重启，这比-b更加限制了大小
- journalctl -u cron.service --since='2014-07-06 07:00' --until='2014-07-06 08:23' : 显示了计划任务（cron）在指定时间段的日志
- journalctl -p 2 --since=today : 显示优先级2的日志，这包括emerg（最高的紧急程度状态）、alert（紧急状态）和crit（重要信息）
- journalctl > yourlog.log : 将二进制格式的系统日志作为文本拷贝到你的当前目录
- journalctl --vacuum-time=2d : Retain only the past two days
- journalctl --vacuum-time=1seconds : A very brute force method to clean the entire log
- journalctl --vacuum-size=500M : Retain only the past 500 MB

## 使用systemd分析引导过程
- systemd-analyze : 显示内核和用户空间上一次引导花了多长时间
- systemd-analyze blame : 显示每个服务启动用了多长时间方面的详细信息
- systemd-analyze critical-chain : 打印对时间要求严格的单元链的树结构
- systemd-analyze dot | dot -Tsvg > systemd.svg : 列出引导过程的矢量图（需要graphviz程序包）
- systemd-analyze plot > bootplot.svg : 生成引导过程的图形化时间图

## write .service
- 设置stop signal, KillSignal=SIGINT

##
systemctl list-units --type target: 查看目前可用的target
systemctl isolate name.target: 改变当前的target
systemctl get-default: 到默认的运行级别
systemctl set-default name.target: 修改默认的运行target
systemctl show -p "[Wants|WantedBy|Requires|RequiredBy|Conflicts|ConflictedBy|Before|After]" multi-user.target

##
#### [Unit]节选项
After: 定义在那些单元之后启动,本单元只在制定的单元启动之后启动，不像Requires选项，After选项不明确激活特定的单元，Before选项则是有相反的功能。
Requires: 配置单元的依赖性，在Requires选项中的单元需要一起被激活，如果有一个单元启动失败，其他单元都不会被启动。
Wants: 比Requires选项依赖性要弱很多，如果列表之中的的单元启动失败，不会对其他单元造成影响，这是推荐的建立自定义单元依赖性的方式。
Conflicts: 定义单元冲突关系，和Requires相反。

#### [unittype]类型是[Service]时的选项
Type: 配置单元进程在启动时候的类型，影响执行和关联选项的功能，可选的关键字是：
simple: 默认值，进程和服务的主进程一起启动；
forking: 进程作为服务主进程的一个子进程启动，父进程在完全启动之后退出。
oneshot: 同simple相似，但是进程在启动单元之后随之退出。
dbus: 同simple相似，但是随着单元启动后只有主进程得到D-BUS名字。
notify: 同simple相似，但是随着单元启动之后，一个主要信息被sd_notify()函数送出。
idle: 同simple相似，实际执行进程的二进制程序会被延缓直到所有的单元的任务完成，主要是避免服务状态和shell混合输出。
ExecStart: 指定启动单元的命令或者脚本，
ExecStartPre和ExecStartPost节: 指定在ExecStart之前或者之后用户自定义执行的脚本。
Type=oneshot允许指定多个希望顺序执行的用户自定义命令。
ExecStop指定单元停止时执行的命令或者脚本。
ExecReload指定单元重新加载是执行的命令或者脚本。
Restart这个选项如果被允许，服务重启的时候进程会退出，会通过systemctl命令执行清除并重启的操作。
RemainAfterExit如果设置这个选择为真，服务会被认为是在激活状态，即使所以的进程已经退出，默认的值为假，这个选项只有在Type=oneshot时需要被配置。

#### [Install]节选项
Alias: 为单元提供一个空间分离的附加名字。
RequiredBy: 单元被允许运行需要的一系列依赖单元，RequiredBy列表从Require获得依赖信息。
WantBy: 单元被允许运行需要的弱依赖性单元，Wantby从Want列表获得依赖信息。
Also: 指出和单元一起安装或者被协助的单元。
DefaultInstance: 实例单元的限制，这个选项指定如果单元被允许运行默认的实例。
