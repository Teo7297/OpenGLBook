#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>


#include <Shader.h>
#include <InputProcessor.h>
//#include <Texture.h>
#include <Camera.h>
#include <Renderer.h>
#include <VertexBufferLayout.h>
#include <Colors.h>
#include <Model.h>

#define FLOAT_SIZE sizeof(GL_FLOAT)
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200
#define TARGET_FRAME_TIME 0.0166666667f

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


#define IMGUI_INIT() \
	IMGUI_CHECKVERSION();\
	ImGui::CreateContext();\
	ImGuiIO& io = ImGui::GetIO();\
	(void)io;\
	ImGui::StyleColorsDark();\
	ImGui_ImplGlfw_InitForOpenGL(window, true);\
	ImGui_ImplOpenGL3_Init();

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

glm::vec3 getModelToWorldCoordinates(const glm::mat4& modelMatrix, const glm::vec3& modelCoordinates)
{
	glm::mat4 inverseModelMatrix = glm::inverse(modelMatrix);
	glm::vec4 worldCoordinates = inverseModelMatrix * glm::vec4(modelCoordinates, 1.0f);
	return glm::vec3(worldCoordinates);
}


float mixFactor = 0.5f;

int main()
{
	GL_INIT();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	IMGUI_INIT();
	///////////////////////////////////////////////////////////// SHADERS /////////////////////////////////////////////////////////////


	const char* v1Path = "./shaders/VertexShader1.vert";
	//const char* v2Path = "./shaders/VertexShader2.vert";
	const char* f1Path = "./shaders/FragmentShader1.frag";
	//const char* f2Path = "./shaders/FragmentShader2.frag";

	Shader modelLoadShader = Shader(v1Path, f1Path);
	//Shader shader2 = Shader(v2Path, f2Path);

	//const char* lightVPath = "./shaders/LightReceiver.vert";
	//const char* lightFPath = "./shaders/LightReceiver.frag";
	//Shader modelLoadShader = Shader(lightVPath, lightFPath);

	/*const char* lightEmitterVPath = "./shaders/LightEmitter.vert";
	const char* lightEmitterFPath = "./shaders/LightEmitter.frag";
	Shader lightEmitterShader = Shader(lightEmitterVPath, lightEmitterFPath);*/

	///////////////////////////////////////////////////////////// END SHADERS /////////////////////////////////////////////////////////////


	// Texture 1

	//Texture texture1("./textures/bricks.jpg", GL_TEXTURE_2D, GL_RGB, GL_RGB);
	//texture1.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//texture1.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture1.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//texture1.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//// Texture 2
	//Texture texture2("./textures/awesomeface.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
	//texture2.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//texture2.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture2.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//texture2.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//// Texture 3 Container wood diffuse map
	//Texture texture3("./textures/container2.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
	//texture3.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//texture3.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture3.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//texture3.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//// Texture 4 Container wood specular map
	//Texture texture4("./textures/container2_specular.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
	//texture4.GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	//texture4.GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture4.GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//texture4.GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);





	///////////////////////////////////////////////////////////// RECTANGLE /////////////////////////////////////////////////////////////

	//float vertices[] = {
	//	// positions		| normals		     | texture coords
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	//};

	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(2.0f, 5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f, 3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f, 2.0f, -2.5f),
	//	glm::vec3(1.5f, 0.2f, -1.5f),
	//	glm::vec3(-1.3f, 1.0f, -1.5f)
	//};



	///////////////////////////////////////////////////////////// END RECTANGLE /////////////////////////////////////////////////////////////
	
	{
		InputProcessor inputProcessor(window, mixFactor);
		Renderer renderer = Renderer();
		Camera& camera = Camera::GetInstance();

		//VertexBuffer VBO_Rect = VertexBuffer(vertices, sizeof(vertices));

		//VertexBufferLayout VBO_Rect_Layout = VertexBufferLayout();
		//VBO_Rect_Layout.Push<float>(3);
		//VBO_Rect_Layout.Push<float>(3);
		//VBO_Rect_Layout.Push<float>(2);

		//VertexArray VAO_Rect = VertexArray();
		//VAO_Rect.AddBuffer(VBO_Rect, VBO_Rect_Layout);

		//ElementBuffer EBO_Rect = ElementBuffer({}, 0);
		


		deltaTime = 0.0f; // Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame

		const char* path = "C:/Users/teoca/Desktop/OpenGL_Projects/Models/backpack/backpack.obj";

		Model* backpack = new Model(path);

		while (!glfwWindowShouldClose(window))
		{
			inputProcessor.Process();


			


			renderer.SetBackgroundColor(Colors::DARK_GRAY);
			renderer.Clear();
			// Time transform variable to see things moving easily
			const float sinVal = sin(static_cast<float>(lastFrame));
			const float fastSinVal = sin(static_cast<float>(lastFrame * 5));
			const float cosVal = cos(static_cast<float>(lastFrame));

			const glm::mat4 projection = glm::perspective(glm::radians(camera.m_POV), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);


			auto cubePosition = glm::vec3(0.f);
			/*const glm::mat4 model1 =
				glm::translate(glm::identity<glm::mat4>(), cubePosition)
				*
				glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.f));*/


			glm::vec3 lightPosition = glm::vec3(2.0f, .5f, 1.0f);
			const glm::mat4 model2 =
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(3.f, 0.f, 0.5f))
				//glm::translate(glm::identity<glm::mat4>(), glm::vec3(sinVal, cosVal, 1.f))
				*
				glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.12f));

			const glm::vec3 lightWorldPosition = glm::vec3(model2 * glm::vec4(0.f, 0.f, 0.f, 1.f));

			
			/*const glm::vec3 cameraWorldPosition = glm::vec3(camera.GetView() * glm::vec4(0.f, 0.f, 0.f, 1.f));*/


			// Shader
			//lightReceiverShader.Bind();
			////lightReceiverShader.SetUniform("model", model1);
			//lightReceiverShader.SetUniform("view", camera.GetView());
			//lightReceiverShader.SetUniform("projection", projection);

			//lightReceiverShader.SetUniform("material.diffuse", 2);
			//lightReceiverShader.SetUniform("material.specular", 3);
			////lightReceiverShader.SetUniform("material.specular", glm::vec3(0.5f));
			//lightReceiverShader.SetUniform("material.shininess", 32.f);

			//// directional
			//lightReceiverShader.SetUniform("directional_light.toggled", false);
			//lightReceiverShader.SetUniform("directional_light.direction", -0.2f, -1.0f, -0.3f);
			//lightReceiverShader.SetUniform("directional_light.ambientStrength", .05f, .05f, .05f);
			//lightReceiverShader.SetUniform("directional_light.diffuseStrength", .1f, .1f, .1f);
			//lightReceiverShader.SetUniform("directional_light.specularStrength", .5f, .5f, .5f);

			//// spot
			//lightReceiverShader.SetUniform("spot_light.toggled", true);
			//lightReceiverShader.SetUniform("spot_light.position", lightWorldPosition);
			//lightReceiverShader.SetUniform("spot_light.direction", glm::normalize(glm::vec3(0.f) - lightWorldPosition));
			//lightReceiverShader.SetUniform("spot_light.ambientStrength", glm::vec3(.01f));
			//lightReceiverShader.SetUniform("spot_light.diffuseStrength", glm::vec3(1.f));
			//lightReceiverShader.SetUniform("spot_light.specularStrength", glm::vec3(1.f));
			//lightReceiverShader.SetUniform("spot_light.constant", 1.f);
			//lightReceiverShader.SetUniform("spot_light.linear", 0.09f);
			//lightReceiverShader.SetUniform("spot_light.quadratic", 0.032f);
			//lightReceiverShader.SetUniform("spot_light.cutOff", cos(glm::radians(7.5f)));
			//lightReceiverShader.SetUniform("spot_light.outerCutOff", cos(glm::radians(10.f)));


			//// point
			//constexpr int pointlights_amount = 3;

			//lightReceiverShader.SetUniform("point_lights.amount", pointlights_amount);
			//lightReceiverShader.SetUniform("point_lights.ambientStrength", .05f, .05f, .05f);
			//lightReceiverShader.SetUniform("point_lights.diffuseStrength", glm::vec3(1.f));
			//lightReceiverShader.SetUniform("point_lights.specularStrength", glm::vec3(1.f));
			//lightReceiverShader.SetUniform("point_lights.constant", 1.f);
			//lightReceiverShader.SetUniform("point_lights.linear", 0.09f);
			//lightReceiverShader.SetUniform("point_lights.quadratic", 0.032f);
			//lightReceiverShader.SetUniform("point_lights.color", Colors::WHITE);

			//lightReceiverShader.SetUniform("objectColor", Colors::WHITE);
			//lightReceiverShader.SetUniform("viewPos", camera.m_Pos);


			//lightEmitterShader.Bind();
			//lightEmitterShader.SetUniform("model", model2);
			//lightEmitterShader.SetUniform("view", camera.GetView());
			//lightEmitterShader.SetUniform("projection", projection);
			//lightEmitterShader.SetUniform("u_color", Colors::WHITE);
			//

			//// Textures
			//texture1.Activate();
			//texture1.Bind();
			//texture2.Activate();
			//texture2.Bind();
			//texture3.Activate();
			//texture3.Bind();
			//texture4.Activate();
			//texture4.Bind();

			//glm::vec3 pointlights_pos[pointlights_amount] = {};
			//glm::mat4 lightModels[pointlights_amount] = {};
			//for (int i = 0; i < pointlights_amount; i++)
			//{
			//	const glm::mat4 model3 =
			//		glm::translate(glm::identity<glm::mat4>(), glm::vec3((i%2 ? sinVal : cosVal) * 4, 0.f, 1.f - 4 * (float)i))
			//		//glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.f, 0.f, -5 * i))
			//		*
			//		glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.12f));

			//	const glm::vec3 pointlightWorldPosition = glm::vec3(model3 * glm::vec4(0.f, 0.f, 0.f, 1.f));

			//	pointlights_pos[i] = pointlightWorldPosition;
			//	lightModels[i] = model3;
			//}
			//lightReceiverShader.Bind();
			//lightReceiverShader.SetUniform("point_lights.position", *pointlights_pos, pointlights_amount);

			//for (unsigned int i = 0; i < 9; i++)
			//{
			//	glm::mat4 model = glm::mat4(1.0f);
			//	model = glm::translate(model, cubePositions[i]);
			//	//model = glm::rotate(model, glm::radians(20.0f * i * sinVal), glm::vec3(1.0f, 0.3f, 0.5f));
			//	lightReceiverShader.Bind();
			//	lightReceiverShader.SetUniform("model", model);

			//	renderer.Draw(VAO_Rect, EBO_Rect, lightReceiverShader);
			//}
			//// spotlight render
			//renderer.Draw(VAO_Rect, EBO_Rect, lightEmitterShader);

			//// pointlight render
			//for(int i = 0; i < pointlights_amount; i++)
			//{
			//	lightEmitterShader.Bind();
			//	lightEmitterShader.SetUniform("model", lightModels[i]);
			//	lightEmitterShader.SetUniform("view", camera.GetView());
			//	lightEmitterShader.SetUniform("projection", projection);
			//	lightEmitterShader.SetUniform("u_color", Colors::WHITE);
			//	renderer.Draw(VAO_Rect, EBO_Rect, lightEmitterShader);
			//}

			//// Unbinding
			//texture2.Unbind();
			

			modelLoadShader.Bind();
			modelLoadShader.SetUniform("model", glm::identity<glm::mat4>());
			modelLoadShader.SetUniform("view", camera.GetView());
			modelLoadShader.SetUniform("projection", projection);
			backpack->Draw(modelLoadShader);

			//////////////// END RECTANGLE //////////////////

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Test");
			ImGui::SetWindowSize(ImVec2(400, 200));
			ImGui::Button("Hello");
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();


			auto currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			while (deltaTime < TARGET_FRAME_TIME)
			{
				deltaTime += static_cast<float>(glfwGetTime()) - currentFrame;
				currentFrame = static_cast<float>(glfwGetTime());
			}
			lastFrame = currentFrame;
			// std::cout << deltaTime << std::endl;

		} // This scope block cleans up all on-stack created objects
	}
	glfwTerminate();
	return 0;
}
