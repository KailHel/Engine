//
// Created by kail on 30.12.2020.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <glad/glad.h>
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

namespace SK {
    namespace Render {
        class Camera {
        public:
            //--------------------------------------------------------------------------------------------------------------------------------------------------------
            Camera(const GLfloat x = 0, const GLfloat y = 0, const GLfloat w = 800, const GLfloat h = 600, const GLfloat zNear = -100.f, const GLfloat zFar = 100.f);
            ~Camera() = default;

            //--------------------------------------------------------------------------------------------------------------------------------------------------------
            const mat4 getMatrix4() const;
            void Move(const vec3& vecMove);
            void Rotate(const GLfloat grad);
        private:
            //--------------------------------------------------------------------------------------------------------------------------------------------------------

            glm::mat4 _Matrix4 =  mat4(1.f);
        };
    }
}
#endif //OPENGL_CAMERA_H
