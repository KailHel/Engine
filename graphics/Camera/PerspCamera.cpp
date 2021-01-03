#include "PerspCamera.h"

SK::Renderer::SKPerspCamera::SKPerspCamera(const GLfloat w, const GLfloat h, const GLfloat zNear, const GLfloat zFar)
{
	_Matrix4 = glm::perspective(45.0f, (float)w / (float)h, zNear, zFar);
}

const mat4 SK::Renderer::SKPerspCamera::getMatrix4() const
{
	return _Matrix4;
}
void SK::Renderer::SKPerspCamera::Move(const vec3& vecMove)
{
	_Matrix4 = translate(_Matrix4, vecMove);
}
void SK::Renderer::SKPerspCamera::Rotate(const GLfloat grad)
{
	_Matrix4 = rotate(_Matrix4, radians(grad), vec3(0.f, 0.f, 1.f));
}
