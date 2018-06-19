#ifndef GAME_H
#define GAME_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class game
{
    public:
        game();
        virtual ~game();
        void gameOverCheck(GLFWwindow* window,std::vector<glm::vec3> cubePositions);
        int startGameMenue();
        void endGameMenue(int points);


    protected:

    private:
};

#endif // GAME_H
