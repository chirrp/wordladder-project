#Variables
COMPILE = g++
FLAGS = -g -W -Wall -Werror -ansi

#Targets

all: 
	$(COMPILE) $(FLAGS) main.cc

clean:
	rm -rf *~ *.o a.out
