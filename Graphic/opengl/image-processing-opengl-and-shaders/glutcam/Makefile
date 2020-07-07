#
#
# Makefile for glutcam


TARGET = glutcam


OBJS = callbacks.o  capabilities.o  device.o  display.o  glutcam.o \
       parseargs.o  shader.o  testpattern.o textfile.o controls.o


LDFLAGS = -L/usr/X11R6/lib -g -lGLEW -lglut  -lGLU -lGL -lXmu -lX11 

# profiling:
# 
# to turn on profiling, recompile with
# PROFILE set to -pg and OPT set to -g
#

#PROFILE= -pg 

# no profiling
PROFILE=

# optimization:
#
# for max optimization, turn OPT to O3.
# for debugging or profiling, use -g

# profiling, debugging
OPT = -g
CPU_OPT =



# max optimization
#OPT = -O3

# set CPU_OPT based on the contents of /proc/cpuinfo. in particular pay 
# attention to the model name and flags. compare against the listing for 
# cpu type on the gcc info pages entry for cpu type 

#CPU_OPT = -march=pentium3

DFLAGS = -DGL_CHECK

CFLAGS = -Wformat=2 -Wall -Wswitch-default -Wswitch-enum \
         -Wunused-parameter -Wextra -Wshadow \
         -Wbad-function-cast -Wsign-compare -Wstrict-prototypes \
         -Wmissing-prototypes -Wmissing-declarations -Wunreachable-code \
	 -ffast-math $(CPU_OPT) $(PROFILE) $(OPT)


$(TARGET): $(OBJS)
	cc  -o $(TARGET) $(OBJS)  $(PROFILE) $(OPT) $(LDFLAGS)



%.o : %.c
	cc -c $(CFLAGS) $(DFLAGS) $<


flow:
	cflow $(OBJS:.o=.c)

# lint -O2 -Wuninitialized -Wextra -fsyntax-only -pedantic 

lint:
	cc -O2  $(DFLAGS) -Wuninitialized -Wextra -fsyntax-only \
	         -pedantic  $(OBJS:.o=.c)

clean:
	@rm $(OBJS)
