#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 ambientLightColor;
uniform vec4 lightColor;
uniform float ambientLightIntensity;
uniform vec3 lightDirection;
uniform vec4 objectColor;

out vec4 vertexColor;
out vec4 camPos;
out vec3 norm;

out vec4 computedLight;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	float lightIntensity = dot(lightDirection, aNormal);

	vec4 cameraPosition = view * vec4(0.f,0.f,0.f,1.f);
	

	computedLight = 
		(ambientLightColor * ambientLightIntensity) +		// Ambient light
		(lightColor * max(0.0f, lightIntensity));//	+		// Diffused light

	vertexColor = objectColor;

	vertexColor.w = 1.0f;

	norm = aNormal;
}