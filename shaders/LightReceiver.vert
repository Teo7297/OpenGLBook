#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;
uniform vec3 lightDirection;
uniform vec3 objectColor;
out vec4 vertexColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	float lightIntensity = dot(lightDirection, aNormal);

	vertexColor = vec4(ambientLightColor * (ambientLightIntensity + max(0.0f, lightIntensity)) * objectColor, 1.0f);
}