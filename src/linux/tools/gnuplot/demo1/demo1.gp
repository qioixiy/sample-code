#!/usr/bin/gnuplot

set terminal png font './font/fzht.ttf,11' size 1000,1000
set output "w.png"
set multiplot layout 2, 1 title "LAMOST 天气信息"

#
set size ratio 0.4
set title "LAMOST 天气信息 - 温度 露点温度 相对湿度图" font './font/fzht.ttf,13'
set xdata time
set xlabel "\n时间"
set ylabel "温度 / 露点温度 (C)"
set timefmt "%Y-%m-%d %H:%M:%S"
set grid
#set yrange [-3:6]
set y2label "相对湿度 (%)"
set y2tics
plot 'w.dat' using 1:4 with line title "温度", \
     'w.dat' using 1:10 with line title "露点温度", \
     'w.dat' using 1:5 axes x1y2 with line title "相对湿度"

#
set title "LAMOST 天气信息 - 风速 大气压图" font './font/fzht.ttf,13'
set xdata time
set xlabel "\n时间"
set ylabel "风速 (m/s)"
set timefmt "%Y-%m-%d %H:%M:%S"
set grid
#set nokey
set y2label "大气压 (hPa)"
set y2tics
plot 'w.dat' using 1:8 with line title "瞬时最大风速", \
     'w.dat' using 1:7 with line title "平均风速", \
     'w.dat' using 1:6 axes x1y2 with line title "大气压"