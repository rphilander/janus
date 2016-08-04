# Makefile

INCLUDES = /usr/local/Cellar/readline/6.3.8/include/
LIBS = /usr/local/Cellar/readline/6.3.8/lib/
CC = clang++
CFLAGS  = -g -Wall -I $(INCLUDES)

OBJS = main.o stringutils.o

default: main

main: $(OBJS)
	$(CC) $(CFLAGS) -L $(LIBS) -o main $^ -lreadline

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) main
