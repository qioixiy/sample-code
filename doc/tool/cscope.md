### cscope安装
1. 首先到Cscope的主页上去下载最新的源代码包，编译安装。要在Emacs里面使用
首先必须把xcscope.el拷贝到load-path里面包含的目录里面。并在 ~/.emacs
里面加上(require 'xcscope)就可以了; 或者如果你希望在打开c或者c++文件的时候
才加载xcsope，可以写：
```
(add-hook 'c-mode-common-hook
'(lambda ()
(require 'xcscope)))
```
如果源代码全部处于同一个目录下面，现在就可以使用了。否则，如果源代码有多层
目录,或者其他地方还有附加的源代码，则需要 cscope-indexer 脚本。把 那个脚本
拷贝到系统PATH里面去。如果所有的源代码以及子目录都是在同一个目录下面的，
只要执行C-c s I(cscope-index-files)就可以生成Cscope的数据库,接下来就可以使用了。


### 使用简介
默认是的快捷键都是绑定到C-c s的前缀上面,如果嫌麻烦的话可以自己更改快捷键绑定。
1. 这是默认的用于查找的键绑定：
C-c s s         Find symbol.
C-c s d         Find global definition.
C-c s g         Find global definition (alternate binding).
C-c s G         Find global definition without prompting.
C-c s c         Find functions calling a function.
C-c s C         Find called functions (list functions called from a function).
C-c s t         Find text string.
C-c s e         Find egrep pattern.
C-c s f         Find a file.
C-c s i         Find files #including a file.
***
2. 下面是在搜索到的结果之间切换用的快捷键：
C-c s b         Display *cscope* buffer.
C-c s B         Auto display *cscope* buffer toggle.
C-c s n         Next symbol.
C-c s N         Next file.
C-c s p         Previous symbol.
C-c s P         Previous file.
C-c s u         Pop mark.
*更详细的使用说明请参见xcscope.el文件头部的注释*

***
### 实例
```
#!/bin/sh

find -type f | grep -E '\.[chS]$' | tee cscope.files

#-k 专门用于生成 linux kernel 源码的索引
cscope -b -k
```
