PKG_CONFIG=`pkg-config --libs --cflags libavcodec libswresample libavutil`

all:
#	gcc audio_decoder.c -o out ${PKG_CONFIG} -o audio_decoder
	gcc decode_audio.c -o out ${PKG_CONFIG} -o decode_audio
	gcc resampling_audio.c -o out ${PKG_CONFIG} -o resampling_audio -lm
