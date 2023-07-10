#pragma once

#include <vector>


class GameObject;



	
class Scene
{
public:
	~Scene() = default;

	static Scene& GetInstance();
	void addGameObject(GameObject& gameobject);
	void addLight(GameObject& light);

	std::vector<GameObject> m_GameObjects;
	std::vector<GameObject> m_Lights;

private:
	Scene();
};

