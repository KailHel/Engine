#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

float zNear = 0.1;
float zFar  = 100.0;

float LinearizeDepth(float depth)
{
     // преобразуем обратно в NDC
     float z = depth * 2.0 - 1.0;
     return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
}

void main()
{
     //float depth = LinearizeDepth(gl_FragCoord.z) / zFar;
     color = texture(ourTexture, TexCoord);
}