GLEW_LIBS=$(shell pkgconf glew --libs)
GLFW_LIBS=$(shell pkgconf glfw3 --libs)

cg1: main.c
	gcc -o cg1 main.c $(GLEW_LIBS) $(GLFW_LIBS) -lm

ue3: logo.c
	gcc -o ue3 logo.c $(GLEW_LIBS) $(GLFW_LIBS) -lm 