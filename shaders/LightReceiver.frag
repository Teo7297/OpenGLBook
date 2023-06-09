#version 330 core
in vec4 vertexColor;
in vec4 camPos;
in vec3 norm;
in vec4 computedLight;

uniform vec3 lightDirection;
uniform vec4 lightColor;

out vec4 FragColor;

void main()
{
	vec3 directionToCamera = normalize(vec3(gl_FragCoord - camPos));
	vec3 reflection = normalize(lightDirection - 2 * dot(lightDirection, norm) * norm);
	float reflection_intensity = dot(directionToCamera, reflection);

	vec4 compLight = computedLight + (lightColor * max(0.0f, reflection_intensity));


	FragColor = compLight * vertexColor;
	FragColor.w = 1.0f;
}