gcc_args = -Wall -pedantic-errors -g
PROGRAMS = a3
OBJECTS = $(PROGRAMS:=.o)


a3: a3.o 
	gcc $(gcc_args) a3.o -o a3


%.o: %.c 
	gcc $(gcc_args) -c $< -o $@

clean: 
	rm -f $(PROGRAMS) $(OBJECTS)