#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const char* pathTexture)
{
	color = glm::vec4(1.0f);

	shader_basic = new Shader("res/Shaders/Basic.shader");
	shader_basic->Bind();

	const std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
	texture->Bind();
	texture_path = pathTexture;
	shader_basic->SetUniform1i("u_Texture", 0);
	

	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	texture->Unbind();
}

SpriteComponent::SpriteComponent(const char* pathTexture, glm::vec4 nowColor)
{
	color = nowColor;

	shader_basic = new Shader("res/Shaders/Basic.shader");
	shader_basic->Bind();

	
	const std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
	texture->Bind();
	texture_path = pathTexture;
	shader_basic->SetUniform1i("u_Texture", 0);

	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	texture->Unbind();
}

SpriteComponent::SpriteComponent(const char* pathTexture, const char* pathShader, glm::vec4 nowColor)
{
	color = nowColor;

	shader_basic = new Shader(pathShader);
	shader_basic->Bind();

	
	const std::string mode = "CLAMP";
	texture = new Texture(pathTexture, mode);
	texture_path = pathTexture;

	
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	texture->Unbind();
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
	isDisabled = false;
	transform = entity->GetComponent<Transform>();

	m_MVP = glm::mat4(1.0f);

	shader_basic->Bind();
	texture->Bind();
	vb = new VertexBuffer(postitions, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
	
	shader_basic->SetUniform1i("u_Texture", 0);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader_basic->Unbind();
}

void SpriteComponent::update() 
{
	glDepthFunc(GL_LEQUAL);

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), transform->GetPos());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform->GetScale());
	m_MVP = proj * view * model * scale;
	
	shader_basic->Bind();
	shader_basic->SetUniformMat4f("u_MVP", m_MVP);
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	shader_basic->Unbind();
}
void SpriteComponent::draw()
{
	if (isDisabled)
		return;

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

