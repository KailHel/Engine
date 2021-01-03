//
// Created by kail on 27.12.2020.
//

#include "ResourcesManager.h"

#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/SKStruct.h"

#include "../support/glError.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external_libraries//stbi/stb_image.h"

//################################################################################################################################
//---CallbackWindowProcedure
void defResizeWindowCallback(GLFWwindow* window, int W, int H)
{
	ResourcesManager::WINDOW_W = W;
	ResourcesManager::WINDOW_H = H;
	glViewport(0, 0, W, H);
}
void defWindowKeyCallback(GLFWwindow* window, int key, int scan, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

//################################################################################################################################
//---init static variables
		//----------------------------------------------------------------------//

GLFWwindow* ResourcesManager::_MWindow = nullptr;

//---//

int       ResourcesManager::WINDOW_W = 800;
int       ResourcesManager::WINDOW_H = 600;
string    ResourcesManager::WINDOW_TITLE = "title";

//--//

ResourcesManager::_shMap ResourcesManager::_ShaderMap = _ShaderMapInit();
ResourcesManager::_stMap ResourcesManager::_TextureMap = _TextureMapInit();
ResourcesManager::_sfMap ResourcesManager::_SurfaceMap = _SurfaceMapInit();
ResourcesManager::_spMap ResourcesManager::_Sprite2DMap = _Sprite2DMapInit();

string ResourcesManager::_defaultPath = "";

//----------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------//
//################################################################################################################################
bool ResourcesManager::InitGLFW() {
	if (!glfwInit()) {
		cerr << " ERROR : glfw init \n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, 1);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

	_MWindow = glfwCreateWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE.c_str(), nullptr, nullptr);
	if (!_MWindow) {
		cerr << " ERROR : glfwWindow init \n";
		return false;
	}

	glfwMakeContextCurrent(_MWindow);
	glfwSetWindowSizeCallback(_MWindow, defResizeWindowCallback);
	glfwSetKeyCallback(_MWindow, defWindowKeyCallback);

	return true;
}
//---

bool ResourcesManager::InitGLAD() {
	if (!gladLoadGL()) {
		cerr << " ERROR : glad init \n";
		return false;
	}

	std::cout << "RENDERER   " << glGetString(GL_RENDERER) << "\n";
	std::cout << "VER OPENGL " << glGetString(GL_VERSION) << "\n";
	std::cout << "USE OpenGL " << GLVersion.major << "." << GLVersion.minor << "\n";

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}
//---

void ResourcesManager::Destroy() {
	if (_MWindow) glfwDestroyWindow(_MWindow);

	freeAllShader();
	freeAllTexture();

	glfwTerminate();
}

//################################################################################################################################
//---SHADER---
SK::Renderer::SKShader* ResourcesManager::createShaderProgram(const string& VertexShaderPath, const string& FragmentShaderPath, const string& ShaderName) {
	SK::Renderer::SKShader* shader = new SK::Renderer::SKShader();
	GLuint vertS = 0;
	vertS = glCreateShader(GL_VERTEX_SHADER);
	{
		auto s = FileToString(VertexShaderPath);
		auto c = s.c_str();
		glShaderSource(vertS, 1, &c, nullptr);
	}
	glCompileShader(vertS);
	{//---
		GLint wtf = 0;
		glGetShaderiv(vertS, GL_COMPILE_STATUS, &wtf);
		if (wtf != GL_TRUE) {
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(vertS, 1024, &log_length, message);
			cout << "ERROR :: compile vertex shader - " << message << "    \n : name = " << ShaderName << "\n"; \
				shader->isCompile = false;
			glDeleteShader(vertS);
			return shader;
		}
	}//---

	GLuint fragS = 0;
	fragS = glCreateShader(GL_FRAGMENT_SHADER);
	{
		auto s = FileToString(FragmentShaderPath);
		auto c = s.c_str();
		glShaderSource(fragS, 1, &c, nullptr);
	}
	glCompileShader(fragS);
	{//---
		GLint wtf = 0;
		glGetShaderiv(fragS, GL_COMPILE_STATUS, &wtf);
		if (wtf != GL_TRUE) {
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(vertS, 1024, &log_length, message);
			cout << "ERROR :: compile fragment shader - " << message << "    \n : name = " << ShaderName << "\n"; \
				shader->isCompile = false;
			glDeleteShader(vertS);
			glDeleteShader(fragS);
			return shader;
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
		cout << "ERROR :: compile shader program- " << message << "\n"; \
			shader->isCompile = false;
		glDeleteShader(vertS);
		glDeleteShader(fragS);
		return shader;
	}

	glDeleteShader(vertS);
	glDeleteShader(fragS);

	shader->ID = ShaderProgram;
	shader->isCompile = true;

	_ShaderMap.emplace(ShaderName, shader);
	return  shader;
}

SK::Renderer::SKShader* ResourcesManager::getShaderByName(const string& ShaderName) {
	auto iter = _ShaderMap.find(ShaderName);
	if (iter == _ShaderMap.end()) {
		cout << "WARNING :: getShaderByName :: ShaderList does not contain  -- " << ShaderName << "\n";
		return nullptr;
	}
	return _ShaderMap.find(ShaderName)->second;
}

bool ResourcesManager::freeShaderByName(const string& ShaderName) {
	auto iter = _ShaderMap.find(ShaderName);
	if (iter == _ShaderMap.end()) {
		cout << "WARNING :: freeShaderByName :: ShaderList does not contain  -- " << ShaderName << "\n";
		return false;
	}
	if (iter->second != nullptr) delete iter->second;
	_ShaderMap.erase(ShaderName);
	return true;
}

void ResourcesManager::freeAllShader() {
	for (auto iter : _ShaderMap) {
		if (iter.second != nullptr) delete iter.second;
	}
}
//################################################################################################################################
//---SURFACE---
SK::Renderer::SKSurface* ResourcesManager::createSurface(const string& ImagePath, const string& SurfaceName)
{
	stbi_set_flip_vertically_on_load(true);
	SK::Renderer::SKSurface* surface = new SK::Renderer::SKSurface;
	string path = _defaultPath + "\\" + ImagePath;
	int w, h, c = 0;
	surface->data = stbi_load(path.c_str(), &w, &h, &c, 0);
	surface->channel = c;
	surface->height = h;
	surface->width = w;

	switch (c)
	{
	case 3: surface->Type = GL_RGB; break;
	case 4: surface->Type = GL_RGBA; break;
	default:
		surface->Type = GL_RGBA;
		break;
	}

	if (surface->channel == 0 || surface->data == nullptr || surface->height <= 0 || surface->width <= 0 || !surface->data)
	{
		cout << "ERROR :: create surface - " << ImagePath << "  name = " << SurfaceName;
		surface->isCompile = false;
		return surface;
	}
	else {
		surface->isCompile = true;
		_SurfaceMap.emplace(SurfaceName, surface);
		return surface;
	}
}

SK::Renderer::SKSurface* ResourcesManager::getSurfaceByName(const string& SurfaceName)
{
	auto iter = _SurfaceMap.find(SurfaceName);
	if (iter == _SurfaceMap.end()) {
		cout << "WARNING :: getSurfaceByName :: SyrfaceList does not contain  -- " << SurfaceName << "\n";
		return nullptr;
	}
	return _SurfaceMap.find(SurfaceName)->second;
}

bool ResourcesManager::freeSurfaceByName(const string& SurfaceName)
{
	auto iter = _SurfaceMap.find(SurfaceName);
	if (iter == _SurfaceMap.end()) {
		cout << "WARNING :: freeSurfaceByName :: SurfaceList does not contain  -- " << SurfaceName << "\n";
		return false;
	}
	if (iter->second != nullptr) delete iter->second;
	_SurfaceMap.erase(SurfaceName);
	return true;
}

void ResourcesManager::freeAllSurface()
{
	for (auto iter : _SurfaceMap) {
		if (iter.second != nullptr) delete iter.second;
		_SurfaceMap.erase(iter.first);
	}
}

//################################################################################################################################
//---TEXTURE---
SK::Renderer::SKTexture2D* ResourcesManager::createTexture(const string& SurfaceName, const string& TextureName) {
	SK::Renderer::SKSurface* surface = getSurfaceByName(SurfaceName);
	SK::Renderer::SKTexture2D* texture = new SK::Renderer::SKTexture2D;

	glGenTextures(1, &texture->ID);
	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, surface->Type, surface->width, surface->height, 0, surface->Type, surface->dataType, surface->data);
	glError("ResMan create Texture", "glTexImage2D");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, surface->wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, surface->wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, surface->filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, surface->filter);

	glError("ResMan create Texture", "setParam");
	glBindTexture(GL_TEXTURE_2D, 0);

	texture->isCompile = true;
	texture->height = surface->height;
	texture->width = surface->width;
	texture->ShaderLayer = GL_TEXTURE0;
	texture->FormatType = surface->Type;

	_TextureMap.emplace(TextureName, texture);
	return texture;
}

