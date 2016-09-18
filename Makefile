# Makefile

# INCLUDES = -I /usr/local/Cellar/readline/6.3.8/include/ -I /Users/rod/Dev/janus/thirdparty/folly-2016.07.26/folly
INCLUDES = -I /usr/local/Cellar/readline/6.3.8/include/
LIBS = -L /usr/local/Cellar/readline/6.3.8/lib/
CC = clang++
CFLAGS  = -O0 -g -std=c++11 -Wall -Wno-c++11-extensions -Werror $(INCLUDES)

OBJS = status.o janus.o atom.o runtime.o readline_atom.o writeline_atom.o

default: janus

janus: $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lreadline -o janus $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) janus
