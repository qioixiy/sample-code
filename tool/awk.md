
## awk 提取特定数据
awk '{print gensub(/.*href="(.*)".*/,"\\1", "g")}';;()里面的内容通过\\n引用

