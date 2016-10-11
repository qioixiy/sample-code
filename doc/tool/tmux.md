# tmux
# 基本终终端操作
tmux # 启动
tmux new -s "session_name"       # 创建一个seesion
tmux new -s "session_name" -d    # 创建一个seesion, 并在后台运行
tmux attach
tmux attach -t session           # 进入指定的会话（可终端共享）
tmux kill-session -t "session"   # 删除指定会话
tmux kill-server                 # 关闭
tmux ls                          # 列出tmux会话列表

# 控制台操作
# Ctrl+b  # 激活控制台
# 系统操作
? 列出所有快捷键；按q返回
d 脱离当前会话；可以暂时返回Shell界面，输入tmux attach能够重新进入之前的会话
D 选择要脱离的会话；在同时开启了多个会话时使用
Ctrl+z 挂起当前会话
r 强制重绘未脱离的会话
s 选择并切换会话；在同时开启了多个会话时使用
: 进入命令行模式；此时可以输入支持的命令，例如kill-server可以关闭服务器
: new-session # 创建新会话
[ 进入复制模式；此时的操作与vi/emacs相同，按q/Esc退出
~ 列出提示信息缓存；其中包含了之前tmux返回的各种提示信息
# 会话操作
( # preview session
) # next session
L # last session
s # list session
$ # rename seesion
# 窗口操作
c # 创建新窗口
& # 关闭当前窗口
[0-9] # 切换至指定窗口
p # 切换至上一窗口
n # 切换至下一窗口
l # 在前后两个窗口间互相切换
w # 通过窗口列表切换窗口
, # 重命名当前窗口；这样便于识别
. # 修改当前窗口编号；相当于窗口重新排序
f # 在所有窗口中查找指定文本
i # 显示tmux当前信息
" 将当前面板平分为上下两块
% 将当前面板平分为左右两块
x 关闭当前面板
! 将当前面板置于新窗口；即新建一个窗口，其中仅包含当前面板
# 面板操作
" # 将当前面板平分为上下两块|横向切割
% # 将当前面板平分为左右两块|竖向切割
x # 关闭当前面板
; # 切换到最后的pane
! # 将当前面板置于新窗口；即新建一个窗口，其中仅包含当前面板
Ctrl+方向键  # 以1个单元格为单位移动边缘以调整当前面板大小
Alt+方向键   # 以5个单元格为单位移动边缘以调整当前面板大小
Space        # 在预置的面板布局中循环切换;依次包括:
    even-horizontal even-vertical main-horizontal main-vertical tiled
q # 显示面板编号
o # 在当前窗口中选择下一面板
{ # 向前置换当前面板
} # 向后置换当前面板
方向键 # 移动光标以选择面板
Alt+o  # 逆时针旋转当前窗口的面板
Ctrl+o # 顺时针旋转当前窗口的面板

# 参考配置
set -g history-limit 50000
set -g default-terminal "screen-256color" #设置终端颜色为256色
set -g status-utf8 on #开启status-bar uft-8支持
set -g status-fg white #设置status-bar颜色
set -g status-bg black
set -g status-left-length 40 #设置status bar格式
set -g status-left "#[fg=green]Session: #S #[fg=yellow]#I #[fg=cyan]#P"
set -g status-right "#[fg=cyan]%d %b %R"
set -g status-interval 60
set -g status-justify centre
set -g pane-border-fg green #设置pan前景色
set -g pane-border-bg black #设置pane背景色
set -g pane-active-border-fg white #设置活跃pane前景色
set -g pane-active-border-bg yellow #设置活跃pane背景色
set -g message-fg white #设置消息前景色
set -g message-bg black #设置消息背景色
set -g message-attr bright #设置消息高亮显示
set -g visual-activity on
set -g status-utf8 on # 开启status-bar uft-8支持
set -g base-index 1 # 设定窗口起始
set -g renumber-windows on # 设置窗口可自动调整index
set -g mouse-resize-pane off
set -g mouse-select-pane off
set -g mouse-select-window off
set -g mouse-select-pane on # 鼠标可以选中窗格
set -g history-limit 4096 # history limit
set -g default-shell /bin/sh #设置Shell
set -g history-limit 4096 # history limit
set -g allow-rename off # 设置窗口名字不能修改
setw -g mode-mouse on # 鼠标滚轮可以用
setw -g mode-keys [vi,emacs] # 设置复制模式，空格开始选，Enter结束复制
setw -g window-status-fg cyan #设置窗口列表颜色
setw -g window-status-bg default
setw -g window-status-attr dim
setw -g window-status-current-fg white #设置当前窗口在status bar中的颜色
setw -g window-status-current-bg red
setw -g window-status-current-attr bright
setw -g monitor-activity on #开启window事件提示
# bind
bind-key k select-pane -U # up
bind-key j select-pane -D # down
bind-key h select-pane -L # left
bind-key l select-pane -R # right
bind-key C-l select-window -l # select last window
bind r source-file ~/.tmux.conf \; display "reload conf file!"
#
Ctrl+b " # split pane horizontally
Ctrl+b % # 将当前窗格垂直划分
Ctrl+b 方向键 # - 在各窗格间切换
Ctrl+b 并且不要松开Ctrl，方向键 - 调整窗格大小
Ctrl+b c # (c)reate # 生成一个新的窗口
Ctrl+b n # (n)ext # 移动到下一个窗口
Ctrl+b p # (p)revious # 移动到前一个窗口.
Ctrl+b space # 采用下一个内置布局
Ctrl+b q # 显示分隔窗口的编号
Ctrl+b o # 跳到下一个分隔窗口
Ctrl+b & # 确认后退出 tmux
# layout-1
splitw -h -p 50  #将其分成左右两个
selectp -t 1     #选中第一个，也就是右边那个
splitw -v -p 50  #将其分成上下两个
selectp -t 0     #选回第一个
## .tmux.conf 后面加上一句 bind D source-file ~/.tmux/layout1
## 进入tmux后，键入 Ctrl + b D，即会自动执行layout1脚本
# reload source-file`tmux source-file ~/.tmux.conf`
# 复制和粘贴模式
Mouse cope/paste
shift+鼠标左键选择复制的文件,Ctrl+Shift+C复制，Ctrl+Shift+V/Shift+
鼠标[中,右]建粘贴
bind y copy-mode
bind c-y copy-mode
bind p paste-buffer
bind c-p paste-buffer
# toggle mouse mode to allow mouse copy/paste, set mouse on with prefix m
bind m \
set -g mode-mouse on \;\
set -g mouse-resize-pane on \;\
set -g mouse-select-pane on \;\
set -g mouse-select-window on \;\
display 'Mouse: ON'
# set mouse off with prefix M
bind M \
set -g mode-mouse off \;\
set -g mouse-resize-pane off \;\
set -g mouse-select-pane off \;\
set -g mouse-select-window off \;\
display 'Mouse: OFF'
# bind commands to sequences of keys
bind-key -Ttable2 c list-keys
bind-key -Ttable1 b switch-client -Ttable2
bind-key -Troot   a switch-client -Ttable1

# helper
* http://blog.csdn.net/ZCF1002797280/article/details/51859524
```
% mkdir ~/.tmux && cd ~/.tmux
% git clone https://github.com/tmux-plugins/tmux-resurrect.git
% git clone https://github.com/tmux-plugins/tmux-continuum.git
% git clone https://github.com/tmux-plugins/tmux-pain-control
% git clone https://github.com/tmux-plugins/tmux-logging
% echo run-shell ~/.tmux/tmux-resurrect/resurrect.tmux >> ~/.tmux.conf
% echo run-shell ~/.tmux/tmux-continuum/continuum.tmux >> ~/.tmux.conf
% echo set -g @continuum-save-interval '60' >> ~/.tmux.conf
```

# 实例1
# tmux conf
# set was a set-option alias
# setw was a set-window-option alias

new -s work # 新建名为work的会话
set -g history-limit 50000

#unbind C-b
setw -g prefix C-b
setw -g mouse on
setw -g mouse-utf8 on
setw -g mode-keys emacs # vi
setw -g automatic-rename on

# 窗口操作
unbind '"'
bind - splitw -v # 分割成上下两个窗口
unbind %
bind | splitw -h # 分割成左右两个窗口
setw -g window-status-format '#[dim]#I:#[default]#W#[fg=grey,dim]'
setw -g window-status-current-format '#[fg=cyan,bold]#I#[fg=blue]:#[fg=cyan]#W#[fg=dim]'

# 状态栏
set -g status-justify centre # 对齐方式
set -g status-bg black # 状态栏背景和前景色
set -g status-fg white #yellow
set -g status-left '#[bg=black,fg=green][#[fg=cyan]#S#[fg=green]]'
set -g status-left-length 20
set -g status-right "#[fg=green][#[fg=cyan]%Y-%m-%d#[fg=green]]#[fg=green]#[default]•#[fg=green]#(cut -d ' ' -f 1-3 /proc/loadavg)#[default]"

# 默认启动应用
#neww vim # 启动 vim
selectw -t 0 # 默认选择标号为0的窗口

# bind
bind R source-file ~/.tmux.conf \; display-message "~/.tmux.conf reloaded"
## 执行命令
bind m command-prompt "splitw -h 'exec %%'"
bind M command-prompt "splitw -h 'exec man %%'"
## panel操作
bind k selectp -U # 选择上窗格 # 选择分割的窗格
bind j selectp -D # 选择下窗格
bind h selectp -L # 选择左窗格
bind l selectp -R # 选择右窗格
bind ^u swapp -U # 与上窗格交换 Ctrl-u
bind ^d swapp -D # 与下窗格交换 Ctrl-d
bind-key J resize-pane -D 10 # 重新调整窗格的大小
bind-key K resize-pane -U 10
bind-key H resize-pane -L 10
bind-key L resize-pane -R 10
## Toggle log to file
bind H pipe-pane -o 'cat >>$HOME/#W-tmux.log' '\;' \
    display-message 'Toggled logging to $HOME/#W-tmux.log'
bind h pipe-pane \; display-message 'Ended logging to $HOME/#W-tmux.log'

# layout
bind L source-file ~/.tmux/layout1
