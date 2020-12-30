###################################################################################################################################################
###################################################################################################################################################

                                                        cmake_minimum_required(VERSION 3.13)
                                                                project(OpenGL)


                                   add_executable(OpenGL main.cpp
                                           external_libraries/stbi/stb_image.h
                                           support/ResourcesManager.cpp support/ResourcesManager.h
                                           game/ILoop.h game/ILoop.cpp
                                           graphics/Shader.h
                                           graphics/Texture.h
                                           graphics/Sprite.h
                                           game/Game.cpp
                                           game/Game.h
                                           graphics/Camera.h)
#----------------------------------------------------------------GLFW COMPILE OPTION--------------------------------------------------------------#
                                            set(GLFW_BUILD_EXAMPLES OFF     CACHE BOOL      "" FORCE)
                                            set(GLFW_BUILD_TESTS    OFF     CACHE BOOL      "" FORCE)
                                            set(GLFW_BUILD_DOCS     ON     CACHE BOOL       "" FORCE)
                                            set(GLFW_INSTALL        OFF     CACHE BOOL      "" FORCE)
                                                #-----------------------------------------------#
                                                            add_subdirectory(external_libraries/glfw)
                                                    target_link_libraries(${PROJECT_NAME} glfw)
                                                #-----------------------------------------------#
                                                            add_subdirectory(external_libraries/glad)
                                                    target_link_libraries(${PROJECT_NAME} glad)
                                                #-----------------------------------------------#
                                                        include_directories(external_libraries/glm)
#-------------------------------------------------------------------------------------------------------------------------------------------------#
###################################################################################################################################################
###################################################################################################################################################
