# Makefile

# INCLUDES = -I /usr/local/Cellar/readline/6.3.8/include/ -I /Users/rod/Dev/janus/thirdparty/folly-2016.07.26/folly
INCLUDES = -I /usr/local/Cellar/readline/6.3.8/include/
LIBS = -L /usr/local/Cellar/readline/6.3.8/lib/
CC = clang++
CFLAGS  = -g -std=c++11 -Wall -Wno-c++11-extensions $(INCLUDES)

OBJS = janus.o semaphore.o stringutils.o status.o interface_manager.o simple_interface_manager.o \
	interface.o readline_atom.o writeline_atom.o

default: janus

# export DYLD_LIBRARY_PATH=/Users/rod/Dev/janus/thirdparty/actor-framework-0.15.0a1/build/lib
janus: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o janus $^ -lreadline

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) janus
