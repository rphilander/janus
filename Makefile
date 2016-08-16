# Makefile

INCLUDES = -I /usr/local/Cellar/readline/6.3.8/include/
LIBS = -L /usr/local/Cellar/readline/6.3.8/lib/
CC = clang++
CFLAGS  = -g -std=c++11 -Wall -Wno-c++11-extensions $(INCLUDES)

OBJS = main.o stringutils.o status.o

default: janus

janus: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o janus $^ -lreadline

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) janus
