
## awk 提取特定数据
awk '{print gensub(/.*href="(.*)".*/,"\\1", "g")}';;()里面的内容通过\\n引用

## 获取socket状态
http://blog.csdn.net/shootyou/article/details/6615051
netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'
