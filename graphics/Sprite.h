//
// Created by kail on 28.12.2020.
//

#ifndef OPENGL_SPRITE_H
#define OPENGL_SPRITE_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec2.hpp"


#include "memory"
#include "string"

#include "Texture.h"
#include "Shader.h"
#include "../support/Logger.h"

namespace SK {
    namespace Render {
        class Sprite {
        public:
            Sprite(const std::string &ShaderName, const std::string &TextureName,
                   const glm::vec3 &position,
                   const glm::vec2 &size) :
                    _position(position),
                    _size(size) {
                _shader = ResourcesManager::getShaderByName(ShaderName);
                _texture = ResourcesManager::getTextureByName(TextureName);
                _angle = 0;
                _rotation = glm::vec3(1, 1, 1);
                GLfloat vertices[] = {
                        // Позиции        // Текстурные координаты
                        1.f, 1.0f, 0.0f,    1.0f, 0.0f,   // Верхний правый
                        1.f, -1.f, 0.0f,    1.0f, 1.0f,   // Нижний правый
                        -1.f, -1.f, 0.0f,   0.0f, 1.0f,   // Нижний левый
                        -1.f, 1.f, 0.0f,    0.0f, 0.0f    // Верхний левый
                };
                GLuint indices[] = {  // Note that we start from 0!
                        0, 1, 3,  // First Triangle
                        1, 2, 3   // Second Triangle
                };
                GLuint VBO, VAO, EBO, VBO_TEXTURE;
                glGenVertexArrays(1, &VAO);
                //glGenBuffers(1,&VBO_COLOR);
                glGenBuffers(1, &VBO_TEXTURE);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                Logger::CGL("Sprite Create buffer");
                glBindVertexArray(VAO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
                glEnableVertexAttribArray(0);

                Logger::CGL("Create Sprite | Set VBO DATA");

                glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXTURE);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
                glEnableVertexAttribArray(1);

                Logger::CGL("Create Sprite | Set VBO TEXTURE DATA");

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                Logger::CGL("Create Sprite | Set EBO DATA");

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                vao = VAO;
                vbo = VBO;
                ebo = EBO;


            }

            void Draw() {
                _shader->use();
                _texture->bind();

                glm::mat4 model(1.f);

                model = glm::translate(model, _position);
                model = glm::rotate(model, glm::radians(_angle), _rotation);
                model = glm::scale(model, glm::vec3(_size, 1.f));

                _shader->setUniformMatrix4("model", model);

                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
                Logger::CGL("render Sprite");
            }

        private:
            GLuint vao = 0;
            GLuint vbo = 0;
            GLuint ebo = 0;
            GLuint tex = 0;

            Shader *_shader;
            Texture *_texture;





        public:
            glm::vec3 _position;
            glm::vec3 _rotation;
            float _angle;
            glm::vec2 _size;

            ~Sprite() {
                glDeleteBuffers(1, &vao);
                glDeleteBuffers(1, &ebo);
                glDeleteBuffers(1, &vbo);
            }

            Sprite() = delete;

            Sprite(const Sprite &) = delete;

            Sprite &operator=(const Sprite &) = delete;

            Sprite &operator=(Sprite &&) = delete;
        };

    }
}
#endif //OPENGL_SPRITE_H
