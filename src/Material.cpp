#include <Material.h>

#include "Texture.h"


Material::Material(const Shader& shader, const Texture** textures, int texturesCount, const Color& baseColor, int diffuseMapIndex, int specularMapIndex, float shininess=32.f)
		: m_Shader(shader), m_Textures(textures), m_TexturesCount(texturesCount), m_baseColor(baseColor), m_DiffuseMapIndex(diffuseMapIndex), m_SpecularMapIndex(specularMapIndex), m_Shininess(shininess)
{

}


void Material::Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos)
{
	// Activate and bind textures
	for (int i = 0; i < m_TexturesCount; ++i)
	{
		m_Textures[i]->Activate();
		m_Textures[i]->Bind();
	}

	// bind shader
	m_Shader.Bind();

	// set uniforms
	SetUniforms();
	
	// set material uniforms
	const int diffuseMapIndex = m_Textures[m_DiffuseMapIndex]->TEXTURE_NUMBER;
	const int specularMapIndex = m_Textures[m_SpecularMapIndex]->TEXTURE_NUMBER;
	m_Shader.SetUniform("material.diffuse", diffuseMapIndex);
	m_Shader.SetUniform("material.specular", specularMapIndex);
	m_Shader.SetUniform("material.shininess", m_Shininess);
	m_Shader.SetUniform("objectColor", m_baseColor);

	m_Shader.SetUniform("model", model);
	m_Shader.SetUniform("view", view);
	m_Shader.SetUniform("projection", projection);
	m_Shader.SetUniform("viewPos", cameraPos);


}


