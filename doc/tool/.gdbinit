# filename: .gdbinit
# gdb will read it when starting

#                                                                                                        
#   STL GDB evaluators/views/utilities - 1.03
#
#   The new GDB commands:                                                         
#         are entirely non instrumental                                             
#         do not depend on any "inline"(s) - e.g. size(), [], etc
#       are extremely tolerant to debugger settings
#                                                                                 
#   This file should be "included" in .gdbinit as following:
#   source stl-views.gdb or just paste it into your .gdbinit file
#
#   The following STL containers are currently supported:
#
#       std::vector -- via pvector command
#       std::list -- via plist or plist_member command
#       std::map -- via pmap or pmap_member command
#       std::multimap -- via pmap or pmap_member command
#       std::set -- via pset command
#       std::multiset -- via pset command
#       std::deque -- via pdequeue command
#       std::stack -- via pstack command
#       std::queue -- via pqueue command
#       std::priority_queue -- via ppqueue command
#       std::bitset -- via pbitset command
#       std::string -- via pstring command
#       std::widestring -- via pwstring command
#       void * array[]  -- via parray command   this command for print content infomantion of point array
#
#   The end of this file contains (optional) C++ beautifiers
#   Make sure your debugger supports $argc
#
#   Simple GDB Macros writen by Dan Marinescu (H-PhD) - License GPL
#   Inspired by intial work of Tom Malnar,
#     Tony Novac (PhD) / Cornell / Stanford,
#     Gilad Mishne (PhD) and Many Many Others.
#   Contact: dan_c_marinescu@yahoo.com (Subject: STL)
#
#   Modified to work with g++ 4.3 by Anders Elton
#   Also added _member functions, that instead of printing the entire class in map, prints a member.



#
# std::vector<>
#

define pvector
    if $argc == 0
        help pvector
    else
        set $size = $arg0._M_impl._M_finish - $arg0._M_impl._M_start
        set $capacity = $arg0._M_impl._M_end_of_storage - $arg0._M_impl._M_start
        set $size_max = $size - 1
    end
    if $argc == 1
        set $i = 0
        while $i < $size
            printf "elem[%u]: ", $i
            p *($arg0._M_impl._M_start + $i)
            set $i++
        end
    end
    if $argc == 2
        set $idx = $arg1
        if $idx < 0 || $idx > $size_max
            printf "idx1, idx2 are not in acceptable range: [0..%u].\n", $size_max
        else
            printf "elem[%u]: ", $idx
            p *($arg0._M_impl._M_start + $idx)
        end
    end
    if $argc == 3
      set $start_idx = $arg1
      set $stop_idx = $arg2
      if $start_idx > $stop_idx
        set $tmp_idx = $start_idx
        set $start_idx = $stop_idx
        set $stop_idx = $tmp_idx
      end
      if $start_idx < 0 || $stop_idx < 0 || $start_idx > $size_max || $stop_idx > $size_max
        printf "idx1, idx2 are not in acceptable range: [0..%u].\n", $size_max
      else
        set $i = $start_idx
        while $i <= $stop_idx
            printf "elem[%u]: ", $i
            p *($arg0._M_impl._M_start + $i)
            set $i++
        end
      end
    end
    if $argc > 0
        printf "Vector size = %u\n", $size
        printf "Vector capacity = %u\n", $capacity
        printf "Element "
        whatis $arg0._M_impl._M_start
    end
end

document pvector
    Prints std::vector information.
    Syntax: pvector
    Note: idx, idx1 and idx2 must be in acceptable range [0...size()-1].
    Examples:
    pvector v - Prints vector content, size, capacity and T typedef
    pvector v 0 - Prints element[idx] from vector
    pvector v 1 2 - Prints elements in range [idx1..idx2] from vector
end

#
# std::list<>
#

define plist
    if $argc == 0
        help plist
    else
        set $head = &$arg0._M_impl._M_node
        set $current = $arg0._M_impl._M_node._M_next
        set $size = 0
        while $current != $head
            if $argc == 2
                printf "elem[%u]: ", $size
                p *($arg1*)($current + 1)
            end
            if $argc == 3
                if $size == $arg2
                    printf "elem[%u]: ", $size
                    p *($arg1*)($current + 1)
                end
            end
            set $current = $current._M_next
            set $size++
        end
        printf "List size = %u \n", $size
        if $argc == 1
            printf "List "
            whatis $arg0
            printf "Use plist to see the elements in the list.\n"
        end
    end
end

document plist
    Prints std::list information.
    Syntax: plist : Prints list size, if T defined all elements or just element at idx
    Examples:
    plist l - prints list size and definition
    plist l int - prints all elements and list size
    plist l int 2 - prints the third element in the list (if exists) and list size
end

define plist_member
    if $argc == 0
        help plist_member
    else
        set $head = &$arg0._M_impl._M_node
        set $current = $arg0._M_impl._M_node._M_next
        set $size = 0
        while $current != $head
            if $argc == 3
                printf "elem[%u]: ", $size
                p (*($arg1*)($current + 1)).$arg2
            end
            if $argc == 4
                if $size == $arg3
                    printf "elem[%u]: ", $size
                    p (*($arg1*)($current + 1)).$arg2
                end
            end
            set $current = $current._M_next
            set $size++
        end
        printf "List size = %u \n", $size
        if $argc == 1
            printf "List "
            whatis $arg0
            printf "Use plist_member to see the elements in the list.\n"
        end
    end
end

document plist_member
    Prints std::list information.
    Syntax: plist : Prints list size, if T defined all elements or just element at idx
    Examples:
    plist_member l int member - prints all elements and list size
    plist_member l int member 2 - prints the third element in the list (if exists) and list size
end


#
# std::map and std::multimap
#

