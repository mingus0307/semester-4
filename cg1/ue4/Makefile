GLEW_LIBS=$(shell pkgconf glew --libs)
GLFW_LIBS=$(shell pkgconf glfw3 --libs)

cg1: main.c
	gcc -o cg1 main.c $(GLEW_LIBS) $(GLFW_LIBS) -lm -g -pedantic-errors

clean:
	rm cg1