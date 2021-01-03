//
// Created by kail on 30.12.2020.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <string>

#include <glad/glad.h>
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../SKStruct.h"
#include "../Camera/OrthoCamera.h"
#include "../Camera/PerspCamera.h"

#include "../../support/ResourcesManager.h"
#include "../../support/glError.h"
using namespace glm;

namespace SK {
	namespace Renderer {
		class Render {
		public:
			Render(const string& SpriteShaderName) {
				_DEFAULT_SPRITE_SHADER = ResourcesManager::getShaderByName(SpriteShaderName);
				_DEFAULT_SPRITE_SHADER_M_MAT4_ID = glGetUniformLocation(_DEFAULT_SPRITE_SHADER->ID, "model");
				_DEFAULT_SPRITE_SHADER_V_MAT4_ID = glGetUniformLocation(_DEFAULT_SPRITE_SHADER->ID, "view");
				_DEFAULT_SPRITE_SHADER_P_MAT4_ID = glGetUniformLocation(_DEFAULT_SPRITE_SHADER->ID, "projection");
			}
			~Render() {
			}
			void Draw(SKSprite2D* sprite, const mat4& projectionMatrix, const mat4& viewMatrix) {
				glUseProgram(_DEFAULT_SPRITE_SHADER->ID);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, sprite->texture->ID);
				//-------

				glm::mat4 projection = ortho(0, 2, 0, 2, -1000, 1000);
				glm::mat4 model(1.f);
				glm::mat4 view(1.f);

				model = translate(model, vec3(2, 2, 0));

				glUniformMatrix4fv(_DEFAULT_SPRITE_SHADER_M_MAT4_ID, 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(_DEFAULT_SPRITE_SHADER_V_MAT4_ID, 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(_DEFAULT_SPRITE_SHADER_P_MAT4_ID, 1, GL_FALSE, glm::value_ptr(projection));
				//-------
				glBindVertexArray(sprite->VaoID);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);

				glBindTexture(GL_TEXTURE_2D, 0);
				glUseProgram(0);
			}
			void Begin() {}
			void End() {}
		private:
			SK::Renderer::SKShader* _DEFAULT_SPRITE_SHADER = nullptr;
			GLuint                              _DEFAULT_SPRITE_SHADER_P_MAT4_ID = 0;
			GLuint                              _DEFAULT_SPRITE_SHADER_V_MAT4_ID = 0;
			GLuint                              _DEFAULT_SPRITE_SHADER_M_MAT4_ID = 0;
		};
	}
}
#endif //OPENGL_CAMERA_H
