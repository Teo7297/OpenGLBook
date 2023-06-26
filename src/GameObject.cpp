#include <GameObject.h>

namespace gameobject
{
	GameObject::GameObject(glm::vec3 position, glm::quat rotation, VertexArray vao, ElementBuffer ebo, Material material)
		: m_Position(position), m_Rotation(rotation), m_VAO(vao), m_EBO(ebo), m_Material(material)
	{
		
	}



}
