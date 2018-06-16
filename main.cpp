#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void fixingVertexValues();

float color = 0;
unsigned int VBO, VAO, EBO;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left
    // second triangle
     0.2f, -0.6f, 0.0f,  // bottom right
    -0.6f, -0.6f, 0.0f,  // bottom left
    -0.6f,  0.5f, 0.0f   //top left
    };
unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,  // first Triangle
        3, 4, 5   // second Triangle
    };


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.3f, 0.3f, 1.0f);\n"
    "}\n\0";


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glViewport(0, 0, 800, 600); //Verhältnis des Fensters zu 0 - 1 Values.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Callback Funktion falls das Fenster resized wird.


    ///////////////////////////////////////////////////////////////////////////////////////
    //////SHADER///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    Shader ourShader("coordinate_systems.vs", "coordinate_systems.fs");

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ////////////////SHADER PROGRAM ///////////


    int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    fixingVertexValues();
    ///////////////////////////////////////////////////////////////////////////////////////
    //LOOP SECTION/////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(color, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glm::mat4 view;
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("view", view);



        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        fixingVertexValues();

        std::this_thread::sleep_for (std::chrono::milliseconds(20));
    }


    ///////////////////////////////////////////////////////////////////////////////////////

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    std::cout<<vertices[11]<<std::endl;

    return 0;
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_UP)== GLFW_PRESS)
    {
        color=color+0.02;
    }
        if(glfwGetKey(window, GLFW_KEY_DOWN)== GLFW_PRESS)
    {
        color=color-0.02;
    }

        if(glfwGetKey(window, GLFW_KEY_RIGHT)== GLFW_PRESS)
    {
        vertices[9]=vertices[9]+0.02;
        vertices[12]=vertices[12]+0.02;
        vertices[15]=vertices[15]+0.02;
    }

        if(glfwGetKey(window, GLFW_KEY_LEFT)== GLFW_PRESS)
    {
        vertices[9]=vertices[9]-0.02;
        vertices[12]=vertices[12]-0.02;
        vertices[15]=vertices[15]-0.02;
    }

        if(glfwGetKey(window, GLFW_KEY_A)== GLFW_PRESS)
    {
        vertices[11]=vertices[11]-0.02;
        vertices[14]=vertices[14]-0.02;
        vertices[17]=vertices[17]-0.02;
    }
        if(glfwGetKey(window, GLFW_KEY_D)== GLFW_PRESS)
    {
        vertices[11]=vertices[11]+0.02;
        vertices[14]=vertices[14]+0.02;
        vertices[17]=vertices[17]+0.02;
    }

}

void fixingVertexValues()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}



