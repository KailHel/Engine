//
// Created by kail on 28.12.2020.
//

#ifndef OPENGL_GAME_H
#define OPENGL_GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include "../support/ResourcesManager.h"
#include "ILoop.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/Sprite.h"

using std::string;
using std::cout;
using std::cerr;

class Game : public SK::GAME::IFpsController  {
public:

    const string defaultVertexShaderPath        =       "res/vertex.glsl";
    const string defaultFragmentShaderPath      =       "res/fragment.glsl";
    const string defaultShaderName              =       "DEF";

    GLFWwindow* window;

    //test
    SK::Render::Sprite* sprite;

    void Init()    override;
    void Update()  override;
    void Render()  override;
    void Dispose() override;


    SK::Render::Sprite* s;


};


#endif //OPENGL_GAME_H
