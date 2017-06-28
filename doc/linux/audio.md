
# aplay
aplay -r44100 -f cd test.pcm
aplay -f S16_LE -c2 -r44100 test.pcm

# ffmpeg
ffmpeg -i audio.raw.aac -f s16le -ar 44100 -acodec pcm_s16le output.pcm
[ffmpeg](http://www.cnblogs.com/wangkangluo1/archive/2012/07/10/2585095.html)
