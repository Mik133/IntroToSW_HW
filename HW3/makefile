CC = gcc
CCLINK=$(CC)
CFLAGS = -g -Wall -std=c99
OBJS = main.o stack.o student.o

prog.exe : $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe
	
main.o : main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

student.o : student.c student.h
	$(CC) $(CFLAGS) -c student.c
	
clean:
	rm -rf *.o *.exe