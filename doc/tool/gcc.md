# library
[LibraryArchives-StaticAndDynamic](http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html)

# linker
    -L 指定链接目录
    -rpath-link 链接库自己依赖的查找目录
    -rpath 运行时查找目录
    gcc -Wl,--start-group a.o b.o c.o -Wl,end-group
