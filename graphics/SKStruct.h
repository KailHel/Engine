#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>



namespace SK {
	namespace Renderer {

		//---LoadPixel
		struct SKSurface {
			GLenum								Type;
		    GLuint								channel;
		    unsigned char*						data;

			GLuint								width;
			GLuint								height;
			
			GLenum filter				=		GL_LINEAR;
			GLenum wrapMode				=		GL_CLAMP_TO_EDGE;

			GLenum dataType				=		GL_UNSIGNED_BYTE;

			~SKSurface() { delete data; }
		};
		//--------------
		//---Compile texture
		struct SKTexture2D {
			GLenum							    ID;
			GLenum	 ShaderLayer		=		GL_TEXTURE0;

			GLuint								width;
			GLuint								height;
			GLenum								FormatType;

			~SKTexture2D() { glDeleteTextures(1, &ID); }
		};
		//--------------
		//---Shaders----
		struct SKShader {
			GLuin		ID;
			GLboolean   isCompile		=		false;

			~SKShader(){ glDeleteProgram(ID) }
		};
		//--------------
		//---Draw Texture
		struct SKSprite2D {
		private:
			static GLfloat vertices[] = {
					// �������           // ���������� ����������
					 1.f,  1.0f, 0.0f,    1.0f, 1.0f,   // ������� ������
					 1.f, -1.f, 0.0f,     1.0f, 0.0f,   // ������ ������
					-1.f, -1.f, 0.0f,    0.0f, 0.0f,   // ������ �����
					-1.f,  1.f, 0.0f,    0.0f, 1.0f    // ������� �����
			};
			static GLuint indices[] = {  // ������� ���������
					0, 1, 3,  // 1 ��
					1, 2, 3   // 2 ��
			};
		public:
			GLuint VaoID;
			SKTexture2D*	texture;
			SKShader*		shader;


			mat4 Matrix4				=		mat4(1.f);

			~SKSprite2D() { glDeleteVertexArrays( 1 , &VaoID); }
		};
	}
}
