PKG_CONFIG=`pkg-config --libs --cflags libavformat libavcodec libswresample libavutil`

all:
#	gcc audio_decoder.c -o out ${PKG_CONFIG} -o audio_decoder
	gcc decode_audio.c ${PKG_CONFIG} -o decode_audio
	gcc resampling_audio.c ${PKG_CONFIG} -o resampling_audio -lm
	gcc wav_parser.c ${PKG_CONFIG} -o wav_parser -lm
