#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(const char* pathTexture, const char* pathShader, glm::vec4 nowColor)
{
	vb = new VertexBuffer(postitions, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader_basic = new Shader(pathShader);
	shader_basic->Bind();

	const std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
	texture->Bind();
	shader_basic->SetUniform1i("u_Texture", 0);

	color = nowColor;
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	texture->Unbind();
	
	m_MVP = glm::mat4(1.0f);
}

void SpriteComponent::SetNewColor(glm::vec4 newColor)
{
	color = newColor;
	shader_basic->Bind();
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	shader_basic->Unbind();
}

void SpriteComponent::init() 
{
	transform = entity->GetComponent<Transform>();
}

void SpriteComponent::update() 
{
	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform->GetPos());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform->GetScale());
	m_MVP = proj * view * model * scale;
	
	shader_basic->Bind();
	shader_basic->SetUniformMat4f("u_MVP", m_MVP);
	shader_basic->Unbind();
}
void SpriteComponent::draw()
{
	texture->Bind();
	Renderer::Draw(*va, *ib, *shader_basic);
	texture->Unbind();
}

SpriteComponent::~SpriteComponent()
{
	delete ib;
	delete vb;
	delete va;
	delete shader_basic;
	delete texture;
}

