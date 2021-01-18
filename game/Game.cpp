//
// Created by kail on 28.12.2020.
//




#include "Game.h"
#include "../graphics/Render.h"


typedef ResourcesManager _R;
Camera *camera;
SK::Render::Sprite *sprite;
SK::Render::Shader *defShader;
GLFWwindow *window;

Mesh *mesh[1000];


bool stopTime = false;

void Game::Init() {
    if (!ResourcesManager::InitGLFW()) {
        ResourcesManager::Destroy();
        exit(404);
    }
    if (!ResourcesManager::InitGLAD()) {
        ResourcesManager::Destroy();
        exit(404);
    }
    Events::initialize();
    window = _R::getWindow();

    defShader =
            _R::createShaderProgram("res/shader/vertex.glsl", "res/shader/fragment.glsl", "def");
    _R::createTexture("res/texture/4.png", "1");
    _R::createTexture("res/texture/44.png", "2");
    sprite = new SK::Render::Sprite("def", "2", vec3(2, 0, 0), vec2(1000, 1000));
    camera = new Camera(vec3(0, 0, 0), 90);

    glClearColor(0.22f, 0.3f, 0.3f, 1);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
}

void Game::Render() {
    static float time = 1;
    if (!stopTime)  time += 0.05f;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    defShader->use();
    defShader->setUniformMatrix4("projection", camera->getProjection());
    defShader->setUniformMatrix4("view", camera->getView());
    defShader->setUniformMatrix4("model",mat4(1.f));
    defShader->setUniform1f("time",time);
    double x,y;
    glfwGetCursorPos(window,&x,&y);
    defShader->setUniform2f("mouse" ,x,y);
    defShader->setUniform2f("resolution" ,_R::WINDOW_W,_R::WINDOW_H);


//    for (int i = 0; i < 50; ++i) {
//        for (int j = 0; j < 50; ++j) {
//            sprite->Draw();
//            srand((time*10) / cos(i) * cos(j) + 3.4f / sin(time));
//            sprite->_position = vec3(i*20 + sin(time) * 20, j*20 + rand() % 100, sin(rand() % 60) * cos(time) * 1000);
//            sprite->_rotation = vec3(cos(time) * sin(rand()),cos(time) * 1000,tan(time) * 100);
//            sprite->_angle = sin(time) * 10000;
//        }
//    }
    //sprite->Draw();

    glfwSwapBuffers(window);
}

void Game::Update() {
    //------------------------------------------------------------------------------------------------------------------
    //---camera---
    static float camX = 0.0f;
    static float camY = 0.0f;
    static float speed = 0.0000001f;

    Events::pullEvents();
    if (Events::pressed(GLFW_KEY_W)) {
        camera->position += camera->front * speed * (float) (getDelta());
    }
    if (Events::pressed(GLFW_KEY_S)) {
        camera->position -= camera->front * speed * (float) (getDelta());
    }
    if (Events::pressed(GLFW_KEY_D)) {
        camera->position += camera->right * speed * (float) (getDelta());
    }
    if (Events::pressed(GLFW_KEY_A)) {
        camera->position -= camera->right * speed * (float) (getDelta());
    }
    if (Events::pressed(GLFW_KEY_SPACE)) {
        camera->position += camera->up * speed * (float) (getDelta());
    }
    if (Events::pressed(GLFW_KEY_LEFT_CONTROL)) {
        camera->position -= camera->up * speed * (float) (getDelta());
    }
    if (Events::clicked(GLFW_MOUSE_BUTTON_1)) Events::_cursor_locked = true;
    else Events::_cursor_locked = false;


    if (Events::_cursor_locked) {
        camY += -Events::deltaY / 600 * 2;
        camX += -Events::deltaX / 600 * 2;

        if (camY < -glm::radians(89.0f)) {
            camY = -glm::radians(89.0f);
        }
        if (camY > radians(89.0f)) {
            camY = radians(89.0f);
        }

        camera->rotation = mat4(1.0f);
        camera->rotate(camY, camX, 0);
    }
    //------------------------------------------------------------------------------------------------------------------
    //---Exit---
    if (Events::pressed(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(ResourcesManager::getWindow()))
        isRunning = false;
    //------------------------------------------------------------------------------------------------------------------

    if (Events::pressed(GLFW_KEY_R)) {
        stopTime = true;
    } else {
        stopTime = false;
    }
    if (Events::pressed(GLFW_KEY_LEFT_SHIFT)) {
        float speed = 0.00005f;
    } else {
        float speed = 0.0000001f;
    }
}


void Game::Dispose() {

}
