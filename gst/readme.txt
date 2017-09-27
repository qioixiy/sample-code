gst-inspect-1.0 mad
gst-launch-1.0 filesrc location=call_Sound.mp3 ! mad ! audioconvert ! alsasink
gst-launch-1.0 playbin uri=http://docs.gstreamer.com/media/sintel_trailer-480p.webm
gst-launch-1.0 souphttpsrc location=http://docs.gstreamer.com/media/sintel_trailer-480p.webm ! matroskademux ! video/x-vp8 ! matroskamux ! filesink location=sintel_video.mkv
gst-launch-1.0 souphttpsrc location=http://docs.gstreamer.com/media/sintel_trailer-480p.webm ! matroskademux name=d ! queue ! vp8dec ! ffmpegcolorspace ! autovideosink d. ! queue ! vorbisdec ! audioconvert ! audioresample ! autoaudiosink

https://linux.die.net/man/1/gst-launch-0.10
http://blog.csdn.net/sakulafly/article/details/21455637
[gst 命令](http://blog.csdn.net/wangzhen209/article/details/42194739)
