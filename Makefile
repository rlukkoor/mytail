all: mytail.c
		cc -g -Wall -o mytail mytail.c

clean:
		$(RM) mytail 
