#include "InputProcessor.h"

InputProcessor::InputProcessor(GLFWwindow* window, float mixFactor)
	: m_window(window), m_mixFactor(mixFactor)
{
}

void InputProcessor::Process()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//EventManager::Get()->dispatchEvent(&onESCAPEPressed);
		glfwSetWindowShouldClose(m_window, true);

	if (glfwGetKey(m_window, GLFW_KEY_F3) == GLFW_PRESS)
		//EventManager::Get()->dispatchEvent(&onF3Pressed);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(m_window, GLFW_KEY_F3) == GLFW_RELEASE)
		//EventManager::Get()->dispatchEvent(&onF3Released);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (up_released && glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		//EventManager::Get()->dispatchEvent(&onUPPressed);
		m_mixFactor = std::min(m_mixFactor + 0.1f, 1.0f);
		up_released = false;
		up_pressed = true;
	}

	if (down_released && glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		//EventManager::Get()->dispatchEvent(&onDOWNPressed);
		m_mixFactor = std::max(m_mixFactor - 0.1f, 0.0f);
		down_released = false;
		down_pressed = true;
	}

	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		//EventManager::Get()->dispatchEvent(&onUPReleased);
		up_pressed = false;
		up_released = true;
	}

	if (down_pressed && glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		//EventManager::Get()->dispatchEvent(&onDOWNReleased);
		down_pressed = false;
		down_released = true;
	}
}

