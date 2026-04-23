#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <sys/select.h>

GLuint program; 
GLuint vao; 


GLfloat make_angle_to_float(float n){

}

void init(){
    /*VERTEX SHADER*/
    const char* vertexText = 
        "#version 330 core\n"
        "layout (location = 0) in vec2 aPosition;\n"
        "layout (location = 1) in vec3 hsv;\n"
        "out vec3 vertexValue;\n"
        "void main() {\n"
        "   vertexValue = hsv;\n"
        "   gl_Position = vec4(aPosition, 0.0, 1.0);\n"
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

    /*FRAGEMENT SHADER*/
    const char* fragmentText = 
        "#version 330 core\n"
        "in vec3 vertexValue;\n"
        "uniform vec3 fragColor1;\n"
        "uniform float time;\n"
        "vec3 hsv2rgb(vec3 c){\n"
        "   float h = floor(c.x / 60);\n"
        "   float f = (c.x / 60) - h;\n"
        "   "
        "}\n"
        "void main() {\n"
        //"   float wave = sin(vertexValue * 10.00);\n"
        //"   float t = (wave + 1.0) / 3.0;\n"
        "   vec3 color = hsv2rgb(vertexValue);\n"
        //"   vec3 color = mix(fragColor1, fragColor2, step(0.5f, vertexValue));\n"
        //"   vec3 color = mix(fragColor1, fragColor2, smoothstep(0.3f, 0.7f, vertexValue));\n"        
        //"   vec3 color = mix(fragColor1, fragColor2, t);\n"                
        //"   vec3 color = mix(fragColor1, fragColor2, t);\n"                        
        "   gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragmentShader, 1, &fragmentText, NULL); 
    glCompileShader(fragmentShader); 
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    
    if (!status){
        printf("ERROR compiling fragment shader:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog); 
        printf("%s", infoLog);
        printf("\n");  
    } 

    program = glCreateProgram();
    glAttachShader(program, vertexShader); 
    glAttachShader(program,fragmentShader);
    
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &status); 
    if (!status){
        printf("ERROR linking Program:"); 
        GLchar infoLog[1024]; 
        glGetProgramInfoLog(program, 1024, NULL, infoLog); 
        printf("%s", infoLog); 
        printf("\n");
    } 
    glValidateProgram(program); 
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status); 
    if (!status){
        printf("ERROR validation:"); 
        GLchar infoLog[1024]; 
        glGetShaderInfoLog(program, 1024, NULL, infoLog); 
        printf("%s",infoLog); 
        printf("\n");
    } 

    GLfloat triangleVertice[] = 
    {   //x         //y        //h      //s         //v
        -0.75f, 0.5f, 36.4f, 0.0f, 0.0f,
        -0.75f, -0.5f, 36.4f, 0.0f, 0.0f,
        0.75f, -0.5f,45.0f, 0.0f, 0.0f,

        0.75f, 0.5f, 45.2f,  0.0f, 0.0f,
        0.75f, -0.5f, 76.3f,  0.0f, 0.0f,
        -0.75f, 0.5f, 64.3f, 0.0f, 0.0f,

    };
    GLuint triangleVertexBufferObject;
    glGenBuffers(1, &triangleVertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertice), triangleVertice, GL_STATIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    /*VERTEX ARRAY OBJECT*/
    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao); 
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject);

    glVertexAttribPointer(
        0, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        5 * sizeof(GLfloat),
        0 
    ); 

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        5 * sizeof(GLfloat),
        (GLvoid*)(2* sizeof(GLfloat)) 
    ); 

    glEnableVertexAttribArray(1); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, 800, 600); 
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);  
    glUseProgram(program); 
    GLuint frag1 = glGetUniformLocation(program, "fragColor1");  
    glUniform3f(frag1, 1.0f, 0.0f, 0.0f);
    glBindVertexArray(vao); 
    glDrawArrays(GL_TRIANGLES, 0, 6); 
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height); 
}

int main(void){

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

