//
// Created by kail on 27.12.2020.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "glad/glad.h"
#include "string"
#include "../external_libraries/stbi//stb_image.h"

#include "../support//ResourcesManager.h"
#include "../support/Logger.h"
namespace SK {
    namespace Render {
        class Texture {
        public:
            //################################################################################################################################
            Texture(const GLuint width, const GLuint height,
                    unsigned char *data,
                    const unsigned int channel = 4,
                    const GLenum filter = GL_LINEAR,
                    const GLenum wrapMode = GL_CLAMP_TO_EDGE) : _width(width), _height(height) {
                GLenum mode = GL_RGB;
                switch (channel) {
                    case 4:
                        mode = GL_RGBA;
                        break;
                    case 3:
                        mode = GL_RGB;
                        break;
                    default:
                        mode = GL_RGBA;
                        break;
                }
                glGenTextures(1, &ID);
                glBindTexture(GL_TEXTURE_2D, ID);
                glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
                Logger::CGL("Texture set data");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
                glGenerateMipmap(GL_TEXTURE_2D);
                Logger::CGL("Texture error");
                glBindTexture(GL_TEXTURE_2D, 0);
                stbi_image_free(data);
            }
            //################################################################################################################################
            void bind() const {
                glBindTexture(GL_TEXTURE_2D, ID);
            }

        private:
            GLuint ID;
            unsigned int _width = 0;
            unsigned int _height = 0;
        public:
            ~Texture() {
                glDeleteTextures(1, &ID);
            }
            Texture() = delete;
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture& operator=(Texture&&) = delete;
        };
    }
}
#endif //OPENGL_TEXTURE_H
