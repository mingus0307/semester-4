#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

GLuint program;
GLuint vao;  

void identity(GLfloat* out){
    for (int i = 0; i < 15; i++){
        out[i] = 0; 
    }
    out[0] = 1; 
    out[5] = 1; 
    out[10] = 1; 
    out[15] = 1; 
}

void translate(GLfloat* out, GLfloat* in, GLfloat* v){
    GLfloat* ident = malloc(sizeof(GLfloat) * 16); 
    identity(ident);

    ident[12] = v[0]; 
    ident[13] = v[1]; 
    ident[14] = v[2]; 
    ident[15] = v[3]; 

    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            out[col *4 + row] = 
                in[0*4 + row] * ident[col*4 +0] +
                in[1*4 + row] * ident[col*4 +1] +
                in[2*4 + row] * ident[col*4 +2] +
                in[3*4 + row] * ident[col*4 +3]; 
        }
    }
}

int main(){
    GLfloat* id = malloc(sizeof(GLfloat) * 16);  
    identity(id); 

    for (int i = 0; i < 16; i++){
        printf("%.0f ", id[i]); 
        if((i+1) % 4 == 0){
            printf("\n"); 
        }
    }
}