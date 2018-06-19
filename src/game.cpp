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

int startGameMenue(){

    int difficulty = 2;
    std::string choice = " ";


    std::cout<<"Willkommen bei Snake v.1.2"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Um das Spiel zu starten tippe >start<."<<std::endl;
    std::cout<<"Die Schwierigkeit kann mit >leicht<,>mittel< und >schwer< eingegeben werden."<<std::endl;

    std::cout<<"Um die Optionen erneut auszugeben tippe >hilfe< ein."<<std::endl;

    while(choice!="start")
    {
        std::cin >> choice;
        if(choice=="leicht")
        {
            difficulty=1;
            std::cout<<"Schwierigkeit auf LEICHT gesetzt"<<std::endl;
        }
        else if(choice=="mittel")
        {
            difficulty=2;
            std::cout<<"Schwierigkeit auf MITTEL gesetzt"<<std::endl;
        }
        else if(choice=="schwer")
        {
            difficulty=4;
            std::cout<<"Schwierigkeit auf SCHWER gesetzt"<<std::endl;
        }
        else if(choice=="hilfe")
        {
            std::cout<<"Um das Spiel zu starten tippe >start<."<<std::endl;
            std::cout<<"Die Schwierigkeit kann mit >leicht<,>mittel< und >schwer< eingegeben werden."<<std::endl;
        }
        else if(choice=="start")
        {
            std::cout<<"Viel Spass!"<<std::endl;
        }
        else{
            std::cout<<"Keine Gueltige Eingabe"<<std::endl;
        }
    }

    return difficulty;
}

void endGameMenu(int points)
{

    std::string choice = "  ";
    std::cout<<"Gratuliere du hast: "<<points<<" Punkte gesammelt!"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Um das neu zu starten tippe >start<."<<std::endl;
    std::cout<<"Um das Spiel zu beenden tippe >exit<"<<std::endl;

    std::cout<<"Um die Optionen erneut auszugeben tippe >hilfe< ein."<<std::endl;

    while(choice!="exit")
    {
        std::cin >> choice;
        if(choice=="start")
        {

            std::cout<<"NOCH NICHT IMPLEMENTIERT"<<std::endl;
        }

        else if(choice=="hilfe")
        {
            std::cout<<"Um das neu zu starten tippe >start<."<<std::endl;
            std::cout<<"Um das Spiel zu beenden tippe >exit<"<<std::endl;

            std::cout<<"Um die Optionen erneut auszugeben tippe >hilfe< ein."<<std::endl;
        }
        else if(choice=="exit")
        {
            std::cout<<"Aufwiedersehen!"<<std::endl;
        }
        else{
            std::cout<<"Keine Gueltige Eingabe"<<std::endl;
        }
    }
}



