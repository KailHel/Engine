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
                                           graphics/Camera.h
                                           graphics/Camera.cpp)
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
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
###################################################################################################################################################
###################################################################################################################################################
