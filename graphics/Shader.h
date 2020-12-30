//
// Created by kail on 27.12.2020.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <glad/glad.h>
#include <sstream>
#include "string"
#include "../support//ResourcesManager.h"
#include "ios"
#include "fstream"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

using std::string;
using std::cout;

namespace SK {
    namespace Render {
        class Shader {
        public:
            //################################################################################################################################
            Shader(const string &vertSorce, const string &fragSorce) {
                GLuint vertS = 0;
                vertS = glCreateShader(GL_VERTEX_SHADER);
                {
                    auto s = vertSorce.c_str();
                    glShaderSource(vertS, 1, &s, nullptr);
                }
                glCompileShader(vertS);
                {//---
                    GLint wtf = 0;
                    glGetShaderiv(vertS, GL_COMPILE_STATUS, &wtf);
                    if (wtf != GL_TRUE) {
                        GLsizei log_length = 0;
                        GLchar message[1024];
                        glGetShaderInfoLog(vertS, 1024, &log_length, message);
                        cout << "ERROR :: compile vertex shader - " << message << "\n";\
                    exit(3);
                    }
                }//---

                GLuint fragS = 0;
                fragS = glCreateShader(GL_FRAGMENT_SHADER);
                {
                    auto s = fragSorce.c_str();
                    glShaderSource(fragS, 1, &s, nullptr);
                }
                glCompileShader(fragS);
                {//---
                    GLint wtf = 0;
                    glGetShaderiv(fragS, GL_COMPILE_STATUS, &wtf);
                    if (wtf != GL_TRUE) {
                        GLsizei log_length = 0;
                        GLchar message[1024];
                        glGetShaderInfoLog(vertS, 1024, &log_length, message);
                        cout << "ERROR :: compile fragment shader - " << message << "\n";\
                    exit(3);
                    }
                }//---

                GLint ShaderProgram = 0;
                ShaderProgram = glCreateProgram();

                glAttachShader(ShaderProgram, vertS);
                glAttachShader(ShaderProgram, fragS);
                glLinkProgram(ShaderProgram);

                GLint program_linked;
                glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &program_linked);
                if (program_linked != GL_TRUE) {
                    GLsizei log_length = 0;
                    GLchar message[1024];
                    glGetProgramInfoLog(ShaderProgram, 1024, &log_length, message);
                    cout << "ERROR :: compile shader program- " << message << "\n";\
                exit(3);
                }

                glDeleteShader(vertS);
                glDeleteShader(fragS);

                ID = ShaderProgram;
                _isCompile = true;
            }
            //################################################################################################################################
            void use() const {
                glUseProgram(ID);
            }
            //################################################################################################################################
            void setInt(const string &UniformName, const GLint value) {
                glUniform1i(glGetUniformLocation(ID, UniformName.c_str()), value);
            }
            void setFloat1(const string &UniformName, const GLfloat value) {
                glUniform1f(glGetUniformLocation(ID, UniformName.c_str()), value);
            }
            void setFloat2(const string &UniformName, const GLfloat value1 ,const GLfloat value2) {
                glUniform2f(glGetUniformLocation(ID, UniformName.c_str()), value1,value2);
            }
            //################################################################################################################################
            void setMatrix4(const std::string &UniformName, const glm::mat4 matrix) {
                glUniformMatrix4fv(glGetUniformLocation(ID, UniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
            }
            //################################################################################################################################
            const GLuint getID(){return ID;}
            //################################################################################################################################
        private:
            GLuint ID;
            bool _isCompile = false;
        public:
            ~Shader() { glDeleteProgram(ID); }
        };
    }
}
#endif //OPENGL_SHADER_H
