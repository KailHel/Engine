//
// Created by kail on 27.12.2020.
//

#ifndef OPENGL_RESOURCESMANAGER_H
#define OPENGL_RESOURCESMANAGER_H


#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include <fstream>
#include <sstream>
#include "string"
#include "iostream"
#include "map"
#include "memory"




using std::string;
using std::cout;
using std::cerr;

namespace SK {
    namespace Render {
        class Shader;

        class Texture;
    }
}








class ResourcesManager {
public:
    ResourcesManager() = delete;
    ~ResourcesManager() = default;
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;
    ResourcesManager& operator=(ResourcesManager&&) = delete;








    //################################################################################################################################
    //---INIT---
    static bool InitGLFW();
    static bool InitGLAD();
    static void Destroy();



    //################################################################################################################################
    //---WINDOW---
    static GLFWwindow *             _MWindow;
    static int                      WINDOW_W;
    static int                      WINDOW_H;
    static string                   WINDOW_TITLE;

    static GLFWwindow *getWindow() {
        return _MWindow;
    }
    //################################################################################################################################
    //---SUPPORT---
    static string FileToString(const string &path) {
        std::ifstream f;
        f.open(path.c_str() ,std::ios::in | std::ios::binary);
        if (!f.is_open()){
            cout << "WARNING :file not found - " << path << "\n";
        }
        std::stringstream s;
        s << f.rdbuf();
        if (s.str().empty()){
            cout << "WARNING :the file is empty - " << path << "\n";
        }
        return s.str();
    }


private:
    static string _defaultPath;
public:
    static void setDefaultPath(const string& Path) {
        size_t found = Path.find_last_of("/\\");
        _defaultPath = Path.substr(0, found);
    }

    //################################################################################################################################
    //---------SHADER---------
private:
    typedef std::map<const string ,SK::Render::Shader*>_shMap;
    static _shMap _ShaderMapInit(){_shMap s; return s;}
    static _shMap _ShaderMap;
public:
    static SK::Render::Shader* createShaderProgram  (const string& VertexShaderPath ,const string& FragmentShaderPath ,const string& ShaderName);
    static SK::Render::Shader* getShaderByName      (const string& ShaderName);
    static bool                freeShaderByName     (const string& ShaderName);
    static void                freeAllShader        ();


    //################################################################################################################################
    //---------TEXTURE---------
private:
    typedef std::map<const string ,SK::Render::Texture*>_stMap;
    static _stMap _TextureMapInit(){_stMap s; return s;}
    static _stMap _TextureMap;
public:
    static SK::Render::Texture* createTexture       (const string& ImagePath ,const string& TextureName);
    static SK::Render::Texture* getTextureByName    (const string& TextureName);
    static bool             freeTextureByName       (const string& TextureName);
    static void             freeAllTexture          ();

};

#endif //OPENGL_RESOURCESMANAGER_H
