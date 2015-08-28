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
