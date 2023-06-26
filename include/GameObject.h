#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <VertexArray.h>
#include <ElementBuffer.h>
#include <Material.h>


class Shader;

namespace gameobject
{
	class GameObject
	{
	public:
		GameObject(glm::vec3 position, glm::quat rotation, VertexArray vao, ElementBuffer ebo, Material material);
		~GameObject() = default;

	private:
		glm::vec3 m_Position;
		glm::quat m_Rotation;
		VertexArray m_VAO;
		ElementBuffer m_EBO;
		Material m_Material;


	public:
		void Scale(const glm::vec3& scaleVector);
		void Rotate(float degrees, const glm::vec3& rotateVector);
		void SetRotation(const glm::quat& quaternion);
		void Translate(const glm::vec3& translateVector);
		void SetPosition(const glm::vec3& position);
		void SetShader(const Shader& shader); // 1 shader only for now TODO: pipeline

		glm::vec3& GetPosition();
		glm::quat& GetRotation();

		void Render(float deltaTime);
	};
}
