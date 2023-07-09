#include <GameObject.h>
#include <GL/gl.h>
#include <Shader.h>
#include <Texture.h>
#include <VertexBuffer.h>

#include "VertexBufferLayout.h"
#include <VertexArray.h>

namespace gameobject
{
	GameObject::GameObject(Renderer& renderer)
		: renderer(renderer)
	{
// shader init
		const char* lightVPath = "./shaders/LightReceiver.vert";
		const char* lightFPath = "./shaders/LightReceiver.frag";
		shader = new Shader(lightVPath, lightFPath);

// texture init
		// Container wood diffuse map
		diffMap = new Texture("./textures/container2.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
		diffMap->GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
		diffMap->GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
		diffMap->GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		diffMap->GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Container wood specular map
		diffMap = new Texture("./textures/container2_specular.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA, true);
		diffMap->GL_TexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
		diffMap->GL_TexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
		diffMap->GL_TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		diffMap->GL_TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);



// vertexarray init
		VertexBuffer VBO(vertices, sizeof(vertices));
		VertexBufferLayout layout = VertexBufferLayout();
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		VAO = new VertexArray();
		VAO->AddBuffer(VBO, layout);

// elementbuffer init
		EBO = new ElementBuffer({}, 0);

	}

	void GameObject::Update(const float& deltaTime)
	{
		shader->Bind();

		diffMap->Activate();
		diffMap->Bind();
		specMap->Activate();
		specMap->Bind();

		// set uniforms

		//draw
		renderer.Draw(*VAO, *EBO, *shader);

	}





}
