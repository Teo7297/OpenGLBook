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

#include <Renderer.h>
#include <VertexBufferLayout.h>


#define FLOAT_SIZE sizeof(GL_FLOAT)
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200
#define TARGET_FRAME_TIME 0.0166666667

extern int SCREEN_WIDTH = SCR_WIDTH;
extern int SCREEN_HEIGHT = SCR_HEIGHT;
GLFWwindow* window;
extern GLFWwindow* WINDOW = window;
float deltaTime;
extern float* DELTA_TIME = &deltaTime;

#define GL_INIT(); glfwInit(); \
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
	GL_INIT();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

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
	texture2.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture2.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	texture2.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture2.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	///////////////////////////////////////////////////////////// RECTANGLE /////////////////////////////////////////////////////////////

	float vertices_rect[] = {
		// Front face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // Top right
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  // Top left

		// Back face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // Bottom left
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // Bottom right
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,   // Top right
		-0.5f,  0.5f, 0.5f, 0.0f, 1.0f,   // Top left

		// Left face
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // Bottom left
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // Top right
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // Top left

		// Right face
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // Bottom left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  // Top right
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // Top left

		 // Top face
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  // Bottom left
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  // Top right
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  // Top left

		// Bottom face
	   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom left
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  // Top right
	   -0.5f, -0.5f,  0.5f, 0.0f, 1.0f   // Top left
	};

	unsigned int indices_rect[] = {
		0, 1, 2,
		2, 3, 0,  // Front face

		4, 5, 6,
		6, 7, 4,  // Back face

		8, 9, 10,
		10, 11, 8,  // Left face

		12, 13, 14,
		14, 15, 12,  // Right face

		16, 17, 18,
		18, 19, 16,  // Top face

		20, 21, 22,
		22, 23, 20  // Bottom face
	};



	///////////////////////////////////////////////////////////// END RECTANGLE /////////////////////////////////////////////////////////////
	
	{
		InputProcessor inputProcessor(window, mixFactor);
		Renderer renderer = Renderer();
		Camera& camera = Camera::GetInstance();

		VertexBuffer VBO_Rect = VertexBuffer(vertices_rect, sizeof(vertices_rect));

		VertexBufferLayout VBO_Rect_Layout = VertexBufferLayout();
		VBO_Rect_Layout.Push<float>(3);
		VBO_Rect_Layout.Push<float>(2);

		VertexArray VAO_Rect = VertexArray();
		VAO_Rect.AddBuffer(VBO_Rect, VBO_Rect_Layout);

		ElementBuffer EBO_Rect = ElementBuffer(indices_rect, sizeof(indices_rect));
		


		deltaTime = 0.0f; // Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame



		

		while (!glfwWindowShouldClose(window))
		{
			inputProcessor.Process();


			renderer.SetBackgroundColor(.2f, .3f, .3f, 1.f);
			renderer.Clear();

			// Time transform variable to see things moving easily
			const float sinVal = sin(static_cast<float>(glfwGetTime())) + 1.f;

			const glm::mat4 projection = glm::perspective(glm::radians(camera.m_POV), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);




			//////////////// DRAW RECTANGLE //////////////////

			// Shader
			shader2.Bind();
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
			VAO_Rect.Bind();

			for (int i = 0; i < 10; i++)
			{

				const glm::mat4 model =
					glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.25f * i - 1.f, 0.1f * i, 0.2f * i))
					*
					glm::rotate(glm::identity<glm::mat4>(), glm::radians(50.0f) * static_cast<float>(glfwGetTime() * 3), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)))
					*
					glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.2f))
					;
				shader2.SetUniform("model", model);
				renderer.Draw(VAO_Rect, EBO_Rect, shader2);
			}

			// Unbinding
			Shader::Unbind();
			VAO_Rect.Unbind();
			texture2.Unbind();

			//////////////// END RECTANGLE //////////////////


			// Swap buffer and poll events
			glfwSwapBuffers(window);
			glfwPollEvents();


			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			while (deltaTime < TARGET_FRAME_TIME)
			{
				deltaTime += glfwGetTime() - currentFrame;
				currentFrame = glfwGetTime();
			}
			lastFrame = currentFrame;
			// std::cout << deltaTime << std::endl;

		} // This scope block cleans up all on-stack created objects
	}
	glfwTerminate();
	return 0;
}
