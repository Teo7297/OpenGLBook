#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec4 vertexPosition;
out vec2 TexCoord;
uniform float positionOffset;
uniform mat4 trans;
void main()
{
 //gl_Position = vec4(-(aPos.x + positionOffset), -aPos.y, -aPos.z, 1.0f);
 gl_Position = trans * vec4(aPos, 1.0f);
 vertexColor = vec4(aCol, 1.0f);
 vertexPosition = gl_Position;
 TexCoord = aTexCoord;
}