define pmap
    if $argc == 0
        help pmap
    else
        set $tree = $arg0
        set $i = 0
        set $node = $tree._M_t._M_impl._M_header._M_left
        set $end = $tree._M_t._M_impl._M_header
        set $tree_size = $tree._M_t._M_impl._M_node_count
        if $argc == 1
            printf "Map "
            whatis $tree
            printf "Use pmap to see the elements in the map.\n"
        end
        if $argc == 3
            while $i < $tree_size
                set $value = (void *)($node + 1)
                printf "elem[%u].left: ", $i
                p *($arg1*)$value
                set $value = $value + sizeof($arg1)
                printf "elem[%u].right: ", $i
                p *($arg2*)$value
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
        end
        if $argc == 4
            set $idx = $arg3
            set $ElementsFound = 0
            while $i < $tree_size
                set $value = (void *)($node + 1)
                if *($arg1*)$value == $idx
                    printf "elem[%u].left: ", $i
                    p *($arg1*)$value
                    set $value = $value + sizeof($arg1)
                    printf "elem[%u].right: ", $i
                    p *($arg2*)$value
                    set $ElementsFound++
                end
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
            printf "Number of elements found = %u\n", $ElementsFound
        end
        if $argc == 5
            set $idx1 = $arg3
            set $idx2 = $arg4
            set $ElementsFound = 0
            while $i < $tree_size
                set $value = (void *)($node + 1)
                set $valueLeft = *($arg1*)$value
                set $valueRight = *($arg2*)($value + sizeof($arg1))
                if $valueLeft == $idx1 && $valueRight == $idx2
                    printf "elem[%u].left: ", $i
                    p $valueLeft
                    printf "elem[%u].right: ", $i
                    p $valueRight
                    set $ElementsFound++
                end
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
            printf "Number of elements found = %u\n", $ElementsFound
        end
        printf "Map size = %u\n", $tree_size
    end
end

document pmap
    Prints std::map or std::multimap information. Works for std::multimap as well.
    Syntax: pmap : Prints map size, if T defined all elements or just element(s) with val(s)
    Examples:
    pmap m - prints map size and definition
    pmap m int int - prints all elements and map size
    pmap m int int 20 - prints the element(s) with left-value = 20 (if any) and map size
    pmap m int int 20 200 - prints the element(s) with left-value = 20 and right-value = 200 (if any) and map size
end


define pmap_member
    if $argc == 0
        help pmap_member
    else
        set $tree = $arg0
        set $i = 0
        set $node = $tree._M_t._M_impl._M_header._M_left
        set $end = $tree._M_t._M_impl._M_header
        set $tree_size = $tree._M_t._M_impl._M_node_count
        if $argc == 1
            printf "Map "
            whatis $tree
            printf "Use pmap to see the elements in the map.\n"
        end
        if $argc == 5
            while $i < $tree_size
                set $value = (void *)($node + 1)
                printf "elem[%u].left: ", $i
                p (*($arg1*)$value).$arg2
                set $value = $value + sizeof($arg1)
                printf "elem[%u].right: ", $i
                p (*($arg3*)$value).$arg4
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
        end
        if $argc == 6
            set $idx = $arg5
            set $ElementsFound = 0
            while $i < $tree_size
                set $value = (void *)($node + 1)
                if *($arg1*)$value == $idx
                    printf "elem[%u].left: ", $i
                    p (*($arg1*)$value).$arg2
                    set $value = $value + sizeof($arg1)
                    printf "elem[%u].right: ", $i
                    p (*($arg3*)$value).$arg4
                    set $ElementsFound++
                end
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
            printf "Number of elements found = %u\n", $ElementsFound
        end
        printf "Map size = %u\n", $tree_size
    end
end

document pmap_member
    Prints std::map or std::multimap information. Works for std::multimap as well.
    Syntax: pmap : Prints map size, if T defined all elements or just element(s) with val(s)
    Examples:
    pmap_member m class1 member1 class2 member2 - prints class1.member1 : class2.member2
    pmap_member m class1 member1 class2 member2 lvalue - prints class1.member1 : class2.member2 where class1 == lvalue
end


#
# std::set and std::multiset
#

define pset
    if $argc == 0
        help pset
    else
        set $tree = $arg0
        set $i = 0
        set $node = $tree._M_t._M_impl._M_header._M_left
        set $end = $tree._M_t._M_impl._M_header
        set $tree_size = $tree._M_t._M_impl._M_node_count
        if $argc == 1
            printf "Set "
            whatis $tree
            printf "Use pset to see the elements in the set.\n"
        end
        if $argc == 2
            while $i < $tree_size
                set $value = (void *)($node + 1)
                printf "elem[%u]: ", $i
                p *($arg1*)$value
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
        end
        if $argc == 3
            set $idx = $arg2
            set $ElementsFound = 0
            while $i < $tree_size
                set $value = (void *)($node + 1)
                if *($arg1*)$value == $idx
                    printf "elem[%u]: ", $i
                    p *($arg1*)$value
                    set $ElementsFound++
                end
                if $node._M_right != 0
                    set $node = $node._M_right
                    while $node._M_left != 0
                        set $node = $node._M_left
                    end
                else
                    set $tmp_node = $node._M_parent
                    while $node == $tmp_node._M_right
                        set $node = $tmp_node
                        set $tmp_node = $tmp_node._M_parent
                    end
                    if $node._M_right != $tmp_node
                        set $node = $tmp_node
                    end
                end
                set $i++
            end
            printf "Number of elements found = %u\n", $ElementsFound
        end
        printf "Set size = %u\n", $tree_size
    end
end

document pset
    Prints std::set or std::multiset information. Works for std::multiset as well.
    Syntax: pset : Prints set size, if T defined all elements or just element(s) having val
    Examples:
    pset s - prints set size and definition
    pset s int - prints all elements and the size of s
    pset s int 20 - prints the element(s) with value = 20 (if any) and the size of s
end



#
# std::dequeue
#

