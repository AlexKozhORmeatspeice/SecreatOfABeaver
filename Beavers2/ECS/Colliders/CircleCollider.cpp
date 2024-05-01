#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
	checkDist = 1.0f;
	isTrigger = true;
	isMoveble = true;
}

CircleCollider::CircleCollider(float radius, bool nowIsTrigger, bool moveable)
{
	checkDist = radius;
	isTrigger = nowIsTrigger;
	isMoveble = moveable;
}

void CircleCollider::init()
{
	pos = entity->GetComponent<PositionComponent>();

	vb = new VertexBuffer(vertices, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);

	va = new VertexArray;
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader = new Shader("res/Shaders/Circle.shader");
	shader->Bind();
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();

	initVecPositions();
}

void CircleCollider::draw()
{
	if (!drawingColliders)
		return;

	shader->Bind();
	if (getCol)
	{
		shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		shader->SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
	}
	

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, pos->GetPos().y, pos->GetPos().z + 1.0f));
	
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(checkDist, checkDist, 1.0f));
	model = model * scale;

	m_MVP = proj * view * model;

	shader->SetUniformMat4f("u_MVP", m_MVP);

	Renderer::Draw(*va, *ib, *shader);
	shader->Unbind();
}

bool CircleCollider::CheckCollision()
{
	collisionObjs.clear();
	bool finelState = false;

	for (auto& collider : AllColliders)
	{
		if (collider == this)
			continue;

		float checkDistNow = checkDist + collider->GetCheckDist();

		std::vector<glm::vec3> verticesB = collider->flatVectors;

		glm::vec3 posA = pos->GetPos();
		glm::vec3 posB = (verticesB[0] + verticesB[1] + verticesB[2] + verticesB[3]) / 4.0f; //avarage of pos_vertices sum is a center of the figure éîó

		glm::vec2 posA2(posA);
		glm::vec2 posB2(posB);

		if (glm::distance(posA2, posB2) < checkDistNow )
		{
			collisionObjs.push_back(collider);
			finelState = true;
		}
	}

	return finelState;
}

void CircleCollider::ResolveColision()
{
	if (!isMoveble)
		return;

	glm::vec3 posA = pos->GetPos();
	glm::vec3 resVec = glm::vec3(0.0f);
	for (auto& collisionObj : collisionObjs)
	{
		if (!collisionObj->GetIsTrigger() || collisionObj == this)
			continue;

		std::vector<glm::vec3> verticesB = collisionObj->flatVectors;
		glm::vec3 posB = (verticesB[0] + verticesB[1] + verticesB[2] + verticesB[3]) / 4.0f; //avarage of pos_vertices sum is a center of the figure éîó

		resVec += posA - posB;
	}


	if (resVec == glm::vec3(0.0f))
		return;
	resVec /= glm::length(resVec);

	pos->SetPos(pos->GetPos() + resVec * 5.0f);
}

void CircleCollider::initVecPositions()
{
	float x = pos->GetPos().x;
	float y = pos->GetPos().y;

	flatVectors =
	{
		glm::vec3(x - checkDist, y - checkDist, 0),
		glm::vec3(x + checkDist, y - checkDist, 0),
		glm::vec3(x + checkDist, y + checkDist, 0),
		glm::vec3(x - checkDist, y + checkDist, 0),
	};
}

CircleCollider::~CircleCollider()
{
	delete ib;
	delete va;
	delete vb;
	delete shader;
}