SK::Renderer::SKTexture2D* ResourcesManager::getTextureByName(const string& TextureName) {
	auto iter = _TextureMap.find(TextureName);
	if (iter == _TextureMap.end()) {
		cout << "WARNING :: getTextureByName :: TextureList does not contain  -- " << TextureName << "\n";
		return nullptr;
	}
	return _TextureMap.find(TextureName)->second;
}

bool ResourcesManager::freeTextureByName(const string& TextureName) {
	auto iter = _TextureMap.find(TextureName);
	if (iter == _TextureMap.end()) {
		cout << "WARNING :: freeTextureByName :: TextureList does not contain  -- " << TextureName << "\n";
		return false;
	}

	if (iter->second != nullptr) {
		delete iter->second;
	}
	_TextureMap.erase(TextureName);
	return true;
}

void ResourcesManager::freeAllTexture() {
	for (auto iter : _TextureMap) {
		if (iter.second != nullptr) delete iter.second;
	}
}
//################################################################################################################################
//---SPRITE---
SK::Renderer::SKSprite2D* ResourcesManager::createSprite2D(const string& TextureName, const string& SpriteName)
{
	SK::Renderer::SKSprite2D* sprite = new SK::Renderer::SKSprite2D;
	GLfloat vertices[] = {
		// Позиции          // Цвета             // Текстурные координаты
		1.f,  1.0f, 0.0f,    1.0f, 1.0f,   // Верхний правый
		1.f, -1.f, 0.0f,    1.0f, 0.0f,   // Нижний правый
		-1.f, -1.f, 0.0f,    0.0f, 0.0f,   // Нижний левый
		-1.f,  1.f, 0.0f,    0.0f, 1.0f    // Верхний левый
	};
	GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,  // First Triangle
			1, 2, 3   // Second Triangle
	};
	GLuint VBO, VAO, EBO, VBO_TEXTURE;
	glGenVertexArrays(1, &VAO);//

	glGenBuffers(1, &VBO_TEXTURE);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glError("ResMan create Sprite", "glBufferData 1");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glError("ResMan create Sprite", "glvertexAttribPointer 1");
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXTURE);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glError("ResMan create Sprite", "glBufferData 2");
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glError("ResMan create Sprite", "glvertexAttribPointer 2");
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glError("ResMan create Sprite", "glBufferData EBO 1");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	sprite->VaoID = VAO;
	sprite->texture = ResourcesManager::getTextureByName(TextureName);

	_Sprite2DMap.emplace(SpriteName, sprite);
	return sprite;
}
SK::Renderer::SKSprite2D* ResourcesManager::getSprite2DByName(const string& SpriteName)
{
	return nullptr;
}
bool ResourcesManager::freeSprite2DByName(const string& SpriteName)
{
	return false;
}
void ResourcesManager::freeAllSprite()
{
}
//------------------------------------------------------------------------------------------------------------------------------------------------//