define pdequeue
    if $argc == 0
        help pdequeue
    else
        set $size = 0
        set $start_cur = $arg0._M_impl._M_start._M_cur
        set $start_last = $arg0._M_impl._M_start._M_last
        set $start_stop = $start_last
        while $start_cur != $start_stop
            p *$start_cur
            set $start_cur++
            set $size++
        end
        set $finish_first = $arg0._M_impl._M_finish._M_first
        set $finish_cur = $arg0._M_impl._M_finish._M_cur
        set $finish_last = $arg0._M_impl._M_finish._M_last
        if $finish_cur < $finish_last
            set $finish_stop = $finish_cur
        else
            set $finish_stop = $finish_last
        end
        while $finish_first != $finish_stop
            p *$finish_first
            set $finish_first++
            set $size++
        end
        printf "Dequeue size = %u\n", $size
    end
end

document pdequeue
    Prints std::dequeue information.
    Syntax: pdequeue : Prints dequeue size, if T defined all elements
    Deque elements are listed "left to right" (left-most stands for front and right-most stands for back)
    Example:
    pdequeue d - prints all elements and size of d
end



#
# std::stack
#

define pstack
    if $argc == 0
        help pstack
    else
        set $start_cur = $arg0.c._M_impl._M_start._M_cur
        set $finish_cur = $arg0.c._M_impl._M_finish._M_cur
        set $size = $finish_cur - $start_cur
        set $i = $size - 1
        while $i >= 0
            p *($start_cur + $i)
            set $i--
        end
        printf "Stack size = %u\n", $size
    end
end

document pstack
    Prints std::stack information.
    Syntax: pstack : Prints all elements and size of the stack
    Stack elements are listed "top to buttom" (top-most element is the first to come on pop)
    Example:
    pstack s - prints all elements and the size of s
end



#
# std::queue
#

define pqueue
    if $argc == 0
        help pqueue
    else
        set $start_cur = $arg0.c._M_impl._M_start._M_cur
        set $finish_cur = $arg0.c._M_impl._M_finish._M_cur
        set $size = $finish_cur - $start_cur
        set $i = 0
        while $i < $size
            p *($start_cur + $i)
            set $i++
        end
        printf "Queue size = %u\n", $size
    end
end

document pqueue
    Prints std::queue information.
    Syntax: pqueue : Prints all elements and the size of the queue
    Queue elements are listed "top to bottom" (top-most element is the first to come on pop)
    Example:
    pqueue q - prints all elements and the size of q
end



#
# std::priority_queue
#

define ppqueue
    if $argc == 0
        help ppqueue
    else
        set $size = $arg0.c._M_impl._M_finish - $arg0.c._M_impl._M_start
        set $capacity = $arg0.c._M_impl._M_end_of_storage - $arg0.c._M_impl._M_start
        set $i = $size - 1
        while $i >= 0
            p *($arg0.c._M_impl._M_start + $i)
            set $i--
        end
        printf "Priority queue size = %u\n", $size
        printf "Priority queue capacity = %u\n", $capacity
    end
end

document ppqueue
    Prints std::priority_queue information.
    Syntax: ppqueue : Prints all elements, size and capacity of the priority_queue
    Priority_queue elements are listed "top to buttom" (top-most element is the first to come on pop)
    Example:
    ppqueue pq - prints all elements, size and capacity of pq
end



#
# std::bitset
#

define pbitset
    if $argc == 0
        help pbitset
    else
        p /t $arg0._M_w
    end
end

document pbitset
    Prints std::bitset information.
    Syntax: pbitset : Prints all bits in bitset
    Example:
    pbitset b - prints all bits in b
end



#
# std::string
#

define pstring
    if $argc == 0
        help pstring
    else
        printf "String \t\t\t= \"%s\"\n", $arg0._M_data()
        printf "String size/length \t= %u\n", $arg0._M_rep()._M_length
        printf "String capacity \t= %u\n", $arg0._M_rep()._M_capacity
        printf "String ref-count \t= %d\n", $arg0._M_rep()._M_refcount
    end
end

document pstring
    Prints std::string information.
    Syntax: pstring
    Example:
    pstring s - Prints content, size/length, capacity and ref-count of string s
end

#
# std::wstring
#

define pwstring
    if $argc == 0
        help pwstring
    else
        call printf("WString \t\t= \"%ls\"\n", $arg0._M_data())
        printf "WString size/length \t= %u\n", $arg0._M_rep()._M_length
        printf "WString capacity \t= %u\n", $arg0._M_rep()._M_capacity
        printf "WString ref-count \t= %d\n", $arg0._M_rep()._M_refcount
    end
end

document pwstring
    Prints std::wstring information.
    Syntax: pwstring
    Example:
    pwstring s - Prints content, size/length, capacity and ref-count of wstring s
end

#
# C++ related beautifiers (optional)
#

set print pretty on
set print object on
set print static-members on
set print vtbl on
set print demangle on
set demangle-style gnu-v3
set print sevenbit-strings off

#
# pointer array
#

define parray
    if $argc < 1
        help parray
    else
        if $argc == 1
           set $i = 0
           set $current = *($arg0 + $i)
           while $current != 0
            printf "[array element number: %u] \n", $i
            p *$current
                set $i++
                    set $current = *($arg0 + $i)
           end
           printf "array size = %u\n", $i
        end
        
        if $argc == 2
           printf "arg1 is %u\n", $arg1
               printf "[array element number: %u] \n", $arg1
           p *(*($arg0 + $arg1))
        end

        if $argc == 3
           set $i = $arg1
           printf " idx1 = %u, idx2 = %u \n" , $i, $arg2
           while $i < $arg2 
            printf "[array element number: %u] \n", $i
            p *(*($arg0 + $i))
            set $i++
           end
           printf "array size = %u\n", $i
        end
    end
end

document parray
    Prints array infomation.
    Syntax: parray [elemnum | [idx1, idx2]]
    Example:
    parray array 
    parray array elenum
    parray array idx1 idx2
end

