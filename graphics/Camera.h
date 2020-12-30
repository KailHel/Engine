//
// Created by kail on 30.12.2020.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
    Camera();
    ~Camera();



    glm::mat4 ViewMatrix;
};


#endif //OPENGL_CAMERA_H
