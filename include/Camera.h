#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
public:
	static Camera& GetInstance()
	{
		static Camera instance;
		return instance;
	}
	~Camera() {};

	glm::mat4 GetView();

	GLFWwindow* m_Window;
	int m_ScreenWidth, m_ScreenHeight;
	float m_LastX, m_LastY;
	float m_Yaw = -90.f;
	float m_Pitch = 0.f;
	float m_Roll = 0.f;
	glm::vec3 m_Pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	float m_POV = 45.f;
	bool m_FirstMouseTick = true;
	float m_Speed = 5.f;

private:
	Camera();

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};