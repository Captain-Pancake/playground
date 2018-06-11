#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float color = 0;

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
}

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
    //LOOP SECTION/////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(color, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ///////////////////////////////////////////////////////////////////////////////////////

    glfwTerminate();
    return 0;
}



