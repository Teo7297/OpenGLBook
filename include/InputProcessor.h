#pragma once

#include <GLFW/glfw3.h>
#include "SimpleActionEvent.h"


class InputProcessor
{
public:
	GLFWwindow* m_window;
	float m_mixFactor;

	InputProcessor(GLFWwindow* window, float mixFactor);
	void Process();

private:
	bool up_pressed = false;
	bool up_released = true;
	bool down_pressed = false;
	bool down_released = true;

	SimpleActionEvent onUPPressed;
	SimpleActionEvent onUPReleased;
	SimpleActionEvent onDOWNPressed;
	SimpleActionEvent onDOWNReleased;
	SimpleActionEvent onF3Pressed;
	SimpleActionEvent onF3Released;
	SimpleActionEvent onESCAPEPressed;
	SimpleActionEvent onESCAPEReleased;


};