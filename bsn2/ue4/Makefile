gcc_args = -Wall -pedantic-errors -g 
PROGRAMS = a1 a2 a2c a3 a4
OBJECTS = $(PROGRAMS:=.o)

a1 : a1.o 
	gcc $(gcc_args)  a1.o -o a1 

a2: a2.o 
	gcc $(gcc_args) a2.o -o a2

a2c: a2c.o 
	gcc $(gcc_args) a2c.o -o a2c

a3: a3.o 
	gcc $(gcc_args) a3.o -o a3

a4: a4.o 
	gcc $(gcc_args) a4.o -o a4

%.o: %.c 
	gcc $(gcc_args) -c $< -o $@

clean: 
	rm -f $(PROGRAMS) $(OBJECTS)
