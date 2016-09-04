//强制要求支持一个特定版本的GLSL版本
#version 130

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

void main()
{
Color =VertexColor;
gl_Position = vec4(VertexPosition,1.0);
}  