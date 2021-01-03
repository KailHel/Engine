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
#include "../graphics/SKStruct.h"
#include  "../graphics/Render/Render.h"
#include  "../graphics/Camera/OrthoCamera.h"
#include  "../graphics/Camera/PerspCamera.h"

using std::string;
using std::cout;
using std::cerr;

namespace SK {
	namespace Renderer {
		class SKOrthoCamera;
	}
}

class Game : public SK::GAME::IFpsController {
public:

	const string defaultVertexShaderPath = "res/vertex.glsl";
	const string defaultFragmentShaderPath = "res/fragment.glsl";
	const string defaultShaderName = "DEF";

	GLFWwindow* window;
	SK::Renderer::Render* rend;
	SK::Renderer::SKOrthoCamera* camera;

	//test
	SK::Renderer::SKSprite2D* sprite;
	SK::Renderer::SKShader* shader;

	void Init()    override;
	void Update()  override;
	void Render()  override;
	void Dispose() override;

	SK::Render::Sprite* s;
};

#endif //OPENGL_GAME_H