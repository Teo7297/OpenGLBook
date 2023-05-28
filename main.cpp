#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


#define GL_INIT glfwInit(); \
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\
GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);\
if (window == nullptr)\
{\
	std::cout << "Failed to create GLFW window" << std::endl;\
	glfwTerminate();\
	return -1;\
}\
glfwMakeContextCurrent(window);\
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))\
{\
	std::cout << "Failed to initialize GLAD" << std::endl;\
	return -1;\
}\
glViewport(0, 0, 800, 600);\
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);\
print_attributes_supported();

void print_attributes_supported()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
		<< std::endl;

}


void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void checkShaderCompilationStatus(unsigned int shaderID)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void checkShaderProgramCompilationStatus(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


int main()
{
	GL_INIT

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aCol;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		" vertexColor = vec4(aCol.x, aCol.y, aCol.z, 1.0f);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	const char* fragmentShaderSource = "#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		"uniform vec4 uniformColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vertexColor;\n"
		"}\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// SHADER 2
	const char* vertexShader2Source = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" vertexColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";
	unsigned int vertexShader2;
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader2, 1, &vertexShader2Source, nullptr);
	glCompileShader(vertexShader2);

	const char* fragmentShader2Source = "#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor =vertexColor;\n"
		"}\0";
	unsigned int fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShader2Source, nullptr);
	glCompileShader(fragmentShader2);

	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader2);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glDeleteShader(vertexShader2);
	glDeleteShader(fragmentShader2);
	///////////// end of shader code ////////////////




	///////////////////////////////////////////////////////////// TRIANGLE /////////////////////////////////////////////////////////////

	// Vertices for simple triangle
	float vertices[] = {
		-0.7f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.2f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.45f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	// Vertex buffer object
	unsigned int VBO_Simple_Triangle;
	glGenBuffers(1, &VBO_Simple_Triangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Simple_Triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex array object (after binding will store vertex attrib calls)
	unsigned int VAO_Simple_Triangle;
	glGenVertexArrays(1, &VAO_Simple_Triangle);
	glBindVertexArray(VAO_Simple_Triangle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);								// Close VAO to save settings on it
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Close other buffers to free resources


	///////////////////////////////////////////////////////////// END TRIANGLE /////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////// RECTANGLE /////////////////////////////////////////////////////////////

	// Vertices and indices for rectangle
	float vertices_rect[] = {
		0.9f, 0.5f, 0.0f, // top right
		0.9f, 0.0f, 0.0f, // bottom right
		0.4f, 0.0f, 0.0f, // bottom left
		0.4f, 0.5f, 0.0f // top left
	};

	unsigned int indices_rect[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// Vertex buffer object
	unsigned int VBO_Simple_Rect;
	glGenBuffers(1, &VBO_Simple_Rect);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Simple_Rect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rect), vertices_rect, GL_STATIC_DRAW);

	// Vertex array object (after binding will store vertex attrib calls)
	unsigned int VAO_Simple_Rect;
	glGenVertexArrays(1, &VAO_Simple_Rect);
	glBindVertexArray(VAO_Simple_Rect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Element buffer object (vertex index array)
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rect), indices_rect, GL_STATIC_DRAW);

	// Clear
	glBindVertexArray(0);								// Close VAO to save settings in it
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Close other buffers to free resources
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Close other buffers to free resources

	///////////////////////////////////////////////////////////// END RECTANGLE /////////////////////////////////////////////////////////////


	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		// Set Background
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniformColor");

		// Draw triangle
		glUseProgram(shaderProgram);													// bind shader
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);		// send uniforms to shader
		glBindVertexArray(VAO_Simple_Triangle);											// bind VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);								// draw call
		glUseProgram(0);															// unbind shader
		glBindVertexArray(0);														// unbind VAO

		// Draw rect
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO_Simple_Rect);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
