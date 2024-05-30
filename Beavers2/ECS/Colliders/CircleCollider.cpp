#include "CircleCollider.h"
#include "Raycast.h"


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
	isEnabled = true;
	pos = entity->GetComponent<Transform>();

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

	glDepthFunc(GL_LEQUAL);

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
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, pos->GetPos().y, 0.0f));
	
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
	bool finelStateWithTrigger = false;

	for (auto& collider : AllColliders)
	{
		if (collider == this)
			continue;
		bool gotGap = false;

		std::vector<glm::vec3> verticesA = flatVectors;
		std::vector<glm::vec3> verticesB = collider->flatVectors;

		float checkDistNow = checkDist + collider->GetCheckDist();

		glm::vec3 posA = pos->GetPos();
		glm::vec3 sumVec = glm::vec3(0.0f);
		for (auto& vec : verticesB)
		{
			sumVec += vec;
		}

		glm::vec3 posB = sumVec / (float)verticesB.size(); //avarage of pos_vertices sum is a center of the figure йоу

		glm::vec2 posA2(posA);
		glm::vec2 posB2(posB);

		if (glm::distance(posA2, posB2) > checkDistNow)
		{
			continue;
		}

		for (int i = 0; i < verticesA.size(); i++)
		{
			glm::vec3 vertA1 = verticesA[i];
			glm::vec3 vertA2 = verticesA[(i + 1) % verticesA.size()];

			glm::vec3 sideOfBox = vertA2 - vertA1;
			glm::vec3 norm = glm::vec3(-sideOfBox.y, sideOfBox.x, 0);

			float minA, maxA;
			float minB, maxB;

			GetMinMaxDotProduct(verticesA, norm, minA, maxA);
			GetMinMaxDotProduct(verticesB, norm, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				gotGap = true;
				break;
			}
		}

		if (gotGap)
			continue;

		for (int i = 0; i < verticesB.size(); i++)
		{
			if (gotGap)
				break;
			glm::vec3 vertB1 = verticesB[i];
			glm::vec3 vertB2 = verticesB[(i + 1) % verticesB.size()];

			glm::vec3 sideOfBox = vertB2 - vertB1;
			glm::vec3 norm = glm::vec3(-sideOfBox.y, sideOfBox.x, 0);

			float minA, maxA;
			float minB, maxB;

			GetMinMaxDotProduct(verticesB, norm, minA, maxA);
			GetMinMaxDotProduct(verticesA, norm, minB, maxB);

			if (minA >= maxB || minB >= maxA)
			{
				gotGap = true;
				break;
			}
		}

		if (gotGap)
			continue;


		if (collider->GetIsTrigger())
			finelStateWithTrigger = true;

		collisionObjs.push_back(collider);
		finelState = true;
	}

	getColWithTrigger = finelStateWithTrigger;

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
		glm::vec3 sumVec = glm::vec3(0.0f);
		for (auto& vec : verticesB)
		{
			sumVec += vec;
		}

		glm::vec3 posBCenter = sumVec / (float)verticesB.size(); //avarage of pos_vertices sum is a center of the figure йоу
		glm::vec3 posB = Raycast::GetPointOfCollision(posA, posBCenter - posA, entity);

		resVec += posA - posB;
	}

	if (resVec == glm::vec3(0.0f))
		return;

	resVec /= glm::length(resVec);

	pos->SetPos(pos->GetPos() + resVec * 15.0f);
}

void CircleCollider::initVecPositions()
{
	float x = pos->GetPos().x;
	float y = pos->GetPos().y;

	flatVectors.clear();

	//короче создаю правильный n-угольник, чтобы аппроксемировать круг под алгоритм SAT
	for (int i = 0; i < 16; i++)
	{
		glm::vec3 pos = glm::vec3(x + std::cos(2.0f * pi * (i / 16.0f)) * checkDist,
								  y + std::sin(2.0f * pi * (i / 16.0f)) * checkDist,
								   0.0f);

		flatVectors.push_back(pos);
	}
}

CircleCollider::~CircleCollider()
{
	delete ib;
	delete va;
	delete vb;
	delete shader;
}