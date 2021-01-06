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
#include "../graphics/Camera.h"
#include "Events.h"
#include "../graphics/Camera.h"

using std::string;
using std::cout;
using std::cerr;

class Game : public SK::GAME::IFpsController  {
public:

    class Mesh{
        public:
        SK::Render::Sprite* _cell;
        glm::vec3 _pos;

        Mesh(SK::Render::Sprite* cell ,const vec3& pos){
            _cell = cell;
            _pos = pos;
        }
        void Draw(){
            if (_cell != nullptr ) {
                _cell->_angle = 0;
                _cell->_position = vec3(_pos.x, _pos.y, _pos.z + 1);
                _cell->render();
                _cell->_position = vec3(_pos.x, _pos.y, _pos.z - 1);
                _cell->render();
                _cell->_angle = 90;
                _cell->_position = vec3(_pos.x + 1, _pos.y, _pos.z);
                _cell->_rotation = vec3(0, 1, 0);
                _cell->render();
                _cell->_position = vec3(_pos.x - 1, _pos.y, _pos.z);
                _cell->_rotation = vec3(0, 1, 0);
                _cell->render();

                _cell->_position = vec3(_pos.x, _pos.y + 1, _pos.z);
                _cell->_rotation = vec3(1, 0, 0);
                _cell->render();
                _cell->_position = vec3(_pos.x, _pos.y - 1, _pos.z);
                _cell->_rotation = vec3(1, 0, 0);
                _cell->render();
            }
        }
    };

    Mesh* mesh[90][90];
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

    SK::Render::Sprite* sp;

    Camera* cam;

};


#endif //OPENGL_GAME_H