##########################################################################
# url:http://blog.csdn.net/hexrain/article/details/12429267
# 当 GDB（即 GNU Project Debugger）启动时，它在当前用户的主目录中寻找一个名为 .gdbinit 的文件；如果该文件存在，则 GDB 就执行该文件中的所有命令。通常，该文件用于简单的配置命令，如设置所需的缺省汇编程序格式（Intel® 或 Motorola）或用于显示输入和输出数据的缺省基数（十进制或十六进制）。它还可以读取宏编码语言，从而允许实现更强大的自定义。该语言遵循如下基本格式：

# define <command>
# <code>
# end
# document <command>
# <help text>
# end


# 该命令称为用户命令。可以将所有其他标准 GDB 命令与流控制指令结合使用并向其传递参数，从而创建一种语言，以允许为正在调试的特定应用程序而自定义调试器的行为。

# 从简单开始：清屏

# 从简单开始并在此基础上逐步发展始终是个好主意。启动 xterm，调出您最喜欢的编辑器，让我们开始创建一个有用的 .gdbinit 文件吧！调试器产生的输出可能非常零乱，根据个人偏好，在使用任何可能产生混乱的工具时，许多人都希望能够清屏。GDB 没有用于清屏的内置命令，但它可以调用 shell 函数；下面的代码跳到调试器之外以使用cls 命令来清除 xterm 控制台：

# define cls
# shell clear
# end
# document cls
# Clears the screen with a simple command.
# end


# 此定义的上半部分（在 define ... end 动词所界定的范围内）构成了在调用该命令时所执行的代码。

# 此定义的下半部分（在 document ... end 所界定的范围内）由 GDB 命令解释器使用，用于在您键入help cls 时显示与cls 命令关联的文本。

# 在将该代码键入 .gdbinit 文件以后，调出 GDB 并输入cls 命令。此时屏幕被清除，您所看到的就只有 GDB 提示符。您的 GDB 自定义之旅已经开始了！

# 文档的重要性

# 如果输入 help user 命令，您会看到已在 .gdbinit 文件中输入的所有用户命令的摘要。.gdbinit 用户定义命令的设计者提供了一个重要特性，您在编写自己的命令时不应忽略该特性：document ... end 子句。随着这些命令数量的增加，维护有关命令如何工作的功能文档将变得非常关键。

# 您可能已经遇到过此问题。假设您在若干年前编写了一些代码；后来当您重新处理它（也许是为了修正错误或通过添加新特性来修改它）时，您发现自己很难理解您自己的代码。优秀的程序员习惯将代码保持得简短、简单和具有良好的文档记录，以便使其可维护。

# 适用于编程代码的一般规则也适用于调试器代码。当您在这个最有价值的职业中披荆斩棘地拼搏时，保留仔细的注释和有良好文档记录的代码将为您带来丰厚的回报。

# GDB 的社区使用

# 人类通过多种方式学习新知识，包括研究其他人已做的工作。初学的汽车工程师首先打开他们第一辆车的发动机罩，拔出他们的工具，开始拆卸部件以进行清理和研究。此类活动使他们能够在保持汽车清洁的同时，还了解了汽车引擎是如何工作的。

# 初学的计算机科学家也没有什么不同，因为他们想了解程序究竟是如何工作的——它们如何与动态库和本机操作系统交互。用于查看这些程序如何工作的工具就是调试器。计算机编程是一项复杂的活动，通过与志趣相投的人群社区交流、提问并获得答案，新的计算机科学家能够满足他们对知识的需要。

# 在全球编程社区中，始终存在大量渴求知识的人。他们不再满足于在计算机上运行程序——他们还想知道得更多。他们想知道这些程序是如何运行的，并乐此不疲地使用最适当的可用工具来探索系统的功能：调试器。通过逆向工程（一种在调试器下运行程序并密切注意它们如何完成所做的工作，从而了解程序工作原理的方法），您可以从所研究程序的创作者已完成的工作中学到大量的知识。编程中涉及的大量底层详细信息没有相关的文档记录；了解它们的唯一方法就是在它们的实际工作中观察它们。

# 逆向工程背上了不应有的坏名声，仿佛那只是黑客和犯罪分子企图破坏副本保护系统和编写蠕虫及病毒来对计算机世界造成损害才会干的事情。虽然存在这样的人，但绝大多数使用调试器和逆向工程来研究程序如何工作的人都是当前和将来的软件工程师，他们希望并需要知道这些程序是如何工作的。他们已形成了在线社区以共享他们的知识和发现；抵制该活动是非建设性的，会阻碍计算机科学的未来发展。

# 本文中定义的许多用户函数就来自于此类知识渴求者的社区。如果希望了解有关他们的更多信息，建议您研究本文的参考资料部分所提到的网站。

# 断点别名

# 许多 GDB 命令太繁琐，这是众所周知的事实。尽管可以对它们进行缩写，但是 GDB 宏语言允许实现进一步的简化。诸如info breakpoints 这样的命令可以变得像bpl 一样简单。清单 1 显示了一组此类简单和高度有用的断点别名 用户命令，您可以将它们添加到不断增长的 .gdbinit 文件中。

# 清单 1：断点别名命令

                
# define bpl
# info breakpoints
# end
# document bpl
# List breakpoints
# end

# define bp
# set $SHOW_CONTEXT = 1
# break * $arg0
# end
# document bp
# Set a breakpoint on address
# Usage: bp addr
# end

# define bpc
# clear $arg0
# end
# document bpc
# Clear breakpoint at function/address
# Usage: bpc addr
# end

# define bpe
# enable $arg0
# end
# document bpe
# Enable breakpoint #
# Usage: bpe num
# end

# define bpd
# disable $arg0
# end
# document bpd
# Disable breakpoint #
# Usage: bpd num
# end

# define bpt
# set $SHOW_CONTEXT = 1
# tbreak $arg0
# end
# document bpt
# Set a temporary breakpoint on address
# Usage: bpt addr
# end

# define bpm
# set $SHOW_CONTEXT = 1
# awatch $arg0
# end
# document bpm
# Set a read/write breakpoint on address
# Usage: bpm addr
# end


