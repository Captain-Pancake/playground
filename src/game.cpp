#include "game.h"

game::game()
{
    //ctor
}

game::~game()
{
    //dtor
}



void gameOverCheck(GLFWwindow* window,std::vector<glm::vec3> cubePositions){

if(cubePositions[1][0]>23||cubePositions[1][0]<-23||cubePositions[1][1]>17||cubePositions[1][1]<-17)
{
    glfwSetWindowShouldClose(window, true);
}

    for(unsigned int i=cubePositions.size();i>2;i--)
    {
        if(cubePositions[1]==cubePositions[i])
        {
          glfwSetWindowShouldClose(window, true);
        }
    }
}
