//
// Created by kail on 28.12.2020.
//

#ifndef OPENGL_GAME_H
#define OPENGL_GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../graphics/Mesh.h"

#include "../support/ResourcesManager.h"
#include "ILoop.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/Sprite.h"
#include "../graphics/Camera.h"
#include "Events.h"
#include "../graphics/Camera.h"

using std::string;
using std::cout;
using std::cerr;

class Game : public SK::GAME::IFpsController  {
public:


    void Init()    override;
    void Update()  override;
    void Render()  override;
    void Dispose() override;

};


#endif //OPENGL_GAME_H
