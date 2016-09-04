APP = gl-cairo-simple

CC = gcc

CFLAGS = -Wall -c -g -std=c99 \
	 `sdl-config --cflags` \
	 `pkg-config --cflags cairo`

LDFLAGS = `sdl-config --libs` \
	  `pkg-config --libs cairo` \
	  -lGL -lGLU -lm

SRCS =  geometry.c \
	opengl-rendering.c \
	cairo-rendering.c \
	exponential-blur.c \
	main.c

OBJS = $(SRCS:.c=.o)

all: $(APP)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# it is important that $(OBJS) stands _before_ $(LDFLAGS)
$(APP):	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o$(APP)

clean:
	rm -f *.o  *~ $(APP) frame.png

