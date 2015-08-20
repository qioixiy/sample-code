## bash
[bash 内置函数](http://blog.csdn.net/hejinjing_tom_com/article/details/16116455)
- bash -x | 执行前打印
- bash -n | 只运行不执行

## sh expr
- `echo "2+1-5*1.111" | bc`, echo mothed
- `bc <<< "1+2+3+3.3333"`, here-doc mothed
- ```var=`echo "$var 5"|awk '{printf("%g",$1+$2)}'```, awk mothed
