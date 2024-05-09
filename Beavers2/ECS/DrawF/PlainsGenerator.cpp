#include <PlainsGenerator.h>

Tile::Tile(float now_width, float now_height, const char* pathShader, const char* pathTexture)
{
	width = now_width;
	height = now_height;

	shader_basic = new Shader(pathShader);
	shader_basic->Bind();

	std::string mode = "REPEAT";
	texture = new Texture(pathTexture, mode);
	texture->Bind();
	shader_basic->SetUniform1i("u_Texture", 0);

	shader_basic->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

void Tile::init()
{
	pos = entity->GetComponent<Transform>();
	float tile_how_much_x = width / side;
	float tile_how_much_y = height / side;
	float verticesArr[4 * 4] = 
	{
		(- 1)* width, (- 1)*height, 0.0f, 0.0f, // 0
		  (1)* width, (- 1)*height, tile_how_much_x, 0.0f, // 1
		  (1) *width, (1 )*height,  tile_how_much_x, tile_how_much_y, //2
		  (-1)*width, (1 )*height, 0.0f, tile_how_much_y  //3
	};

	unsigned int indexesArr[6] = 
	{
		0, 
		1, 
		2, 
		2, 
		3,
		0
	};

	std::copy(vertices.begin(), vertices.end(), verticesArr);
	std::copy(indexes.begin(), indexes.end(), indexesArr);
	vb = new VertexBuffer(verticesArr, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indexesArr, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	

	shader_basic->Unbind();
	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	texture->Unbind();
}

void Tile::update()
{
	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), pos->GetPos());
	m_MVP = proj * view * model;

	shader_basic->Bind();
	shader_basic->SetUniformMat4f("u_MVP", m_MVP);
	shader_basic->Unbind();
}

void Tile::firstDraw()
{
	glDepthFunc(GL_LEQUAL);

	texture->Bind();
	Renderer::Draw(*va, *ib, *shader_basic);
	texture->Unbind();
}