# 一旦您习惯了使用断点别名命令，调试会话就变得更有价值了；这些命令极大地提高了调试器的效率，因为它能使您事半功倍。

# 显示进程信息

# 用户定义的 GDB 命令可由其他用户定义的命令调用，从而为各方都带来更高的效率。这就是编程语言的递增性质——编写底层函数，逐渐由更高层的函数调用，直到您只需最少的工作即可让那些工具方便地完成您想要它们完成的任务。要整合到 .gdbinit 文件中的下一组 GDB 定义将在进程被调用时显示有用的进程信息，如清单 2 所示。

# 清单 2： 进程信息命令

                
# define argv
# show args
# end
# document argv
# Print program arguments
# end

# define stack
# info stack
# end
# document stack
# Print call stack
# end

# define frame
# info frame
# info args
# info locals
# end
# document frame
# Print stack frame
# end

# define flags
# if (($eflags >> 0xB) & 1 )
# printf "O "
# else
# printf "o "
# end
# if (($eflags >> 0xA) & 1 )
# printf "D "
# else
# printf "d "
# end
# if (($eflags >> 9) & 1 )
# printf "I "
# else
# printf "i "
# end
# if (($eflags >> 8) & 1 )
# printf "T "
# else
# printf "t "
# end
# if (($eflags >> 7) & 1 )
# printf "S "
# else
# printf "s "
# end
# if (($eflags >> 6) & 1 )
# printf "Z "
# else
# printf "z "
# end
# if (($eflags >> 4) & 1 )
# printf "A "
# else
# printf "a "
# end
# if (($eflags >> 2) & 1 )
# printf "P "
# else
# printf "p "
# end
# if ($eflags & 1)
# printf "C "
# else
# printf "c "
# end
# printf "\n"
# end
# document flags
# Print flags register
# end

# define eflags
# printf "     OF <%d>  DF <%d>  IF <%d>  TF <%d>",\
#         (($eflags >> 0xB) & 1 ), (($eflags >> 0xA) & 1 ), \
#         (($eflags >> 9) & 1 ), (($eflags >> 8) & 1 )
# printf "  SF <%d>  ZF <%d>  AF <%d>  PF <%d>  CF <%d>\n",\
#         (($eflags >> 7) & 1 ), (($eflags >> 6) & 1 ),\
#         (($eflags >> 4) & 1 ), (($eflags >> 2) & 1 ), ($eflags & 1)
# printf "     ID <%d>  VIP <%d> VIF <%d> AC <%d>",\
#         (($eflags >> 0x15) & 1 ), (($eflags >> 0x14) & 1 ), \
#         (($eflags >> 0x13) & 1 ), (($eflags >> 0x12) & 1 )
# printf "  VM <%d>  RF <%d>  NT <%d>  IOPL <%d>\n",\
#         (($eflags >> 0x11) & 1 ), (($eflags >> 0x10) & 1 ),\
#         (($eflags >> 0xE) & 1 ), (($eflags >> 0xC) & 3 )
# end
# document eflags
# Print entire eflags register
# end

# define reg
# printf "     eax:%08X ebx:%08X  ecx:%08X ",  $eax, $ebx, $ecx
# printf " edx:%08X     eflags:%08X\n",  $edx, $eflags
# printf "     esi:%08X edi:%08X  esp:%08X ",  $esi, $edi, $esp
# printf " ebp:%08X     eip:%08X\n", $ebp, $eip
# printf "     cs:%04X  ds:%04X  es:%04X", $cs, $ds, $es
# printf "  fs:%04X  gs:%04X  ss:%04X    ", $fs, $gs, $ss
# flags
# end
# document reg
# Print CPU registers
# end

# define func
# info functions
# end
# document func
# Print functions in target
# end

# define var
# info variables
# end
# document var
# Print variables (symbols) in target
# end

# define lib
# info sharedlibrary
# end
# document lib
# Print shared libraries linked to target
# end

# define sig
# info signals
# end
# document sig
# Print signal actions for target
# end

# define thread
# info threads
# end
# document thread
# Print threads in target
# end

# define u
# info udot
# end
# document u
# Print kernel 'user' struct for target
# end

# define dis
# disassemble $arg0
# end
# document dis
# Disassemble address
# Usage: dis addr
# end


# 十六进制和 ASCII 转储命令

# 要整合进 .gdbinit 文件中的下一组定义包括增强的十六进制和 ASCII 转储函数，如清单 3 所示。程序员注意：若想创建卓越的软件，则应添加宏编程功能，从而允许用户社区能够增强您的工具以适应他们自己的偏好。GDB 就是一个卓越的软件！

# 清单 3: 十六进制和 ASCII 转储命令

                
# define ascii_char
# set $_c=*(unsigned char *)($arg0)
# if ( $_c < 0x20 || $_c > 0x7E )
# printf "."
# else
# printf "%c", $_c
# end
# end
# document ascii_char
# Print the ASCII value of arg0 or '.' if value is unprintable
# end

# define hex_quad
# printf "%02X %02X %02X %02X  %02X %02X %02X %02X",                          \
#                *(unsigned char*)($arg0), *(unsigned char*)($arg0 + 1),      \
#                *(unsigned char*)($arg0 + 2), *(unsigned char*)($arg0 + 3),  \
#                *(unsigned char*)($arg0 + 4), *(unsigned char*)($arg0 + 5),  \
#                *(unsigned char*)($arg0 + 6), *(unsigned char*)($arg0 + 7)
# end
# document hex_quad
# Print eight hexadecimal bytes starting at arg0
# end

# define hexdump
# printf "%08X : ", $arg0
# hex_quad $arg0
# printf " - "
# hex_quad ($arg0+8)
# printf " "

