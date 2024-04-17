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

	vertices[0] = -checkDist;
	vertices[1] = -checkDist;

	vertices[2] = checkDist;
	vertices[3] = -checkDist;

	vertices[4] = checkDist;
	vertices[5] = checkDist;

	vertices[6] = -checkDist;
	vertices[7] = checkDist;

	vb = new VertexBuffer(vertices, 4 * 2 * sizeof(float));
	ib = new IndexBuffer(indices, 6);

	va = new VertexArray;
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader = new Shader("res/Shaders/Circle.shader");
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();
}

void CircleCollider::draw()
{
	if (!drawingColliders)
		return;

	shader->Bind();
	if (getCol)
	{
		shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		if (isTrigger && (collisionObj != nullptr && collisionObj->GetIsTrigger()))
			ResolveColision();
	}
	else
	{
		shader->SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
	}
	shader->Unbind();

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, pos->GetPos().y, pos->GetPos().z + 1.0f));
	m_MVP = proj * view * model;

	shader->Bind();
	shader->SetUniformMat4f("u_MVP", m_MVP);
	shader->Unbind();

	renderer.Draw(*va, *ib, *shader);
}

bool CircleCollider::CheckCollision()
{
	for (auto& collider : AllColliders)
	{
		float checkDistNow = checkDist + collider->GetCheckDist();

		std::vector<glm::vec3> verticesB = collider->flatVectors;

		glm::vec3 posA = pos->GetPos();
		glm::vec3 posB = (verticesB[0] + verticesB[1] + verticesB[2] + verticesB[3]) / 4.0f; //avarage of pos_vertices sum is a center of the figure éîó

		if (glm::distance(posA, posB) < checkDistNow)
		{
			collisionObj = collider;
			return true;
		}
	}
	return false;
}

void CircleCollider::ResolveColision()
{
	if (!isMoveble)
		return;

	std::vector<glm::vec3> verticesB = collisionObj->flatVectors;

	glm::vec3 posA = pos->GetPos();
	glm::vec3 posB = (verticesB[0] + verticesB[1] + verticesB[2] + verticesB[3]) / 4.0f; //avarage of pos_vertices sum is a center of the figure éîó

	glm::vec3 resVec = posA - posB;
	resVec /= glm::length(resVec);

	pos->SetPos(pos->GetPos() + resVec * 5.0f);
}

CircleCollider::~CircleCollider()
{
	delete ib;
	delete va;
	delete vb;
	delete shader;
}