# use pkg-config for getting CFLAGS and LDLIBS
FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

CFLAGS += -Wall -g
CFLAGS += $(shell pkg-config --cflags $(FFMPEG_LIBS))
CFLAGS += $(shell sdl-config --cflags)
CFLAGS += -I./common/include
CPPFLAGS += $(CFLAGS) -D__STDC_CONSTANT_MACROS
LDLIBS += $(shell pkg-config --libs $(FFMPEG_LIBS)) -lSDL

EXAMPLES=player
#export PKG_CONFIG_PATH=/lib/pkgconfig
OBJS=$(addsuffix .o,$(EXAMPLES))
OBJS += convertAndSaveAsBmp.o
OBJS += h264_queue.o
OBJS += common/common.a

# the following examples make explicit use of the math library
LDLIBS += -lm -lstdc++

.phony: all clean-test clean

all: $(EXAMPLES)
run: all
	./$(EXAMPLES)

$(EXAMPLES): $(OBJS)
	gcc  -g $(OBJS) -o ../$@ $(LDLIBS)

common/common.a:
	make -C common
clean:
	make -C common clean
	$(RM) $(EXAMPLES) $(OBJS) *.yuv

test: common/common.a
	gcc -I./common/include -Ic:/bin/home/gtk-bundle/include   -Wall -g -Ic:/bin/home/gtk-bundle/include   -Wall -g -I/usr/include/SDL -D_GNU_SOURCE=1 -D_TEST_ h264_queue.c -c
	gcc h264_queue.o common/common.a -o h264_queue