# ascii_char ($arg0)
# ascii_char ($arg0+1)
# ascii_char ($arg0+2)
# ascii_char ($arg0+3)
# ascii_char ($arg0+4)
# ascii_char ($arg0+5)
# ascii_char ($arg0+6)
# ascii_char ($arg0+7)
# ascii_char ($arg0+8)
# ascii_char ($arg0+9)
# ascii_char ($arg0+0xA)
# ascii_char ($arg0+0xB)
# ascii_char ($arg0+0xC)
# ascii_char ($arg0+0xD)
# ascii_char ($arg0+0xE)
# ascii_char ($arg0+0xF)

# printf "\n"
# end
# document hexdump
# Display a 16-byte hex/ASCII dump of arg0
# end

# define ddump
# printf "[%04X:%08X]------------------------", $ds, $data_addr
# printf "---------------------------------[ data]\n"
# set $_count=0
# while ( $_count < $arg0 )
# set $_i=($_count*0x10)
# hexdump ($data_addr+$_i)
# set $_count++
# end
# end
# document ddump
# Display $arg0 lines of hexdump for address $data_addr
# end

# define dd
# if ( ($arg0 & 0x40000000) || ($arg0 & 0x08000000) || ($arg0 & 0xBF000000) )
# set $data_addr=$arg0
# ddump 0x10
# else
# printf "Invalid address: %08X\n", $arg0
# end
# end
# document dd
# Display 16 lines of a hex dump for $arg0
# end

# define datawin
# if ( ($esi & 0x40000000) || ($esi & 0x08000000) || ($esi & 0xBF000000) )
# set $data_addr=$esi
# else
# if ( ($edi & 0x40000000) || ($edi & 0x08000000) || ($edi & 0xBF000000) )
# set $data_addr=$edi
# else
# if ( ($eax & 0x40000000) || ($eax & 0x08000000) || \
#       ($eax & 0xBF000000) )
# set $data_addr=$eax
# else
# set $data_addr=$esp
# end
# end
# end
#  ddump 2
# end
# document datawin
# Display esi, edi, eax, or esp in the data window
# end


# 流程上下文命令

# 最后，当您调试正在运行的进程时，获得进程上下文的总体视图通常是必要的。清单 4 中有用的进程上下文命令是使用前面定义的数据转储函数来构建的。

# 清单 4: 进程上下文命令

                
# define context
# printf "_______________________________________"
# printf "________________________________________\n"
# reg
# printf "[%04X:%08X]------------------------", $ss, $esp
# printf "---------------------------------[stack]\n"
# hexdump $sp+0x30
# hexdump $sp+0x20
# hexdump $sp+0x10
# hexdump $sp
# datawin
# printf "[%04X:%08X]------------------------", $cs, $eip
# printf "---------------------------------[ code]\n"
# x /6i $pc
# printf "---------------------------------------"
# printf "---------------------------------------\n"
# end
# document context
# Print regs, stack, ds:esi, and disassemble cs:eip
# end

# define context-on
# set $SHOW_CONTEXT = 1
# end
# document context-on
# Enable display of context on every program stop
# end

# define context-off
# set $SHOW_CONTEXT = 1
# end
# document context-on
# Disable display of context on every program stop
# end

# # Calls "context" at every breakpoint.
# define hook-stop
#   context
# end

# # Init parameters
# set output-radix 0x10
# set input-radix 0x10
# set disassembly-flavor intel


# hook-stop 是 GDB 在每次发生断点事件时调用的特殊定义。此例中生成了context 清单，以便您能清楚看到处理器执行每条指令的结果。

# 具有新功能的调试会话

# 让我们试验一下这组新工具，以了解它们在调试我们的“老朋友”（由 IBM developerWorks 供稿作家 Nigel Griffiths 编写的 nweb 服务器代码）时的工作情况。（请参见参考资料部分以获得指向 Nigel 的文章“nweb: a tiny, safe Web server (static pages only)”的链接。）

# 在将 es-nweb.zip 文件下载到 $HOME/downloads 目录后，键入如下命令以提取、编译和运行 nweb。（请注意，这里假设您是将该程序编译到中央处理单元 (CPU) 为 Intel Pentium 的 Linux® 工作站——该 .gdbinit 代码是仅为 Intel Pentium 类型的处理器和兼容处理器而编写的。）

# $ cd src
# $ mkdir nweb
# $ cd nweb
# $ unzip $HOME/downloads/es-nweb.zip
# $ gcc -ggdb -O -DLINUX nweb.c -o nweb
# $ ./nweb 9090 $HOME/src/nweb &


# 注意：此示例中的-ggdb 选项与 Nigel 文章中所述的选项不同，因为它告诉 GNU 编译器集 (GCC) 优化该程序，以便于使用 GDB 来进行调试。

# 接下来，为验证 nweb 服务器正在运行，可使用ps 命令来对它进行检查。

# $ ps
#   PID TTY          TIME CMD
#  2913 pts/5    00:00:00 bash
#  4009 pts/5    00:00:00 nweb
#  4011 pts/5    00:00:00 ps


# 最后，在您的计算机上启动 Web 浏览器，并在地址栏键入：http://localhost:9090。

# 下一步是启动 GDB，并与以前一样附加到当前运行的 nweb 实例，如清单 5 所示。

# 清单 5：运行 GDB

                
# $ gdb --quiet
# (gdb) attach 4009
# Attaching to process 4009
# Reading symbols from /home/bill/src/nweb/nweb...done.
# Reading symbols from /lib/tls/libc.so.6...done.
# Loaded symbols for /lib/tls/libc.so.6
# Reading symbols from /lib/ld-linux.so.2...done.
# Loaded symbols for /lib/ld-linux.so.2
# _______________________________________________________________________________
#      eax:FFFFFE00 ebx:00000005  ecx:BFFFF680  edx:00000001     eflags:00000246
#      esi:00000005 edi:00000000  esp:BFFFF66C  ebp:BFFFF6A8     eip:FFFFE410
#      cs:0073  ds:007B  es:007B  fs:0000  gs:0033  ss:007B    o d I t s Z a P c
# [007B:BFFFF66C]---------------------------------------------------------[stack]
# BFFFF69C : 14 0A 13 42  60 53 01 40 - 24 8F 04 08  C8 F6 FF BF ...B`S.@$.......
# BFFFF68C : A6 8E 04 08  14 0A 13 42 - 70 C6 00 40  10 00 00 00 .......Bp..@....
# BFFFF67C : 82 8E 04 08  00 00 00 00 - C4 C6 04 08  98 F6 FF BF ................
# BFFFF66C : A8 F6 FF BF  01 00 00 00 - 80 F6 FF BF  81 EA 0D 42 ...............B
# [007B:FFFFFE00]---------------------------------------------------------[ data]
# FFFFFE00 : Error while running hook_stop:
# Cannot access memory at address 0xfffffe00
# 0xffffe410 in ?? ()
# (gdb)


