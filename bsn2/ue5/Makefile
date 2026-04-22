gcc_args = -Wall -pedantic-errors -g 
PROGRAMS = a1 a4 a5 a6
OBJECTS = $(PROGRAMS:=.o)

a3 : a3.o 
	gcc $(gcc_args) a3.o -o a3

a4 : a4.o
	gcc $(gcc_args) a4.o -o a4

a5: a5.o 
	gcc $(gcc_args) a5.o -o a5

a6: a6.o 
	gcc $(gcc_args) a6.o -o a6

%.o : %.c 
	gcc $(gcc_args) -c $< -o $@

clean: 
	rm -f $(PROGRAMS) $(OBJECTS)