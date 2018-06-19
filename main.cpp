
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <thread>
#include <chrono>
#include <vector>

#include <iostream>
#include <random>
#include "game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void snakeMovement();
void snakeTail();
void snakeEatsTreat();
extern void gameOverCheck(GLFWwindow* window,std::vector<glm::vec3> cubePositions);
extern int startGameMenue();
extern void endGameMenu(int points);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int points = 0;
int difficulty = 2;             //4 schwer, 2,mittel, 1 leicht
std::string choice = " ";
BOOLEAN snake_movement_flag = false;
short snake_movement_direction=1; //0 rechts, 1 hoch, 2 links, 3 runter
glm::vec3 tempFirst;


        std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f,  2.0f, 0.0f),
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  0.0f,  0.0f),
        glm::vec3( 4.0f,  0.0f,  0.0f),
        glm::vec3( 6.0f,  0.0f,  0.0f),
        glm::vec3( 8.0f,  0.0f,  0.0f),
        glm::vec3( 10.0f,  0.0f,  0.0f),
        glm::vec3( 12.0f,  0.0f,  0.0f),
        glm::vec3( 14.0f,  0.0f,  0.0f),
        glm::vec3( 16.0f,  0.0f,  0.0f),
        glm::vec3( 18.0f,  0.0f,  0.0f)
    };

int main()
{

    difficulty=startGameMenue();


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Snake v.1.2", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("coordinate_systems.vs", "coordinate_systems.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    int counter=0;
    float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("textures/dirt.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

         // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //activate shader
        ourShader.use();
        if(counter%(20/difficulty) == 0)
        {
            snakeMovement();
        }

        // create transformations
        glm::mat4 view;
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(1400.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 2000.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -80.0f));
        // pass transformation matrices to the shader
        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 1; i < cubePositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model,(float)counter, glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

            glm::mat4 model;
            model = glm::translate(model, cubePositions[0]);
            model = glm::rotate(model,(float)counter, glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
        counter++;
       snakeEatsTreat();
       gameOverCheck(window, cubePositions);

        std::this_thread::sleep_for (std::chrono::milliseconds(5));
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
        glfwTerminate();

        ////////////////////////////////////////MENU//////////////////

    endGameMenu(points);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
        glfwSetWindowShouldClose(window, true);
        }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        //cubePositions[1][2]=cubePositions[1][2]-0.1;
        snake_movement_direction=1;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        //cubePositions[1][2]=cubePositions[1][2]+0.1;
        snake_movement_direction=3;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //cubePositions[1][0]=cubePositions[1][0]-0.5;
        snake_movement_direction=2;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
       // cubePositions[1][0]=cubePositions[1][0]+0.5;
        snake_movement_direction=0;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        snake_movement_flag = true;

    }
}

void snakeMovement()
{
    if(snake_movement_flag)
    {
        for(unsigned int i=cubePositions.size();i>1;i--)
        {
            cubePositions[i][0]=cubePositions[i-1][0];
            cubePositions[i][1]=cubePositions[i-1][1];
            cubePositions[i][2]=cubePositions[i-1][2];
        }
        switch(snake_movement_direction)
        {
            case 0 : cubePositions[1][0]=cubePositions[1][0]+1;
            break;
            case 1 : cubePositions[1][1]=cubePositions[1][1]+1;
            break;
            case 2 : cubePositions[1][0]=cubePositions[1][0]-1;
            break;
            case 3 : cubePositions[1][1]=cubePositions[1][1]-1;

        }
    }
}

void snakeEatsTreat(){

   // if(cubePositions[0][0]==cubePositions[1][0]&&cubePositions[0][1]==cubePositions[1][1]&&cubePositions[0][2]==cubePositions[1][2])
   if(cubePositions[0]==cubePositions[1])
    {
        cubePositions[0][0]=rand()%(23+23 + 1) -23;
        cubePositions[0][1]=rand()%(17+17 + 1) -17;
        cubePositions[0][2]=0.0f;

        cubePositions.push_back(glm::vec3(0.0f,40.0f,0.0f));
        points++;
    }
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

