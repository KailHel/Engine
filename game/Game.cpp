//
// Created by kail on 28.12.2020.
//

#include "Game.h"
#include "../graphics/Camera/OrthoCamera.h"

void Game::Init()
{
	if (!ResourcesManager::InitGLFW()) { ResourcesManager::Destroy(); exit(404); }
	if (!ResourcesManager::InitGLAD()) { ResourcesManager::Destroy(); exit(404); }
	window = ResourcesManager::getWindow();
	glClearColor(1, 1, 0, 0);

	shader = ResourcesManager::createShaderProgram(defaultVertexShaderPath, defaultFragmentShaderPath, defaultShaderName);
	SK::Renderer::SKSurface* surface = ResourcesManager::createSurface("res/4.png", "DEF");
	SK::Renderer::SKTexture2D* texture = ResourcesManager::createTexture("DEF", "DEF");
	sprite = ResourcesManager::createSprite2D("DEF", "DEF");

	rend = new SK::Renderer::Render(defaultShaderName);

	camera = new SK::Renderer::SKOrthoCamera();
	//------------------------

	sprite->position.x = 0;
	sprite->position.y = 0;

	sprite->size = vec2(10.f, 10.f);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	rend->Draw(sprite, glm::mat4(1), glm::mat4(1));

	glfwSwapBuffers(window);
}

void Game::Update()
{
	glfwPollEvents();
}

void Game::Dispose()
{
}