# -quiet 选项告诉 GDB 调试器仅显示其提示符，而不要显示所有其他通常显示的启动信息。如果需要显示额外的文本信息，可以去掉-quiet 选项。

# attach 4009 命令开始对当前正在运行的 nweb 服务器的调试，并且 GDB 调试器通过读取有关该进程的所有符号信息来做出同样方式的响应。

# 您将会注意到 context 代码运行并显示大量有关当前进程的有用信息，但它不能访问数据段中的内存。这不是个严重问题，并且应该忽略它。有时，保护模式处理器的保护方案不允许您看到您可能希望看到的所有内容。在此情况下，该问题并不重要。

# 下一步，使用 info 命令来列出有关您所研究的程序的信息（请参见清单 6）。

# 清单 6：info 命令列出程序信息

                
# (gdb) info proc
# process 4009
# cmdline = './nweb'
# cwd = '/home/bill/src/nweb'
# exe = '/home/bill/src/nweb/nweb'
# (gdb)


# 在其运行过程中进行观察

# 由于您所观察的是一个实际运行的程序，所以可以设置相应的断点，然后在它响应浏览器请求并向发出请求的浏览器传输 .html 和 .jpg 文件时，对该程序进行观察。清单 7 表明了如何完成该任务。

# 清单 7：设置断点

                
# (gdb) b 188
# Breakpoint 1 at 0x8048e70: file nweb.c, line 188.
# (gdb) commands 1
# Type commands for when breakpoint 1 is hit, one per line.
# End with a line saying just "end".
# >continue
# >end
# (gdb) c
# Continuing.


# 此时，GDB 调试工具已设置为在 nweb 服务器接受 浏览器请求时所在的行中断，调试器将简单地显示请求并继续处理其他请求，而不会中断正在运行的程序。刷新几次浏览器中的http://localhost:9090/ 页面，可以观察到，GDB 调试器显示了断点并继续运行。

# 在刷新浏览器页面的同时，您应该看到如清单 8 所示的断点信息，在 GDB 调试器 xterm 中滚动输出。还可以通过按Ctrl+C 来停止在 nweb 服务器中的调试。停止跟踪以后，可以通过键入quit 命令来退出 GDB 调试器。

# 清单 8： GDB 调试器 xterm 中的断点信息

                
# _______________________________________________________________________________
#      eax:00000000 ebx:00000001  ecx:00000000  edx:00000001     eflags:00000206
#      esi:00000006 edi:00000000  esp:BFFFF690  ebp:BFFFF6A8     eip:08048E70
#      cs:0073  ds:007B  es:007B  fs:0000  gs:0033  ss:007B    o d I t s z a P c
# [007B:BFFFF690]---------------------------------------------------------[stack]
# BFFFF6C0 : 03 00 00 00  D4 86 04 08 - 00 00 00 00  F5 86 04 08 ................
# BFFFF6B0 : 03 00 00 00  F4 F6 FF BF - 04 F7 FF BF  2C 58 01 40 ............,X.@
# BFFFF6A0 : 60 53 01 40  24 8F 04 08 - C8 F6 FF BF  04 55 01 42 `S.@$........U.B
# BFFFF690 : 14 0A 13 42  70 C6 00 40 - 10 00 00 00  14 0A 13 42 ...Bp..@.......B
# [007B:BFFFF690]---------------------------------------------------------[ data]
# BFFFF690 : 14 0A 13 42  70 C6 00 40 - 10 00 00 00  14 0A 13 42 ...Bp..@.......B
# BFFFF6A0 : 60 53 01 40  24 8F 04 08 - C8 F6 FF BF  04 55 01 42 `S.@$........U.B
# [0073:08048E70]---------------------------------------------------------[ code]
# 0x8048e70 <main+718>:   sub    esp,0x4
# 0x8048e73 <main+721>:   lea    eax,[ebp-16]
# 0x8048e76 <main+724>:   push   eax
# 0x8048e77 <main+725>:   push   0x804c6c4
# 0x8048e7c <main+730>:   push   edi
# 0x8048e7d <main+731>:   call   0x80485e4 <accept>
# ------------------------------------------------------------------------------
# Breakpoint 1, main (argc=3, argv=0x1) at nweb.c:188
# 188           if((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0)
# Program received signal SIGINT, Interrupt.
# 0xffffe410 in ?? ()
# (gdb) quit
# The program is running.  Quit anyway (and detach it)? (y or n) y
# Detaching from program: /home/bill/src/nweb/nweb, process 4009
# $


# 可以看到，context 函数所显示的信息远比您通常使用缺省 GDBhook_stop 函数所看到的信息更详细。（您还会注意到，现在也可以访问数据段了。）使用这些 GDB 增强，您可以看到每次到达断点和执行每步操作时的确切 CPU 状态。单步执行每个命令并观察寄存器和内存值如何受影响，这也是学习 Intel 机器语言命令基础知识的理想方法。

# 与所有程序一样，.gdbinit 文件中的代码提供了无穷无尽的增强和改进机会。无论如何，这都不是结束！强烈建议您使用这里描述的命令，并为不断增长的 .gdbinit 自定义集添加更多命令。

############################################################
#########  GDBINIT FILE FOR JERRY MAX VERSION 1.0 ##########
############################################################

