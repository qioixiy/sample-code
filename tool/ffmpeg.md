## 
* ffmpeg -i 1.mp4 -an -pix_fmt nv12 -s 192x144 1.yuv
* ffplay -pix_fmt nv12 -s 192x144 1.yuv
* ffplay -f rawvideo -video_size 640x480 1.yuv
### YV12: 亮度（行×列） ＋ V（行×列/4) + U（行×列/4）
### I420: 亮度（行×列） ＋ U（行×列/4) + V（行×列/4）

