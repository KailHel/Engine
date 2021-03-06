//
// Created by kail on 27.12.2020.
//

#include "ResourcesManager.h"

#include "../graphics/Shader.h"
#include "../graphics/Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../external_libraries//stbi/stb_image.h"
#include "Logger.h"

//################################################################################################################################
//---CallbackWindowProcedure
void defResizeWindowCallback(GLFWwindow *window, int W, int H) {
    ResourcesManager::WINDOW_W = W;
    ResourcesManager::WINDOW_H = H;
    glViewport(0, 0, W, H);
}

void defWindowKeyCallback(GLFWwindow *window, int key, int scan, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}






//################################################################################################################################
//---init static variables
//----------------------------------------------------------------------//


GLFWwindow *ResourcesManager::_MWindow = nullptr;


//---//


int       ResourcesManager::WINDOW_W = 800;
int       ResourcesManager::WINDOW_H = 600;
string    ResourcesManager::WINDOW_TITLE = "title";


//--//


ResourcesManager::_shMap ResourcesManager::_ShaderMap = _ShaderMapInit();
ResourcesManager::_stMap ResourcesManager::_TextureMap = _TextureMapInit();

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glFrontFace(GL_CCW);

    Logger::CGL("GLAD INIT");
    return true;
}
//---



void ResourcesManager::Destroy() {
    if (_MWindow) glfwDestroyWindow(_MWindow);

    freeAllShader();
    freeAllTexture();
    glfwTerminate();
    Logger::CGL("Res men Destroy");
}


//################################################################################################################################
//---SHADER---
SK::Render::Shader *
ResourcesManager::createShaderProgram(const string &VertexPath, const string &FragmentPath, const string &ShaderName) {
    Logger::LogData("Create Shader Vpath||FPath||Name = " + VertexPath + "||"  + FragmentPath + "||" + ShaderName);
    return _ShaderMap.emplace(ShaderName, new SK::Render::Shader(FileToString(VertexPath),
                                                                 FileToString(FragmentPath))).first->second;
}


SK::Render::Shader *ResourcesManager::getShaderByName(const string &ShaderName) {
    auto iter = _ShaderMap.find(ShaderName);
    if (iter == _ShaderMap.end()) {
        cout << "WARNING :: getShaderByName :: ShaderList does not contain  -- " << ShaderName << "\n";
        return nullptr;
    }
    return _ShaderMap.find(ShaderName)->second;
}


bool ResourcesManager::freeShaderByName(const string &ShaderName) {
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
//---TEXTURE---
SK::Render::Texture *ResourcesManager::createTexture(const string &ImagePath, const string &TextureName) {
    stbi_set_flip_vertically_on_load(false);
    int channel = 0;
    int width = 0;
    int height = 0;
    unsigned char *pixels = stbi_load(ImagePath.c_str(), &width, &height, &channel, 0);

    Logger::LogData("Create Texture Path||Name = " + ImagePath + "||"  + TextureName);
    if (!pixels) {
        cout << "ERROR :: load image - " << ImagePath;
    }


    return _TextureMap.emplace(TextureName, new SK::Render::Texture(width, height, pixels, channel, GL_NEAREST,
                                                                    GL_CLAMP_TO_EDGE)).first->second;
}


SK::Render::Texture *ResourcesManager::getTextureByName(const string &TextureName) {
    return _TextureMap.find(TextureName)->second;
}

bool ResourcesManager::freeTextureByName(const string &TextureName) {
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
//------------------------------------------------------------------------------------------------------------------------------------------------//