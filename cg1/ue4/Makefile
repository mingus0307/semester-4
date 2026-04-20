GLEW_LIBS=$(shell pkgconf glew --libs)
GLFW_LIBS=$(shell pkgconf glfw3 --libs)

cg1: main.c
	gcc -o cg1 main.c $(GLEW_LIBS) $(GLFW_LIBS) -lm -g -pedantic-errors

3d: 3d.c
	gcc -o 3d  3d.c $(GLEW_LIBS) $(GLFW_LIBS) -lm -g -pedantic-errors

clean:
	rm cg1