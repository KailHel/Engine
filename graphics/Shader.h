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
#include "../support/Logger.h"

#include "unordered_map"
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
                        string mes = "|Error ::Compile Vertex Shader|";
                        mes + message + "|";
                        Logger::LogData(mes);
                        _isCompile = false;
                        return;
                    }
                }//---
                Logger::CGL("Create vShader");
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
                        string mes = "|Error ::Compile Fragment Shader |";
                        mes + message + "|";
                        Logger::LogData(mes);
                        _isCompile = false;
                        return;
                    }
                }//---
                Logger::CGL("Create fShader");
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
                    string mes = "|Error ::Compile Shader Program|";
                    mes + message + "|";
                    Logger::LogData(mes);
                    _isCompile = false;
                    return;
                }
                Logger::CGL("Create ShaderProgram");
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
            void setUniform1i(const string &UniformName, const GLint value1);

            void setUniform21(const string &UniformName, const GLint value1, const GLint value2);

            void setUniform3i(const string &UniformName, const GLint value1, const GLint value2, const GLint value3);

            void setUniform1f(const string &UniformName, const GLfloat value1);

            void setUniform2f(const string &UniformName, const GLfloat value1, const GLfloat value2);

            void setUniform3f(const string &UniformName, const GLfloat value1, const GLfloat value2, const GLfloat value3);

            void setUniform2f(const string &UniformName, glm::vec2 &value);

            void setUniform3f(const string &UniformName, glm::vec3 &value);

            void setUniformMatrix4(const string &UniformName, const glm::mat4 &value);

            const GLuint getUniformLocation(const string &UniformName);


            //################################################################################################################################
            const GLuint getLocation() { return ID; }
            //################################################################################################################################
        private:
            GLuint ID;
            bool _isCompile = false;

            std::unordered_map<string , GLuint> _UniformMap;
        public:
            ~Shader() { glDeleteProgram(ID); }

            Shader() = delete;

            Shader(const ResourcesManager &) = delete;

            Shader &operator=(const Shader &) = delete;

            Shader &operator=(Shader &&) = delete;
        };
    }
}
#endif //OPENGL_SHADER_H
