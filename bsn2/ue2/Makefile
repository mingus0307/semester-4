
test: test_prog.o 
	gcc -Wall -pedantic-errors $<  -L. -lbib -o $@	

libbib.a: file1.o file2.o 
	ar rcs  libbib.a file1.o file2.o 

%.o: %.c; 
	gcc -c $< -o $@ 