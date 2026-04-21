gcc_args = -Wall -pedantic-errors -g 
PROGRAMS = a1 a4  
OBJECTS = $(PROGRAMS:=.o)

a3 : a3.o 
	gcc $(gcc_args) a3.o -o a3

a4 : a4.o
	gcc $(gcc_args) a4.o -o a4

%.o : %.c 
	gcc $(gcc_args) -c $< -o $@

clean: 
	rm -f $(PROGRAMS) $(OBJECTS)