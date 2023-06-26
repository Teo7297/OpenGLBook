#pragma once
#include <Shader.h>

class Texture;

class Material
{
public:
	Material(const Shader& shader, const Texture** textures, int texturesCount, const Color& baseColor, int diffuseMapIndex, int specularMapIndex, float shininess);
	virtual ~Material() = default;
	void Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos);

private:

	const Shader& m_Shader;
	const Texture** m_Textures;
	int m_TexturesCount;
	const Color& m_baseColor;
	int m_DiffuseMapIndex;
	int m_SpecularMapIndex;
	float m_Shininess;

	/**
	 * \brief Extend Material and define this function to set specific extra uniforms a part from material properties and color
	 */
	virtual void SetUniforms(){};
};
