gcc_args = -Wall -pedantic-errors -g
PROGRAMS = a3 a4 a5 a6 a7 a8
OBJECTS = $(PROGRAMS:=.o)


a3: a3.o 
	gcc $(gcc_args) a3.o -o a3

a4: a4.o 
	gcc $(gcc_args) a4.o -o a4

a5: a5.o 
	gcc $(gcc_args) a5.o -o a5

a6: a6.o 
	gcc $(gcc_args) a6.o -o a6

a7: a7.o 
	gcc $(gcc_args) a7.o -o a7

a8: a8.o 
	gcc $(gcc_args) a8.o -o a8

a9: a9.o 
	gcc $(gcc_args) a9.o -o a9
	
%.o : %.c
	gcc $(gcc_args) -c $< -o $@


clean: 
	rm -f $(PROGRAMS) $(OBJECTS)