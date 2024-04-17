#include "BoxCollider.h"


BoxCollider::BoxCollider()
{
	width = 10.0f;
	height = 10.0f;
	
	checkDist = sqrt(width * width + height * height);

	isMoveble = false;
	isTrigger = true;
}

BoxCollider::BoxCollider(float nowWidth, float nowHeigt, bool nowIsTrigger, bool moveable)
{
	width = nowWidth;
	height = nowHeigt;
	
	checkDist = sqrt(width * width + height * height);

	isMoveble = moveable;
	isTrigger = nowIsTrigger;
}

void BoxCollider::init()
{
	pos = entity->GetComponent<PositionComponent>();
	
	vertices[0] = -width;
	vertices[1] = -height;

	vertices[2] = width;
	vertices[3] = -height;

	vertices[4] = width;
	vertices[5] = height;

	vertices[6] = -width;
	vertices[7] = height;

	vb = new VertexBuffer(vertices, 4 * 2 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	
	va = new VertexArray;
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader = new Shader("res/Shaders/WithoutTexBasic.shader");
	shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	shader->Unbind();

	initVecPositions();
}

void BoxCollider::draw()
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
	shader->Unbind();

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), -CamComponent::GetPos());
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, pos->GetPos().y, pos->GetPos().z + 1.0f));
	m_MVP = proj * view * model;

	shader->Bind();
	shader->SetUniformMat4f("u_MVP", m_MVP);
	shader->Unbind();

	renderer.DrawLines(*va, *ib, *shader);
}

bool BoxCollider::CheckCollision() //it's an SAT algorithm or something like that
{
	for (auto& collider : AllColliders)
	{
		if (collider  == this)
			continue;
		bool gotGap = false;

		std::vector<glm::vec3> verticesA = flatVectors;
		std::vector<glm::vec3> verticesB = collider->flatVectors;

		float checkDistNow = checkDist + collider->GetCheckDist();

		glm::vec3 posA = pos->GetPos();
		glm::vec3 posB = (verticesB[0] + verticesB[1] + verticesB[2] + verticesB[3]) / 4.0f; //avarage of pos_vertices sum is a center of the figure éîó
		
		if (glm::distance(posA, posB) > checkDistNow)
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

		collisionObj = collider;
		return true;
	}

	collisionObj = this;

	return false;
}


void BoxCollider::ResolveColision()
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

void BoxCollider::initVecPositions()
{
	float x = pos->GetPos().x;
	float y = pos->GetPos().y;

	flatVectors =
	{
		glm::vec3(x - width, y - height, 0), 
		glm::vec3(x + width, y - height, 0),
		glm::vec3(x + width, y + height, 0),
		glm::vec3(x - width, y + height, 0),
	};
}

BoxCollider::~BoxCollider()
{
	delete ib;
	delete va;
	delete vb;
	delete shader;
}
