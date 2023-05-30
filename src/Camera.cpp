#include <Camera.h>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>

extern GLFWwindow* window;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

Camera::Camera()
	: m_Window(window), m_ScreenWidth(SCREEN_WIDTH), m_ScreenHeight(SCREEN_HEIGHT), m_LastX(SCREEN_WIDTH/2), m_LastY(SCREEN_HEIGHT/2)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}


/**
 * \brief Mouse movement event callback
 * \param window GLFW context window
 * \param xpos cursor X position
 * \param ypos cursor Y position
 */
void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Camera& camera = GetInstance();
	if (camera.m_FirstMouseTick)
	{
		camera.m_LastX = xpos;
		camera.m_LastY = ypos;
		camera.m_FirstMouseTick = false;
	}
	float xoffset = xpos - camera.m_LastX;
	float yoffset = camera.m_LastY - ypos;
	camera.m_LastX = xpos;
	camera.m_LastY = ypos;
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera.m_Yaw += xoffset;
	camera.m_Pitch += yoffset;
	if (camera.m_Pitch > 89.0f)
		camera.m_Pitch = 89.0f;
	if (camera.m_Pitch < -89.0f)
		camera.m_Pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(camera.m_Yaw)) * cos(glm::radians(camera.m_Pitch));
	direction.y = sin(glm::radians(camera.m_Pitch));
	direction.z = sin(glm::radians(camera.m_Yaw)) * cos(glm::radians(camera.m_Pitch));
	camera.m_Front = glm::normalize(direction);
}

/**
 * \brief Mouse wheel event callback
 * \param window GLFWwindow context
 * \param xoffset Wheel x axis offset (???)
 * \param yoffset Wheel y axis offset
 */
void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera& camera = GetInstance();
	camera.m_POV -= (float)yoffset;
	if (camera.m_POV < 1.0f)
		camera.m_POV = 1.0f;
	if (camera.m_POV > 45.0f)
		camera.m_POV = 45.0f;
}

