//
// Created by kail on 28.12.2020.
//




#include "Game.h"


void Game::Init()
{
    if (!ResourcesManager::InitGLFW()){ResourcesManager::Destroy();exit(404);}
    if (!ResourcesManager::InitGLAD()){ResourcesManager::Destroy();exit(404);}
    ResourcesManager::createShaderProgram(defaultVertexShaderPath, defaultFragmentShaderPath, defaultShaderName);
    ResourcesManager::createTexture("res/44.png","def");
    Events::initialize();

    window = ResourcesManager::getWindow();


//    s[1] = new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(0,0,-1),glm::vec2(1, 1));
//    s[2] = new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(1,0,0),glm::vec2(1, 1));
//    s[3] = new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(-1,0,0),glm::vec2(1, 1));
//    s[2]->_rotation = vec3(0 ,1 ,0);s[2]->_angle = 90;
//    s[3]->_rotation = vec3(0 ,1 ,0);s[3]->_angle = 90;
//    s[4] = new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(0,1,0),glm::vec2(1, 1));
//    s[5] = new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(0,-1,0),glm::vec2(1, 1));
//    s[4]->_rotation = vec3(1 ,0 ,0);s[4]->_angle = 90;
//    s[5]->_rotation = vec3(1 ,0 ,0);s[5]->_angle = 90;
    //------------------------

    cam = new Camera(vec3(0,0,-30) , 90.f);
    cam->position = glm::vec3(0,0,0);

    glClearColor(0.6f,1.f,0.65f,1);
    glEnable(GL_DEPTH_TEST);



    sp =  new SK::Render::Sprite(defaultShaderName,"def",glm::vec3(0,0,0),glm::vec2(1, 1));

    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <=10 ; ++j) {
            mesh[i][j] = new Mesh(sp,  vec3(i+(i*1),0,j+(j*1)));
        }
    }


    //------------------------
}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mat4 proj(1.f);

    //proj = glm::perspective(45.f , 800.f / 600.f , 0.1f ,100.f);
    //view = translate(view , vec3(0,0,-3));

    cam->rotate(0,0,0);


    ResourcesManager::getShaderByName("DEF")->setMatrix4("view",cam->getView());
    ResourcesManager::getShaderByName("DEF")->setMatrix4("projection",cam->getProjection());


//    s[0]->render();
//    s[1]->render();
//    s[2]->render();
//    s[3]->render();
//    s[4]->render();
//    s[5]->render();--leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no

    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <=10 ; ++j) {
            mesh[i][j]->Draw();
        }
    }

    glfwSwapBuffers(window);
}


void Game::Update()
{
    static float camX = 0.0f;
    static float camY = 0.0f;

    static float speed = 0.000000005f;

    Events::pullEvents();
    if (Events::pressed(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(ResourcesManager::getWindow()))
        isRunning = false;
    if (Events::pressed(GLFW_KEY_W)){
        cam->position += cam->front  * speed * (float)(getDelta());
    }
    if (Events::pressed(GLFW_KEY_S)){
        cam->position -= cam->front * speed * (float)(getDelta());
    }
    if (Events::pressed(GLFW_KEY_D)){
        cam->position += cam->right * speed * (float)(getDelta());
    }
    if (Events::pressed(GLFW_KEY_A)){
        cam->position -= cam->right * speed *  (float)(getDelta());
    }
    if (Events::pressed(GLFW_KEY_SPACE)){
        cam->position +=cam->up * speed * (float)(getDelta());
    }
    if (Events::pressed(GLFW_KEY_LEFT_CONTROL)){
        cam->position -= cam->up * speed * (float)(getDelta());
    }
    if (Events::clicked(GLFW_MOUSE_BUTTON_1)) Events::_cursor_locked = true;
    else Events::_cursor_locked = false;


    if (Events::_cursor_locked){
        camY += -Events::deltaY / 600 * 2;
        camX += -Events::deltaX / 600 * 2;

        if (camY < -glm::radians(89.0f)){
            camY = -glm::radians(89.0f);
        }
        if (camY > radians(89.0f)){
            camY = radians(89.0f);
        }

        cam->rotation = mat4(1.0f);
        cam->rotate(camY, camX, 0);
    }
}


void Game::Dispose()фф
{
    delete(cam);
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <=10 ; ++j) {
            delete mesh[i][j];
        }
    }
    delete(sp);
}