# Display 
############################################################
define dip
display /i $pc
end
document dip
print next introduction after each cmd
end
############################################################
define ls
set listsize 20
list
end
document ls
show source file with 20 lines
end
############################################################


# Info 
############################################################
define ia
info args
end
document ia
pirnt args val
end
############################################################
define il
info locals
end
document il
print local variables
end
############################################################
define ir
info reg
end
document ir
print register val
end
############################################################
define it
info threads
end
document it
pirnt threads
end
############################################################
define ifun
info function $arg0
end
document ifun
print functions with regular exp param or all functions
usage: ifun funname
end
############################################################
define ivar
info variables $arg0
end
document ivar
print variables with regular exp param or all vars
usage: ivar varname
end
############################################################
define ilib
info sharedlibrary $arg0
end
document ilib
print sharedlibrary with regular exp param or all libs
usage: ilib libname
end
############################################################
define isig
info signals $arg0
end
document isig
print signal info of signame
usage: isig signame
end
############################################################
define isigs
info signals
end
document isigs
print all signals info
end
############################################################
define r32
printf " eip:%08X\n", $eip
printf " eax:%08X  ebx:%08X  ecx:%08X  edx:%08X\n", $eax, $ebx, $ecx, $edx
printf " esi:%08X  edi:%08X  esp:%08X  ebp:%08X\n", $esi, $edi, $esp, $ebp
printf " cs:%04X  ds:%04X  es:%04X\n", $cs, $ds, $es
printf " fs:%04X  gs:%04X  ss:%04X\n", $fs, $gs, $ss
printf " eflags:%08X\n", $eflags
print $eflags 
end
document r32
print cpu registers(32bit)
end
############################################################

# Memory eXamming
############################################################
define xb
x /32xb $arg0
end
document xb
print memory with 32 byte
usage: xb addr
end
############################################################
define xh
x /32xh $arg0
end
document xh
print memory with 32 double-byte
usage: xh addr
end
############################################################
define xw
x /32xw $arg0
end
document xw
print memory with 32 quad-byte
usage: xw addr
end
############################################################
define xg
x /32xg $arg0
end
document xg
print memory with 32 eight-byte
usage: xg addr
end
############################################################
define xf
x /32f $arg0 
end
document xf
print memory with 32 float number
usage: xf addr
end
############################################################
define xs
x /s $arg0 
end
document xs
print memory with c-style strings
usage: xs addr
end
############################################################
define xc
x /32bc $arg0
end
document xc
print memory with 32 byte ascii
usage: xc addr
end
############################################################
define xi
x /10i $arg0
end
document xi
disassembly 10 introductions
usage: xi addr
end
############################################################
define xic
x /10i $pc
end
document xic
disassembly 10 introductions under current eip
end
############################################################

# Next and Step 
############################################################
define nl
next
info locals
end
document nl
print local variables after next
end
############################################################
define na
next
info args
end
document na 
print args val after next
end
############################################################
define sl
step
info locals
end
document sl
print local variables after step
end
############################################################
define sa
step
info args
end
document sa
print args val after step
end
############################################################
define nn
next
info locals
info args
end
document nn
print local variables and args val after next
end
############################################################
define ss
step
info locals
info args
end
document ss
print local variables and args val after step
end
############################################################
define np
next
p/x $arg0
p/x $arg1
p/x $arg2
p/x $arg3
end
document np
print params val after next (4 params at most)
usage: np param1 param2 param3 param4 
end
############################################################
define sp
step
p/x $arg0
p/x $arg1
p/x $arg2
p/x $arg3
end
document sp 
print param val after step (4 params at most)
usage: sp param1 param2 param3 param4 
end
############################################################

# Stack and Frame
############################################################
define sf
echo +------------------------ stack info ------------------------+\n
info stack
echo +------------------------ frame info ------------------------+\n
info frame
echo +------------------------------------------------------------+\n
end
document sf
print current stack frame info
end
############################################################

# Breakpoint
############################################################
define bl
info breakpoints
end
document bl
show bp list
end
############################################################
define bm
break main
end
document bm
add bp to main
end
############################################################
define bc
clear $arg0
end
document bc
clear bp at function/address
usage: bc param
end
############################################################
define be
enable $arg0
end
document be
enable bp N 
usage: be bp'id
end
############################################################
define bd
disable $arg0
end
document bd
disable bp N
usage: bd bp'id
end
############################################################
define tb
set $SHOW_CONTEXT = 1
tbreak $arg0
end
document tb
set a temporary bp on address
usage: tb addr
end
############################################################
define ba
set $SHOW_CONTEXT = 1
awatch $arg0
end
document ba
set a read/write breakpoint on address
usage: ba addr
end
############################################################
define dab
delete breakpoints
end
document dab
delete all breakpoints!
end
############################################################


# Shell
##########################################################t#
define cs
shell clear
end
document cs
clear screen
end
############################################################
define re
refresh
end
############################################################


# Threads and Process
############################################################
define setfreeze
set scheduler-locking on
end
document setfreeze
freeze other threads when current thread break
end
############################################################
define setunfreeze
set scheduler-locking off
end
document setunfreeze
unfreeze other threads when current thread break
end
############################################################
define setforkchild
set follow-fork-mode child
end
document setforkchild
set follow child process when fork
end
############################################################
define setforkparent
set follow-fork-mode parent
end
document setforkparent
set follow child process when parent
end

############################################################

def  redirect
call (void)close(1)
call (void)close(2)
call (int)open($arg0, 1)
call (int)open($arg0, 2)
call (int)fflush(0)
end
document redirect
redirect("argument")[shell tty], this is used to switch stderr and stdout
to gdb window. The argument is the name of gdb window.
end

def android
help test
end
document test
gdbserver --multi 127.0.0.1:7772
shell adb forward tcp:7771 tcp:7772
shell adb push ./project/service /data/
set remote exec-file /data/service
set solib-absolute-prefix nonexistantpath
target extended-remote 127.0.0.1:7771
file ./project/service
b main
end
