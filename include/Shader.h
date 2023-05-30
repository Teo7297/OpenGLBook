#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:

	// Program ID
	unsigned int ID;

	// Constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	// Binding
	void Bind() const;
	static void Unbind();

	// Uniforms setting
	void SetUniform(const std::string& name, bool value) const;
	void SetUniform(const std::string& name, int value) const;
	void SetUniform(const std::string& name, float value) const;
	void SetUniform(const std::string& name, float value1,float value2,float value3,float value4) const;
	void SetUniform(const std::string& name, glm::mat4 matrix4x4) const;

private:
	void CheckShaderCompilationStatus(unsigned int shaderID);
	void CheckProgramCompilationStatus(unsigned int programID);
};
