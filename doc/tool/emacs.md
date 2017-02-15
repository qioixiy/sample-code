# 通用命令及其绑定
## basic
```
C-x C-f ;打开文件,出现提示时输入/username@host:filepath可编辑FTP文件
C-x C-v ;打开一个文件,取代当前缓冲区
C-x C-s ;保存文件
C-x C-w ;存为新文件
C-x i ;插入文件
C-x C-q ;切换为只读或者读写模式
C-x C-c ;退出Emacs
C-x k ;关闭缓存中某一个文件
C-x h ;选中所有内容
C-M \ ;auto indent 选中内容
C-u C-@ ;快速回到刚才光标所在的位置
M-k kill ;current point to buffer end
M - C-k ;删除从光标位置到行首方法1
C-u 0 Ctrl-k ;删除从光标位置到行首方法2
```
## edit
```
C-l ;重绘屏幕,当前行居中
C-f ;前进一个字符
C-b ;后退一个字符
C-t ;transpose-chars 这一命令调换光标左右的单个字符
M-t ;transpose-words 这一命令调换光标左右的单个单词
C-x C-t ;transpose-lines 这一命令调换光标所在的行与光标前面的行
M-f ;前进一个字
M-b ;后退一个字
M-{ ;向上移动一段
M-} ;向下移动一段
M-^ ;delete-indentation 这一命令将光标所在的行和前面的行连接起来,以C-1作为开始，以连接光标所在的行和下一 行
M-u ;uppercase-word 这一命令将光标处到其所在词的词尾之间的文本转换为大写字母
M-l ;downcase-word 这一命令将光标处其所在词的词尾之间的文本转换为小写字母
C-x C-l ;downcase-region 这一命令将区域中的内容转换为小写字母
C-x C-u ;upcase-region 这一命令将区域中的内容转换为大写字母
C-a ;移到行首
C-e ;移到行尾
M-a ;移到句首
M-e ;移到句尾
C-p ;后退一行
C-n ;前进一行
M-x ;goto-line 跳到指定行
C-v ;向下翻页
M-v ;向上翻页
M-< ;缓冲区头部
M-> ;缓冲区尾部
M-r ;将光标移动到屏幕中间那行
C-M-f ;向前匹配括号
C-M-b ;向后匹配括号
C-M-v ;scroll up other window
C-M-V ;scroll down other window
M-n or C-u n ;重复操作随后的命令n次
C-u ;重复操作随后的命令4次
C-u C-u ;重复操作随后的命令8次
C-x ESC ESC ;执行历史命令记录
M-p ;选择上一条命令
M-n ;选择下一条命令
C-d ;删除一个字符
M-d ;删除一个字
C-k ;删除一行
M-k ;删除一句
C-w ;删除标记区域
C-y ;粘贴删除的内容,先按C-y,然后按M-y可以选择粘贴被删除的内容
C-@ ;标记开始区域
C-x h ;标记所有文字
C-x C-x ;交换光标位置和区域标记区开头
C-x < ;窗口内容右卷
C-x > ;窗口内容左卷（这两个命令在垂直分割窗口后比较有用）
M-w ;复制标记区域
C-_ or C-x u ;undo撤消操作
flush-lines ^$ ;删除空行
C-space ;(redefined) 设置mark, C-@ 是默认命令
C-w ;(redefined) : 剪切一块区域；如果没有设置mark，则是剪切一行
M-w ;(redefined) : 拷贝一块区域；如果没有设置mark, 则是拷贝一行
C-o ;open-line 这一命令以垂直间距在光标下方打开一个新行，而不移动光标
C-u C-space ;移动到标记环中的前一个标记
C-x C-x ;exchange-point-and-mark 交换光标和标记的位置
M-@ ;mark-word 标记从光标到当前词尾的所有文本
M-h ;mark-paragraph 标记当前段落，不管光标处在什么位置
transient-mark-mode 切换临时标记模式
mark-whole-buffer 标记整个缓冲区，不管光标处在什么位置
M-B1 设置二次选择的开始，拖曳鼠标以进行二次选择
M-B3 设置二次选择的结尾
M-B1-B1 将一个单词标记为二次选择
M-B1-B1-B1 将一行标记为二次选择
C-k kill-line ;剪切行的整数 数目,如果是 0，剪切从光标到该行开头的全部内容；如果是负数，则反向剪切
M-k kill-sentence ;剪切从光标到句子的结尾处的内容
M-z zap-to-char ;删除从光标到指定的字符之间的所有文本
M-y yank-pop ;移动到剪切环中的下一个槽位
C-y ;yank 粘贴剪切环中指定槽位的内容
```
## shell
```
M-x shell ;open shell
M-! ;run shell command
M-1 M-! ;执行SHELL命令,命令输出插入光标位置,不打开新输出窗口
M-| ;针对某一特定区域执行命令(shell-command-on-region), 比如 C-x h M- | uuencode
;;;; shell mode
C-c C-c ;相当于Bash下的C-c
C-c C-z ;相当于Bash下的C-z
C-c C-d ;相当于Bash下的C-d
M-p ;执行前一条命令
C-n ;执行下一条命令
C-c C-o ;删除最后一条命令产生的输出
C-c C-r ;屏幕滚动到最后一条命令输出的开头
C-c C-e ;屏幕滚动到最后一套命令输出的结尾
C-c C-p ;查看前一条命令的输出
C-c C-n ;查看后一条命令的输出
C-u M-! <shell-command> ; 插入命令输出到当前buffer
(global-set-key (kbd "C-c C-d") (lambda () (interactive) (insert (shell-command-to-string "date"))))
```
## window
```
C-x 0 ;关闭本窗口
C-x 1 ;只留下一个窗口
C-x 2 ;垂直均分窗口
C-x 3 ;split-window-horizontally,水平均分窗口
C-x o ;other-window,切换到别的窗口
C-x b ;选择当前窗口的缓冲区
C-x ^ ;纵向扩大窗口
C-x } ;横向扩大窗口
C-x s ;保存所有窗口的缓冲, 会提示你是否需要保存
ESC C-v ;在其它窗口进行卷屏操作
C-x 2; split-window-vertically,从中间将当前窗口划分为两半，垂直地堆叠新的缓冲区。
C-x 4 b ;switch-to-buffer-other-window,垂直地将当前窗口划分为两半，提示输入缓冲区以使用底部的窗口，并将其作为活动窗口。
C-x 4 C-o ;display-buffer,在另一个窗口中显示一个缓冲区，提示输入缓冲区以使用另一个窗口，但保持当前窗口为活动窗口
      如果仅存在一个窗口，那么垂直地划分该窗口以显示另一个缓冲区
C-x 4 f ;find-file-other-window,在新的缓冲区中打开新的文件，在新的垂直窗口中绘制它。
C-x 4 r ;find-file-read-only-other-window,在一个新的只读缓冲区中打开新的文件，在新的垂直窗口中绘制它。
C-M-v ;scroll-other-window,滚动到下一个由 C-x o 切换到的窗口。
C-x 0 ;delete-window,删除当前窗口，并将光标移动到使用 C-x o 将切换到的下一个窗口。
C-x 1 ;delete-other-windows,删除当前窗口之外的所有窗口。
C-x 4 0 ;kill-buffer-and-window,删除当前窗口，并剪切它的缓冲区。
;;;; 调整窗口高度,宽度,适合高度,均分高度
C-x ^ | M+x shrink-window ;enlarge-window使当前窗口增加一行的高度；在其之前使用一个负数，将使得当前窗口减少一行的高度。
C-x } ;shrink-window-horizontally,使当前活动窗口减少一列的宽度。
C-x { ;enlarge-window-horizontally,使当前活动窗口增加一列的宽度。
C-x - ;shrink-window-if-larger-than-buffer,将当前活动窗口的大小缩小到对于它所包含的缓冲区来说可能的最小尺寸。
C-x + ;balance-windows,平衡所有窗口的尺寸，使它们的大小大致相等。
;;;; command
compare-windows,将当前窗口与下一个窗口进行比较，在两个窗口中从光标处开始比较，并在两个缓冲区中将光标移动到第一个不同的字符处，直到到达缓冲区的末尾为止。
windmove-up    移动到正好位于当前窗口上方的窗口
windmove-down  移动到正好位于当前窗口下方的窗口
windmove-left  移动到正好位于当前窗口左边的窗口
windmove-right 移动到正好位于当前窗口右边的窗口
;;;; follow-mode,切换 follow 次要模式。当它在缓冲区中处于打开状态时，将所有显示该缓冲区的窗口连接为一个较大的虚拟窗口。
;;;; scroll-all-mode, 切换 scroll-all 次要模式。当它处于打开状态时，将同时滚动显示当前窗口中的缓冲区的所有窗口，并滚动均等的相应距离。
```
## frame
```
C-x 5 2 ;make-frame-command              生成一个新的 Emacs 框架，并使其成为活动框架。
C-x 5 b ;switch-to-buffer-other-frame    在另一个框架中打开指定的缓冲区。如果不存在其他框架，则创建一个新的框架。
C-x 5 f ;find-file-other-frame           在另一个框架中打开指定的文件。如果不存在其他框架，则创建一个新的框架。
C-x 5 r ;find-file-read-only-other-frame 在另一个框架中的只读缓冲区中打开指定的文件。如果不存在其他框架，则创建一个新的框架。
C-x 5 o ;other-frame                     移动到下一个框架，并使其成为活动框架。
C-x 5 0 ;delete-frame                    删除当前框架，并使下一个框架成为活动框架。
C-x 5 1 ;delete-other-frames             删除当前框架之外的所有框架。
C-z ;iconify-or-deiconify-frame          图标化当前框架。如果该框架已经图标化了，那么取消它的图标化。（在控制台中，这个绑定将挂起 Emacs。）
```
### buffer list
```
C-x C-b ;打开缓冲区列表
d or k ;标记为删除
~ ;标记为未修改状态
% ;标记为只读
s ;保存缓冲
u ;取消标记
f ;在当前窗口打开该缓冲区
o ;在其他窗口打开该缓冲区
x ;执行标记的操作
```
### Directory mode
```
C-x d enter ;打开目录模式
s ;按日期/文件名排序显示
v ;阅读光标所在的文件
q ;退出阅读的文件
d ;标记为删除
x ;执行标记
D ;马上删除当前文件
C ;拷贝当前文件
R ;重名名当前文件
+ ;新建文件夹
Z ;压缩文件
! ;对光标所在的文件执行SHELL命令
g ;刷新显示
i ;在当前缓冲区的末尾插入子目录的内容
[n]m ;标记光标所在的文件,如果指定n,则从光标所在的文件起后n个文件被标记
[n]u ;取消当前光标标记的文件,n的含义同上
t ;反向标记文件
%-m ;正则标记
q ;退出目录模式
;; 在目录模式中,如果输入!,在命令行中包含*或者?,有特殊的含义.*匹配当前光标所在的文件和所有标记的文件, ?分别在每一个标记的文件上执行该命令.
```
### complie and debug
```
M-x compile ;执行编译操作
M-x gdb ;GDB排错
M-x dbx ;DBX排错
M-x xdb ;XDB排错
M-x sdb ;SDB排错
```
## search
```
C-s ;向前搜索（增量式搜索）；连续C-s，跳到下一个搜索到的目标
C-s RET ;普通搜索
C-r key ;反向搜索
C-s C-w ;以光标所在位置的字为关键字搜索
C-s C-s ;重复上次搜索
C-r C-r ;重复上次反向搜索
C-s ENTER C-w ;进入单词搜索模式
C-r ENTER C-w ;进入反向单词搜索模式
M-x replace-string ENTER search-string ENTER ;替换
M-% search-string ENTER replace-string ENTER ;交互替换
C-r ;在进入查找/替换模式后,该命令进入迭代编辑模式
C-M-x ;退出迭代编辑模式,返回到查找/替换模式
C-M-s ;向前正则搜索
C-M-r ;向后正则搜索
C-M-% ;正则交互替换
```
## format style
```
C-M-q ;格式化这一对括号中的代码,注意,光标一定要置于左括号上.
C-c C-q ;格式化一个函数.
C-M-a ;跳到函数的开始.
C-M-e ;跳到函数的结尾.
M-a ;跳到上一个语句.
M-e ;跳到下一个语句.
C-M-b ;当光标置于｝的后面时,跳转到与之匹配的｛.
C-M-f ;当光标置于｛的后面时,跳转到与之匹配的｝.
C-c C-u ;跳转到上一个条件编译的条件处.
c-down-conditional ;跳转到下一个条件编译的条件处,可根据自己情况绑定快捷键.
```
### 注释
```
C-c C-c ;标记你要注释的代码,注释代码块
M-x uncomment-region ;恢复注释前状态
M-; 注释选中内容
```
### 代码块收缩
```
M-x hs-minor-mode
C-c @ ESC C-s ;show all
C-c @ ESC C-h ;hide all
C-c @ C-s ;show block
C-c @ C-h ;hide block
C-c @ C-c ;toggle hide/show
C-c bh ;show block
C-c bs ;hide block
```
## rectangle
```
C-x space ;rectangle mode
C-space ;set-mark-command    标记矩形区块的一个角（光标标记其相对的角）
C-x r k ;kill-rectangle      剪切当前的矩形区块，并将其保存在一个特殊的矩形区块缓冲区中
C-x r d ;delete-rectangle    删除当前的矩形区块，并不为粘贴而保存它
C-x r c ;clear-rectangle     清除当前的矩形区块，使用空白字符替换整个区域
C-x r o ;open-rectangle      打开当前的矩形区块，使用空白字符填充整个区域，并将该矩形区块的所有文本移动到右边
C-x r y ;yank-rectangle      在光标处，粘贴上一次剪切的矩形区块的内容，将所有的现有文本移动到右边
```
## print
```
M-x print-buffer ;先使用pr,然后使用lpr
M-x lpr-buffer ;直接使用lpr
M-x print-region
M-x lpr-region
```
## mail
```
M-x mail ;发送邮件, C-c C-s 发送,C-c C-c 发送并退出
M-x rmail ;接受邮件
```
## Tags
```
M-! etags .c .h ;创建TAGS文件
M-. ;跳到tag所在位置
M-x list-tags ;列出tags
```
## Bookmark
```
C-x r m Bookmark ;bookmark-set,设置一个名为Bookmark的书签
C-x r l ;bookmarks-bmenu-list,列出所有已保存的书签
C-x r b Bookmark ;bookmark-jump,跳转至名为Bookmark的书签中所设置的位置
undefined bookmark-save 将所有的书签保存到书签文件~/.emac.bmk中
bookmark-delete 删除一个书签
```
## help
```
C-h ? ;查看帮助信息
C-h f ;查看一个函数
C-h v ;查看一个变量
C-h k ;查看一个键绑定
C－h c ;也是查看键绑定，但是信息较简略
C-h C-f ;查看一个函数的Info，非常有用
C-h i ;Info
```
## misc
```
C-x C-m c chinese-euc-dos RETURN ;指定编码方式为chinese-euc-dos
C-x C-l ;将一段选定的文字转换为小写文字
C-x C-u ;将一段选定的文字转换为大写文字
c-x i ;拷贝一个文件到一个buffer
c-x c-i ;拷贝一个buffer到另外一个buffer
C-q C-m ;\r字符的输入形式
C-q TAB ;tab键被用来做格式化功能了,真正键入一个tab
C-M-\ ;对选中区域，按照某种格式(比如C程序)进行格式化
C-x h ;全部选中
M-! ;执行外部shell命令
M-x shell ;模拟shell的buffer
M-x term ;模拟terminal,C-c k关闭terminal
C-x C-q ;修改buffer的只读属性
M-Backspace,M-Del;backward-kill-word从插入点开始向回删除字符，直至单词的开始处
C-q ;字符或XXX quoted-insert在插入点插入按键本身代表的字符或由八进制数字（XXX）表示的字符
C-u ;次数命令universal-argument按总的次数（缺省为4次）连续执行命令
```
## Ispell check
```
M-$ ;拼写检查单词
;; ispell-word   调用Ispell以检查光标处单词的拼写
;; ispell-region 调用Ispell以检查某一区域中的拼写
;; ispell-buffer 调用Ispell以检查从光标处到缓冲区末尾的所有单词的拼写
;;;; flyspell mode, 在输入内容的同时，调用Ispell在后台检查缓冲区中所有单词的拼写，突出显示所有的拼写错误
flyspell-auto-correct-word, M-Tab 根据Ispell给出的修改建议，自动地纠正最近一个拼写错误的单词
M-x flyspell-auto-correct-previous-word 根据Ispell给出的修改建议，自动地纠正前面拼写错误的单词
M-x flyspell-correct-word, B2显示单词建议的弹出菜单
;;;; ispell mode, Ispell 单词替换子命令
;; char 使用以（字符）开头的替换建议。
;; space 在此上下文中接受这个单词作为更正。
;; i 接受这个单词作为更正并将其插入到个人字典文件。
;; a 仅对于此次 Emacs 会话接受这个单词作为更正。
;; A 仅对于此次 Emacs 会话中的缓冲区，接受这个单词作为更正。
;; r 使用您输入的字符串替换这个单词（Ispell 会再次进行拼写检查）。
;; R 使用您输入的字符串替换这个单词（Ispell 会再次进行拼写检查），并对整个缓冲区的剩余部分运行query-replace。
;; l 使用给定的字符串替换这个单词，并在给定的字典文件中查找这个新的字符串。
;; u 将这个单词的小写形式插入到个人字典文件。
;; m 使用给定的字符串替代这个单词，将其保存到个人字典，然后再次对该单词进行拼写检查。
;; x 退出拼写检查，并将光标移回到它的原始位置。
;; X 退出拼写检查，并使光标位于它当前所在的位置。
;; q 立刻结束拼写检查。
;; ? 显示选项菜单。
```
## 按键前缀描述
```
C-c ;当前编辑模式特有的命令
C-x ;文件和缓冲区命令
C-h ;帮助命令
M-x ;函数名称
C-x r space X point-to-register 将光标保存到寄存器X
C-x r r X copy-rectangle-to-register 将选定的矩形区块保存到寄存器X
C-x r s X copy-to-register 将区域保存到寄存器X
C-x r j X jump-to-register 将光标移动到寄存器X中给定的位置
C-x r i X insert-register  在光标处插入寄存器X的内容
未定义 view-register       查看一个给定的寄存器的内容
```
## global variable
```
auto-mode-alist                如果设置为nil，那么将关闭根据文件名扩展自动选择主要模式的功能。它的缺省值是一些文件名扩展和相应模式的列表
auto-save-default              如果没有将其设置为nil，那么 Emacs 则根据预设的时间间隔，自动地将经过更改的缓冲区保存到相应的文件它的缺省值是 t
auto-save-interval             包含调用 Auto-save 模式（如果它被设置为“真”）之后经过更改的字符的数目，其缺省值是 300
calendar-latitude              包含用户工作站位置的纬度值，采用度数表示；其缺省值是nil
calendar-longitude             包含用户工作站位置的经度值，采用度数表示；其缺省值是nil
calendar-location-name         包含用户工作站所在位置的位置名（如城市、州或省、国家/地区）的值，其缺省值是nil
colon-double-space             如果没有将其设置为nil，那么填充文本的命令将在冒号后面插入两个 空格而不是一个其缺省值是nil
command-line-args              包含在当前emacs会话中所执行的命令行中使用的参数列表
command-line-default-directory 包含执行当前Emacs会话的目录的路径名
compare-ignore-case            如果没有将其设置为nil，那么在运行 compare-windows 函数的时候，Emacs将忽略大写字母和小写字母的区别
confirm-kill-emacs             如果设置为nil，那么Emacs 在退出的时候不请求确认；否则，可能自定义Emacs Lisp函数以完成退出验证工作，如 y-or-n-p,其缺省值是nil
default-justification          设置缺省的对齐风格该值可能是 left、right、center、full 或者 none 中的一个其缺省值是 left
default-major-mode             为新的文件或者缓冲区选择缺省主要模式其缺省值是 fundamental-mode
display-time-24hr-format       如果设置为 t，那么 Emacs 将采用 24 小时军用格式来显示时间，而不是采用带有 AM 或者 PM 后缀的标准 12 小时格式其缺省值是nil
display-time-day-and-date      如果没有将其设置为nil，那么 Emacs 以当前星期几、当前月份和日期的格式来显示时间，而不仅仅显示小时和分钟其缺省值是nil
fill-column                    包含各行中的列数（从此处开始填充文本到下一行）其缺省值是 70
initial-major-mode             指定启动时用于 *scratch* 缓冲区的主要模式其缺省值是 lisp-interaction-mode
inverse-video                  如果没有将其设置为nil，那么 Emacs 将对显示的颜色取反（如果可能的话）其缺省值是nil
kill-ring                      包含 Emacs 剪切环的内容
kill-ring-max                  设置剪切环中所允许的条目数其缺省值是60
kill-whole-line                如果没有将其设置为nil，那么kill-line函数（绑定于C-k）将剪切当前行以及其尾部的换行符,其缺省值是nil
make-backup-files              如果没有将其设置为nil，Emacs 将进行任何更改之前保存缓冲区的备份（使用相同的文件名，但在文件名后追加了波浪符 (~)）
mark-ring                      包含该缓冲区的当前标记环的内容，如本系列文章的第 3 部分教程中所描述的
mark-ring-max                  包含标记环中所允许的条目数其缺省值是 16
mouse-avoidance-mode           包含描述 mouse-avoidance 模式类型的值，如本系列文章第 5 部分教程中所描述的其缺省值是nil
next-line-add-newline          如果没有将其设置为nil，那么只要按下向下箭头键，Emacs 就会在该缓冲区的末尾添加一个新行其缺省值是nil
scroll-bar-mode                包含 Emacs 框架侧边缘（放置滚动条的位置）的值：right 或 left如果设置为nil，则关闭滚动条其缺省值是 left
scroll-step                    包含使用scroll-down和scroll-up函数（在缺省情况下，绑定于PgDn和PgUp键）在缓冲区中移动的行数,如果设置为0，滚动的时候,光标位于窗口的中心
show-trailing-whitespace       如果没有将其设置为nil，那么 Emacs 将显示当前缓冲区中的行尾处的任何空白字符其缺省值是nil
visible-bell                   如果没有将其设置为nil，那么 Emacs 将使得该框架闪烁，而不是鸣响系统警铃其缺省值是nil
x-cut-buffer-max               设置剪切环的字符的最大数目，该剪切环同样存储于 X Window System的剪切缓冲区中其缺省值是20000
;;;; mode
column-number-mode             在模式行中，为光标所在的当前列（前面有一个 C）切换显示。其缺省值是 nil
display-time                   在模式行中切换当前时间的显示。其缺省值是 nil
font-lock-mode                 如果没有将其设置为 nil，那么 Emacs 将为当前缓冲区自动地打开 Font Lock 模式。其缺省值是 nil
global-font-lock-mode          如果没有将其设置为 nil，那么 Emacs 将为所有的 缓冲区自动地打开 Font Lock 模式。其缺省值是 nil
line-number-mode               在模式行中，为光标所在的当前行（前面有一个 L）切换显示，其缺省值是 t
menu-bar-mode                  切换 Emacs 菜单条的显示。其缺省值是 t
sunrise-sunset                 根据当前地理位置，显示今天日出和日落的时间。如果在它的前面加上 universal-argument，那么这个函数将提示输入一个特定的日期
tool-bar-mode                  切换 Emacs 工具条的显示。其缺省值是 t
```
## command
```
revert-buffer ; load file form disk
window ; other-window,windmove-down,windmove-up,windmove-left,windmove-right
buffer ; buffer-menu,next-buffer,previous-buffer
find-file ; default bind[C-x C-f],
beginning-of-buffer ; the start of buffer, M-< or C-home
end-of-buffer ; the end of buffer, M-> or C-end
beginning-of-line ; line start, C-a
end-of-line ; line end, C-e
next-line ; move point next line, C-n
previous-line ; up line, C-p
forward-char ; forward a char, C-f
forward-line ; forward a line, M-f
backward-char ; backward a char, C-b
backward-line ; backward a line, M-b
search-forward ; search forward a match string, C-s
search-backward ; C-r
untabify ; replace tab use space
hs-hide-block ;  隐藏光标所在代码块,C-c @ C-h
hs-show-block ;显示光标所在代码块
hs-hide-all ; 隐藏所有代码块 C-c @ C-M-h
hs-show-all ; 显示所有代码块 C-c @ C-M-s
hide-ifdefs ; 隐藏所有ifdef块
hide-ifdef-block ; 隐藏光标所在的ifdef块 C-c @ C-d
show-ifdefs ; 显示所有ifdef块 C-c @ s
show-ifdef-block ; 显示光标所在的ifdef块 C-c @ C-d
```
## emacs 包管理器，hosted at GNU ELPA
```
M-x list-packages
```
## emacs 中使用w3m浏览网页
```
- sudo apt-get install w3m w3m-el w3m-img
```
## custom setting
```
;; binding
(tool-bar-mode nil) ; 关掉 toolbar
(setq display-time-day-and-date t) ; 显示日期
(display-time)
(setq c-basic-offset 8) ; 缩进设定
(global-font-lock-mode t) ; 语法高亮显示
(setq make-backup-files nil) ; 不产生备份文件
(global-set-key "\C-h" 'backward-delete-char-untabify)
(global-set-key [DEL] 'delete-char)
(defun my-c-comment ()
       (interactive)
       (insert "/* */"
       (backward-char 3))
(global-unset-key "\M-;")
(global-set-key "\M-;" 'my-c-comment)
;; emacs最大化启动
(setq
 initial-frame-alist
 '((top . 0) (left . 0) (width . 97) (height . 49)))
```
### S-F9 调用 compile 并设置编译命令
### F9 则保存所有文件并编译(无提示)
```
(defun onekey-compile ()
  "Save buffers and start compile"
  (interactive)
  (save-some-buffers t)
  (switch-to-buffer-other-window
   "*compilation*"
   (compile compile-command)
   (other-window 1)))
(global-set-key [S-f9]
                '(lambda ()
                   (interactive)
                   (switch-to-buffer-other-window
                    "*compilation*"
                    (compile)
                    (other-window 1))))
(global-set-key [f9] 'onekey-compile)
```
### cedet
```
cedet is a toolkit
EDE - 项目管理
Semantic - 自动补全和代码间跳转
SRecode - 模板,通过定义一些模板,可以快速的插入一段代码
Cogre - C++类生成UML 图
Speedbar - 显示目录树,函数列表等
```
## cedet提供了几个不同的功能组合,
```
semantic-load-enable-minimun-features
semantic-load-enable-code-helpers
semantic-load-enable-guady-code-helpers
semantic-load-enable-excessive-code-helpers
semantic-load-enable-semantic-debugging-helpers
一般使用semantic-load-enable-code-helpers.
(require 'cedet)
(semantic-load-enable-code-helpers)
```
## semantic在补全时找到函数和结构体,添加一些头文件的位置
```
(require 'semantic-ia)
(require 'semantic-gcc)
(setq-mode-local c-mode semanticdb-find-default-throttle
                 '(project unloaded system recursive))
(require 'semanticdb)
(defconst cedet-user-include-dirs
  (list "./include" "/usr/include"))
(setq cedet-sys-include-dirs
      (list "/usr/include"))
(let (include-dirs cedet-user-include-dirs)
  (setq include-dirs (append include-dirs cedet-sys-include-dirs))
  (mapc (lambda (dir)
          (semantic-add-system-include dir 'c++-mode)
          (semantic-add-system-include dir 'c-mode))
        include-dirs))
```
## 代码补全命令
```
semantic提供了下面几个补全命令
senator-complete-symbol
senator-completion-menu-popup
semantic-ia-complete-symbol
semantic-ia-complete-symbol-menu
semantic-complete-self-insert
(defun my-cedet-hook ()
  (local-set-key [(control return)] 'semantic-ia-complete-symbol-menu))
(add-hook 'c-mode-common-hook 'my-cedet-hook)
(defun my-c-mode-cedet-hook ()
  (local-set-key "." 'semantic-complete-self-insert)
  (local-set-key ">" 'semantic-complete-self-insert))
(add-hook 'c-mode-common-hook 'my-c-mode-cedet-hook)
前提是配置好include路径.代码跳转semantic-ia-fast-jump,跳回来semantic-mrub-switch-tags,
用semantic-mrub-switch-tags跳回时,它默认的不是原来的位置
semantic-complete-jump-local 跳转到当前文件
semantic-complete-jump 可以在其它的文件中搜索匹配的定义
semantic-analyze-proto-impl-toggle可以在函数的声明和实现之间跳转查找引用
semantic-symref可以查看某个函数在什么地方被调用,它会打开一个buffer,然后列出相关调用的地方,将光标移动到某个函数上,回车就能跳到相应位置
M-x semantic-symref-rename-local-variable把光标放在变量上,这时那个变量会出现下划线,删掉原来的变量,重新输入.这样所有这个函数里的变量都会改变.
```
## 代码折叠
```
用hs-minor-mode可以实现代码折叠,cedet也提供了这样的功能,一个是semantic提供的，另一个是senator提供的,第一个比较适合习惯鼠标操作的人
(require 'semantic-tag-folding nil 'noerror )
(global-semantic-tag-folding-mode 1 )
senator-fold-tag  折叠代码
senator-fold-tag-toggle  展开代码
```
## cscope
```
find -type f | grep -E '\.[chS]$' > cscope.files'
cscope -b -k
```
## urls
- [cedet1](http://emacser.com/cedet.htm)
- [cedet2](http://cedet.sourceforge.net/)
- [cedet3](http://alexott.net/en/writings/emacs-devenv/EmacsCedet.html)
- [emacswiki](http://www.emacswiki.org/)
- [emacs 总结](http://planet.emacsen.org/)
- [Org-mode简明手册](http://www.cnblogs.com/Open_Source/archive/2011/07/17/2108747.html)
- [orgmode.org/](http://orgmode.org/)
