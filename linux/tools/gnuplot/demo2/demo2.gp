#!/usr/bin/gnuplot

set terminal png #输出格式为png文件
set output "image_output_file.png"  #指定数据文件名称
set title "KPI"
set ylabel 'net added count'
set yrange [0:700000] #设置Y轴的范围

set key right top height 3 spacing 2  #设置图例
set border 3 lt 3 lw 2  #这会让你的坐标图的border更好看
set grid #显示网格
set key box #它把图例用一个box装起来
set xtics nomirror rotate #只需要一个x轴
set ytics mirror #只需要一个y轴
set mytics 5 #可以增加分刻度
set mxtics 1

# set pointsize 0.4 #点的像素大小
# set datafile separator '\t' #数据文件的字段用\t分开

#注意表的数据导出的时候默认是按照tab来分隔的
set xdata time #x轴代表时间
set timefmt "%Y-%m-%d %H:%M:%S"  #数据文件中时间的格式
#set format x "%Y-%m-%d %H:%M"    #x坐标轴显示的数据

#设置图像的大小 为标准大小的2倍
#set size 2.3,2
# plot 'unit_data.txt' using 1:2 w lp lt 1 lw 2 title "第二列", \
#      'unit_data.txt' using 1:3 w lp lt 2 lw 2 pt 7 title "第三列", \
#      'unit_data.txt' using 1:4 w lp lt 3 lw 2 title "第四列", \
#      'unit_data.txt' using 1:5 w lp lt 4 lw 2 title "第五列", \
#      'unit_data.txt' using 1:6 w lp lt 5 lw 2 title "第六列", \
#      'unit_data.txt' using 1:7 w lp lt 6 lw 2 title "第七列"

plot 'unit_data.txt' using 1:3 with line title "第三列", \
     'unit_data.txt' using 1:4 with line title "第四列", \
     'unit_data.txt' using 1:5 with line title "第五列", \
     'unit_data.txt' using 1:6 with line title "第六列", \
     'unit_data.txt' using 1:7 with line title "第七列"
