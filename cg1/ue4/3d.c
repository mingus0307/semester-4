#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLuint program;
GLuint vao;   
GLfloat proj[16];
GLfloat model[16]; 
GLfloat view[16]; 

void printMat(GLfloat* m) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%8.3f ", m[col * 4 + row]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply(GLfloat* out, GLfloat* in, GLfloat* ident){
    GLfloat tmp[16]; 
     
    for (int i = 0; i < 16; i++){
        tmp[i] = in[i]; 
    }

    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            out[col *4 + row] = 
                ident[0*4 + row] * tmp[col*4 +0] +
                ident[1*4 + row] * tmp[col*4 +1] +
                ident[2*4 + row] * tmp[col*4 +2] +
                ident[3*4 + row] * tmp[col*4 +3]; 
        }
    }
}

GLfloat* cross_mult(GLfloat* a, GLfloat* b){
    GLfloat* fin = malloc(sizeof(GLfloat) * 3); 

    fin[0] = a[1] * b[2] - a[2] * b[1]; 
    fin[1] = a[2] * b[0] - a[0] * b[2];
    fin[2] = a[0] * b[1] - a[1] * b[0];
    
    return fin; 
}

void norm(GLfloat* vec){
    GLfloat tmp[3]; 
    tmp[0] = vec[0];
    tmp[1] = vec[1];
    tmp[2] = vec[2]; 

    vec[0] = (1 / sqrt((tmp[0] * tmp[0]) + (tmp[1] * tmp[1]) + (tmp[2] * tmp[2]))) * tmp[0];
    vec[1] = (1 / sqrt((tmp[0] * tmp[0]) + (tmp[1] * tmp[1]) + (tmp[2] * tmp[2]))) * tmp[1];
    vec[2] = (1 / sqrt((tmp[0] * tmp[0]) + (tmp[1] * tmp[1]) + (tmp[2] * tmp[2]))) * tmp[2];
}

void identity(GLfloat* out){ 
    for (int i = 0; i < 16; i++){
        out[i] = 0; 
    }
    out[0] = 1; 
    out[5] = 1; 
    out[10] = 1; 
    out[15] = 1; 
    
}

void translate(GLfloat* out, GLfloat* in, GLfloat* v){ 
    GLfloat ident[16]; 
    identity(ident);

    ident[12] = v[0]; 
    ident[13] = v[1]; 
    ident[14] = v[2]; 
    ident[15] = 1; 
    
    multiply(out, in, ident); 
}

void scale(GLfloat* out, GLfloat* in, GLfloat* v){
    GLfloat ident[16]; 
    identity(ident); 

    ident[0] = v[0]; 
    ident[5] = v[1]; 
    ident[10] = v[2]; 
    ident[15] = 1; 

    multiply(out, in, ident);
}

void rotatez(GLfloat* out, GLfloat* in, GLfloat angle){
    GLfloat ident[16]; 
    identity(ident); 

    ident[0] = cos(angle); 
    ident[1] = sin(angle); 
    ident[4] = -sin(angle);
    ident[5] = cos(angle); 
    
    multiply(out, ident, in); 
}

void lookAt(GLfloat* out, GLfloat* eye, GLfloat* center, GLfloat* up){
    GLfloat m_r[16]; 
    identity(m_r);

    GLfloat m_t[16]; 
    identity(m_t);

    // Herleitung n
    GLfloat n[3]; 
    n[0] = eye[0] - center[0]; 
    n[1] = eye[1] - center[1]; 
    n[2] = eye[2] - center[2];
    norm(n);
    // Herleitung u 
    GLfloat* u; 
    u = cross_mult(up, n); 
    norm(u);
    // Herleitung v 
    GLfloat* v; 
    v = cross_mult(n, u);  
    norm(v); 

    // build rotation matrix 
    m_r[0] = u[0];
    m_r[4] = u[1];
    m_r[8] = u[2];

    m_r[1] = v[0];
    m_r[5] = v[1];
    m_r[9] = v[2];

    m_r[2] = n[0];
    m_r[6] = n[1];
    m_r[10]= n[2];

    m_t[12] = -eye[0];
    m_t[13] = -eye[1];
    m_t[14] = -eye[2];

    // multiply to view matrix 
    multiply(out, m_r, m_t); 
    free(u); 
    free(v); 

}

void perspective(float* out, float fovy, float aspect, float near, float far){
    float rad = fovy * M_PI / 180.0f;
    float f = 1.0f / tan(rad / 2.0f);  // = cotangent(fovy/2)

    for (int i = 0; i < 16; i++) out[i] = 0.0f;

    out[0]  = f / aspect;
    out[5]  = f;
    out[10] = -(far + near) / (far - near);
    out[11] = -1.0f;
    out[14] = -(2.0f * far * near) / (far - near);
    // out[15] bleibt 0
}


