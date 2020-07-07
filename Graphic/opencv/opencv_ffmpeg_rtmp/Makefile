PKGS=opencv libavdevice libavutil libavformat libavfilter libavcodec libavresample
LIBS:=`pkg-config --libs ${PKGS}`
CFLAGS:=`pkg-config --cflags ${PKGS}`

all:
	g++ --std=c++11 main.cpp ${CFLAGS} ${LIBS} -o main
	g++ --std=c++11 rtmp-stream.cpp ${CFLAGS} ${LIBS} -o rtmp-stream
