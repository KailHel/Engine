#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>



namespace SK {
	namespace Renderer {

		//---LoadPixel
		struct SKSurface {
			GLenum								Type=GL_R;
		    GLuint								channel=0;
		    unsigned char*						data=nullptr;

			GLuint								width=0;
			GLuint								height=0;
			
			GLenum filter				=		GL_LINEAR;
			GLenum wrapMode				=		GL_CLAMP_TO_EDGE;

			GLenum dataType				=		GL_UNSIGNED_BYTE;

			~SKSurface() { delete data; }

			GLboolean isCompile			=		GL_FALSE;
		};
		//--------------
		//---Compile texture
		struct SKTexture2D {
			GLenum							    ID=0;
			GLenum	 ShaderLayer		=		GL_TEXTURE0;

			GLuint								width=0;
			GLuint								height=0;
			GLenum								FormatType=GL_R;

			~SKTexture2D() { glDeleteTextures(1, &ID); }

			GLboolean isCompile			=		GL_FALSE;
		};
		//--------------
		//---Shaders----
		struct SKShader {
			GLuint		ID=0;
			GLboolean   isCompile		=		GL_FALSE;

			~SKShader() { glDeleteProgram(ID); }
		};
		//--------------
		//---Draw Texture
		struct SKSprite2D {
			GLuint VaoID=0;
			SKTexture2D*	texture=nullptr;


			glm::mat4 Matrix4				= glm::mat4(1.f);
			glm::vec2   position			= glm::vec2(1.f);
			glm::vec2   size				= glm::vec2(1.f);
			float       rotation            = 0.f;
			~SKSprite2D() { glDeleteVertexArrays( 1 , &VaoID); }
		};
	}
}
