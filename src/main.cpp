#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>
#include <thread>

#include <Shader.h>
#include <InputProcessor.h>
#include <Texture.h>
#include <Camera.h>


#define FLOAT_SIZE sizeof(GL_FLOAT)
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200

extern int SCREEN_WIDTH = SCR_WIDTH;
extern int SCREEN_HEIGHT = SCR_HEIGHT;
GLFWwindow* window;
extern GLFWwindow* WINDOW = window;
float deltaTime;
extern float* DELTA_TIME = &deltaTime;

#define GL_INIT() glfwInit(); \
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\
window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);\
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
glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);\
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

int main()
{
	GL_INIT()
	
	
	///////////////////////////////////////////////////////////// SHADERS /////////////////////////////////////////////////////////////


	const char* v1Path = "./shaders/VertexShader1.vert";
	const char* v2Path = "./shaders/VertexShader2.vert";
	const char* f1Path = "./shaders/FragmentShader1.frag";
	const char* f2Path = "./shaders/FragmentShader2.frag";

	Shader shader1 = Shader(v1Path, f1Path);
	Shader shader2 = Shader(v2Path, f2Path);


	///////////////////////////////////////////////////////////// END SHADERS /////////////////////////////////////////////////////////////


	// Texture 1

	Texture texture1("./textures/bricks.jpg", GL_TEXTURE_2D, GL_RGB, GL_RGB);
	texture1.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture1.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	texture1.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture1.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Texture 2
	Texture texture2("./textures/awesomeface.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
	texture2 .GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture2 .GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	texture2 .GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture2 .GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	///////////////////////////////////////////////////////////// RECTANGLE /////////////////////////////////////////////////////////////

	// Vertices and indices for rectangle
	//float vertices_rect[] = {
	//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,		// top right
	//	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,		// bottom right
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,		// bottom left
	//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f		// top left
	//};

	float vertices_rect[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, reinterpret_cast<void*>(FLOAT_SIZE * 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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

	/////////////
	///
	Camera& camera = Camera::GetInstance();
	////////////



	InputProcessor inputProcessor(window, mixFactor);

	deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window))
	{
		inputProcessor.Process();


		// Set Background
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Time transform variable to see things moving easily
		const float sinVal = sin(static_cast<float>(glfwGetTime())) + 1.f;

		///////// MVP Matrix for rectangle ////////////
		const glm::mat4 projection = glm::perspective(glm::radians(camera.m_POV), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);

		


		//////////////// DRAW RECTANGLE //////////////////

		// Shader
		shader2.Bind();
		//shader2.SetUniform("model", model);
		shader2.SetUniform("view", camera.GetView());
		shader2.SetUniform("projection", projection);
		shader2.SetUniform("ourTexture", 0);
		shader2.SetUniform("ourTexture2", 1);
		shader2.SetUniform("mixFactor", inputProcessor.m_mixFactor);

		// Textures
		texture1.Activate();
		texture1.Bind();
		texture2.Activate();
		texture2.Bind();

		// VAO
		glBindVertexArray(VAO_Simple_Rect);

		// Draw call
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		for (int i = 0; i < 10; ++i)
		{
			
			const glm::mat4 model =
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.25f * i - 1.f, 0.1f * i, 0.2f * i))
				*
				glm::rotate(glm::identity<glm::mat4>(), glm::radians(50.0f) * static_cast<float>(glfwGetTime() * 3), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)))
				*
				glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.25))
				;
			shader2.SetUniform("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}

		// Unbinding
		Shader::Unbind();
		glBindVertexArray(0);
		texture2.Unbind();

		//////////////// END RECTANGLE //////////////////


		// Swap buffer and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		while(deltaTime < 1.f/60.f)
		{
			deltaTime += glfwGetTime() - currentFrame;
			currentFrame = glfwGetTime();
		}
		lastFrame = currentFrame;

	}

	glfwTerminate();
	return 0;
}
