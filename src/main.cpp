#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>

#include <Shader.h>



#define FLOAT_SIZE sizeof(GL_FLOAT)

#define GL_INIT() glfwInit(); \
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\
GLFWwindow* window = glfwCreateWindow(1600, 1200, "LearnOpenGL", NULL, NULL);\
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
glViewport(0, 0, 1600, 1200);\
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


float mixFactor = 0.5f;
bool up_released = true;
bool up_pressed = true;
bool down_released = true;
bool down_pressed = true;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if(glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (up_released && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixFactor = std::min(mixFactor + 0.1f, 1.0f);
		up_released = false;
		up_pressed = true;
	}

	if (down_released && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixFactor = std::max(mixFactor - 0.1f, 0.0f);
		down_released = false;
		down_pressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		up_pressed = false;
		up_released = true;
	}

	if (down_pressed && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		down_pressed = false;
		down_released = true;
	}
}



int main()
{
	GL_INIT()

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	///////////////////////////////////////////////////////////// SHADERS /////////////////////////////////////////////////////////////

	const char* v1Path = "./shaders/VertexShader1.vert";
	const char* v2Path = "./shaders/VertexShader2.vert";
	const char* f1Path = "./shaders/FragmentShader1.frag";
	const char* f2Path = "./shaders/FragmentShader2.frag";

	Shader shader1 = Shader(v1Path, f1Path);
	Shader shader2 = Shader(v2Path, f2Path);


	///////////////////////////////////////////////////////////// END SHADERS /////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////// TRIANGLE /////////////////////////////////////////////////////////////

	// Vertices for simple triangle
	//float vertices[] = {
	//	-0.7f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
	//	-0.2f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
	//	-0.45f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top
	//};

	float vertices[] = {
		// 3 position        // 3 color        // 2 texcoords
		-0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,			// left
		 0.2f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,			// right
		 0.0f,  0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f			// top
	};

	float texCoords[] = {
		0.0f, 0.0f, // lower-left corner
		1.0f, 0.0f, // lower-right corner
		0.5f, 1.0f // top-center corner
	};

	// Texture 1

	// Create, bind and set Texture object
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load texture jpg
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./textures/bricks.jpg", &width, &height, &nrChannels, 0);
	if(data)
	{
		// Set texture data to Texture object
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::TEXTURE::LOADING" << std::endl;
	}
	// Free space
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Texture 2
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glActiveTexture(texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Load texture jpg
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("./textures/awesomeface.png", &width, &height, &nrChannels, 0);
	
	if (data)
	{
		// Set texture data to Texture object
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::TEXTURE::LOADING" << std::endl;
	}
	// Free space
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Vertex buffer object
	unsigned int VBO_Simple_Triangle;
	glGenBuffers(1, &VBO_Simple_Triangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Simple_Triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex array object (after binding will store vertex attrib calls)
	unsigned int VAO_Simple_Triangle;
	glGenVertexArrays(1, &VAO_Simple_Triangle);
	glBindVertexArray(VAO_Simple_Triangle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, reinterpret_cast<void*>(3 * FLOAT_SIZE));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, reinterpret_cast<void*>(6 * FLOAT_SIZE));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);								// Close VAO to save settings on it
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Close other buffers to free resources


	///////////////////////////////////////////////////////////// END TRIANGLE /////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////// RECTANGLE /////////////////////////////////////////////////////////////

	// Vertices and indices for rectangle
	float vertices_rect[] = {
		0.9f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,		// top right
		0.9f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,		// bottom right
		0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,		// bottom left
		0.4f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f		// top left
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, reinterpret_cast<void*>(FLOAT_SIZE * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, reinterpret_cast<void*>(FLOAT_SIZE * 6));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

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

		// Draw triangle
		shader1.Bind();													
		shader1.SetUniform("positionOffset", 0.4f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		shader1.SetUniform("ourTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader1.SetUniform("ourTexture2", 1);
		glBindVertexArray(VAO_Simple_Triangle);											
		glDrawArrays(GL_TRIANGLES, 0, 3);								
		Shader::Unbind();
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);


		// Draw rect
		shader2.Bind();
		shader2.SetUniform("uniformColor", 0.0f, greenValue, 0.0f, 1.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		shader2.SetUniform("ourTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader2.SetUniform("ourTexture2", 1);
		shader2.SetUniform("mixFactor", mixFactor);
		glBindVertexArray(VAO_Simple_Rect);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		Shader::Unbind();
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
