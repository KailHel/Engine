//
// Created by kail on 28.12.2020.
//




#include "Game.h"


void Game::Init()
{
    if (!ResourcesManager::InitGLFW()){ResourcesManager::Destroy();exit(404);}
    if (!ResourcesManager::InitGLAD()){ResourcesManager::Destroy();exit(404);}
    ResourcesManager::createShaderProgram(defaultVertexShaderPath, defaultFragmentShaderPath, defaultShaderName);
    ResourcesManager::createTexture("res/4.png","def");
    window = ResourcesManager::getWindow();
    glClearColor(1,1,0,0);


    s = new SK::Render::Sprite(defaultShaderName,"def",glm::vec2(400,300),glm::vec2(100, 100),0);

    //------------------------
    glm::mat4 view(1.f);
    glm::mat4 projection(1.f);

    SK::Render::Camera cam(0,0,800,600);

    projection = cam.getMatrix4();
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

    

    ResourcesManager::getShaderByName(defaultShaderName)->use();
    ResourcesManager::getShaderByName(defaultShaderName)->setMatrix4("view",view);
    ResourcesManager::getShaderByName(defaultShaderName)->setMatrix4("projection",projection);




    



    //------------------------
}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);


    static GLfloat time = 0.f;
    time += 0.001f;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);


    ResourcesManager::getShaderByName(defaultShaderName)->setFloat1("time",time);
    ResourcesManager::getShaderByName(defaultShaderName)->setFloat2("resolution",ResourcesManager::WINDOW_W,ResourcesManager::WINDOW_H);
    ResourcesManager::getShaderByName(defaultShaderName)->setFloat2("mouse",xpos / 230,ypos / 230);


    s->render();

    


    glfwSwapBuffers(window);
}


void Game::Update()
{
    glfwPollEvents();
}


void Game::Dispose()
{

}
