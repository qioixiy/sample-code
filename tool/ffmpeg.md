## 
* ffmpeg -i 1.mp4 -an -pix_fmt nv12 -s 192x144 1.yuv
* ffplay -pix_fmt nv12 -s 192x144 1.yuv
* ffplay -f rawvideo -video_size 640x480 1.yuv
### YV12: 亮度（行×列） ＋ V（行×列/4) + U（行×列/4）
### I420: 亮度（行×列） ＋ U（行×列/4) + V（行×列/4）

## ffmpeg scale
ffmpeg -s 480x272 -pix_fmt yuv420p -i src01_480x272.yuv -s 1280x720 -sws_flags bilinear -pix_fmt yuv420p src01_bilinear_1280x720.yuv
ffmpeg -s 480x272 -pix_fmt yuv420p -i src01_480x272.yuv -s 1280x720 -sws_flags bicubic -pix_fmt yuv420p src01_bicubic_1280x720.yuv
ffmpeg -s 480x272 -pix_fmt yuv420p -i src01_480x272.yuv -s 1280x720 -sws_flags neighbor -pix_fmt yuv420p src01_neighbor_1280x720.yuv
