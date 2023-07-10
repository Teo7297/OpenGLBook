#include <Scene.h>
#include <GameObject.h>
#include <iostream>


Scene::Scene()
{
	std::cout << "New scene created!" << std::endl;
}


Scene& Scene::GetInstance()
{
	static Scene instance;
	return instance;
}


void Scene::addGameObject(GameObject& gameobject)
{
	m_GameObjects.push_back(gameobject);
	std::cout << "Added new gameobject to scene!" << std::endl;
}

void Scene::addLight(GameObject& light)
{
	m_Lights.push_back(light);
	std::cout << "Added new light to scene!" << std::endl;
}


