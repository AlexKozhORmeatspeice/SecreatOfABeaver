#pragma once
#include "Components.h"
#include "Renderer.h"


class SpriteComponent : public Component
{
private:
	PostitionComponent* pos;
	//CameraComponent* activeCam;
	glm::mat4 m_MVP;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexArray* va;
	Shader* shader_basic;
	Texture* texture;
	Renderer renderer;

	glm::vec4 color;

	float postitions[4*4] = {
	 -50.0f, -50.0f, 0.0f, 0.0f,
	  50.0f, -50.0f, 1.0f, 0.0f,
	  50.0f,  50.0f, 1.0f, 1.0f,
	 -50.0f,  50.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
public:
	SpriteComponent() = default;

	SpriteComponent(const char* pathTexture, const char* pathShader, glm::vec4 nowColor)
	{
		color = nowColor;
		//activeCam = &nowCam;

		vb = new VertexBuffer(postitions, 4 * 2 * 2 * sizeof(float));
		ib = new IndexBuffer(indices, 6);
		va = new VertexArray;

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va->AddBuffer(*vb, layout);

		shader_basic = new Shader(pathShader);
		shader_basic->Bind();

		texture = new Texture(pathTexture);
		texture->Bind();
		shader_basic->SetUniform1i("u_Texture", 0);

		shader_basic->Unbind();
		vb->Unbind();
		ib->Unbind();
		va->Unbind();
	}

	void SetNewColor(glm::vec4 newColor)
	{
		color = newColor;
	}

	void init() override
	{
		pos = &entity->GetComponent<PostitionComponent>();
	}

	void update() override
	{
		/*glm::mat4 proj = activeCam->GetProj();
		glm::mat4 view = glm::translate(glm::mat4(1.0f), activeCam->GetPos());
		glm::mat4 model = glm::translate(glm::mat4(1.0f), pos->GetPos());
		m_MVP = proj * view * model;*/
		
		

		shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
		//shader_basic->SetUniformMat4f("u_MVP", m_MVP);
	}
	void draw() override
	{
		shader_basic->Bind();
		renderer.Draw(*va, *ib, *shader_basic);
	}

	~SpriteComponent()
	{
		delete ib;
		delete vb;
		delete va;
		delete shader_basic;
		delete texture;
	}
};