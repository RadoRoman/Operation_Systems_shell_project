CC = gcc
CCFLAGS = -Wall

berger_roman: berger_roman.o
	$(CC) $(CCFLAGS) -o berger_roman berger_roman.o -pthread

clean:
	- rm *.o
	- rm berger_roman