void render_loop(GLfloat* out, GLuint pos_loc){ 
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);  
    GLfloat v[3];
    float amplitude = 0.5f;  
    v[0] = amplitude * sin(glfwGetTime() / 1.5f); 
    v[1] = amplitude * cos(glfwGetTime() / 1.5f);
    v[2] = 0.0; 
    float angle = glfwGetTime() * 2.0f * M_PI / 6.0f;

    identity(out); 

    // rotation um mehrere achsen 
    float angleY = glfwGetTime() * 2.0f * M_PI / 6.0f;
    float angleX = 0.5f;  // leichte Neigung damit man oben/unten sieht

    // Rotation um Y-Achse
    GLfloat rotY[16];
    identity(rotY);
    rotY[0]  =  cos(angleY);
    rotY[8]  =  sin(angleY);
    rotY[2]  = -sin(angleY);
    rotY[10] =  cos(angleY);

    // Rotation um X-Achse  
    GLfloat rotX[16];
    identity(rotX);
    rotX[5]  =  cos(angleX);
    rotX[6]  =  sin(angleX);
    rotX[9]  = -sin(angleX);
    rotX[10] =  cos(angleX);

    identity(out);
    multiply(out, rotY, rotX);  // erst X, dann Y

    GLuint projLoc = glGetUniformLocation(program, "projection");
    GLuint modelLoc = glGetUniformLocation(program, "model");
    GLuint viewLoc = glGetUniformLocation(program, "view"); 
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, out);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
    
    printMat(out); 
    glUniformMatrix4fv(pos_loc, 1, GL_FALSE, out);
    glBindVertexArray(vao); 
    glDrawArrays(GL_TRIANGLES, 0, 30); 
}

    

void init(){
    
    // create vertex shader 
    const char* vertexText = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 vertexColor;\n"
        "uniform vec3 color;\n"
        "uniform mat4 offset;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "void main() {\n"
        "   vertexColor = aColor;\n"
        "   gl_Position = projection * view * model * vec4(aPosition, 1.0);\n"
        "}\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexText, NULL); 
    glCompileShader(vertexShader);
    GLint status; 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status); 

    if (!status){
        printf("ERROR compiling vertex shader:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog); 
        printf(infoLog); 
    } 

    // create fragment shader 
    const char* fragmentText = 
        "#version 330 core\n"
        "in vec3 vertexColor;\n"
        "void main() {\n"
        "   gl_FragColor = vec4(vertexColor, 1.0);\n"
        "}\n";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentText, NULL); 
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status); 

    if (!status){
        printf("ERROR compiling fragment shader:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog); 
        printf(infoLog); 
    } 
    // create and link shader programm 

    program = glCreateProgram(); 
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader); 

    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &status); 
    if (!status){
        printf("ERROR linking Program:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog); 
        printf(infoLog); 
    } 
    glValidateProgram(program); 
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status); 
    if (!status){
        printf("ERROR validation:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog); 
        printf(infoLog); 
    } 
    // create triangle buffer 

    GLfloat triangleVertice[] = 
    { 
        //x         //y       //z      //r       //g       //b
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        //back 
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

        //right
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

        0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        //left
        -0.5f, -0.5f, -0.5f, 1.4f, 0.6f, 0.0f,
        -0.5f,  -0.5f, 0.5f,  1.4f, 0.6f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.4f, 0.6f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.4f, 0.6f, 0.0f,
        -0.5f,  0.5f, 0.5f,  1.4f, 0.6f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.4f, 0.6f, 0.0f,        

        //top
        -0.5f, 0.5f, 0.5f, 0.4f, 1.6f, 1.0f,
        0.5f,  0.5f, 0.5f,  0.4f, 1.6f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.4f, 1.6f, 1.0f,

        -0.5f, 0.5f, 0.5f,  0.4f, 1.6f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.4f, 1.6f, 1.0f,
        0.5f,  0.5f, -0.5f, 0.4f, 1.6f, 1.0f,

    };



    GLuint triangleVertexBufferObject; 
    glGenBuffers(1, &triangleVertexBufferObject); 

    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertice), triangleVertice, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // create VAO 
    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao); 
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject); 
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(GLfloat),
        0 

    );
    glEnableVertexAttribArray(0); 
    
    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat)) 
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600); 
    
    perspective(proj, 60.0f, 800.0f/600.0f, 0.1f, 100.0f);
    lookAt(view,
       (GLfloat[]){0,0,3},   // eye
       (GLfloat[]){0,0,0},   // center
       (GLfloat[]){0,1,0});  // up
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glUseProgram(program); 
    
    glEnable(GL_DEPTH_TEST); 

    GLuint projLoc = glGetUniformLocation(program, "projection");
    GLuint modelLoc = glGetUniformLocation(program, "model");


    
    GLuint pos_loc = glGetUniformLocation(program, "offset");
    GLfloat* wMatrix = malloc(sizeof(GLfloat) * 16); 
    render_loop(wMatrix, pos_loc);     
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height); 
}

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    GLFWwindow *window  = glfwCreateWindow(800, 600, "CG1", NULL, NULL); 
    if (!window){
        printf("failed to create window !\n"); 
        glfwTerminate(); 
        return -1; 
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    glfwMakeContextCurrent(window); 
    glewInit(); 

    init(); 
    while (!glfwWindowShouldClose(window)){
        draw(); 
        glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }

    glfwTerminate(); 
    return 0; 
}