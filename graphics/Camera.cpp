#include "Camera.h"

SK::Render::Camera::Camera(const GLfloat x, const GLfloat y, const GLfloat w, const GLfloat h, const GLfloat zNear, const GLfloat zFar)
{
	_Matrix4 = ortho(x, w, y, h, zNear, zFar);
}

const mat4 SK::Render::Camera::getMatrix4() const
{
	return _Matrix4;
}

void SK::Render::Camera::Move(const vec3& vecMove)
{
	_Matrix4 = translate(_Matrix4, vecMove);
}
void SK::Render::Camera::Rotate(const GLfloat grad)
{
	_Matrix4 = rotate(_Matrix4, radians(grad), vec3(0.f, 0.f, 1.f));
}
