#include "BoxCollider.h"
#include "Raycast.h"

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
	pos = entity->GetComponent<Transform>();
	getColWithTrigger = false;

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
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos->GetPos().x, pos->GetPos().y, pos->GetPos().z));
	
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0f));
	model = model * scale;
	
	m_MVP = proj * view * model;

	shader->SetUniformMat4f("u_MVP", m_MVP);

	Renderer::DrawLines(*va, *ib, *shader);
	shader->Unbind();
}

bool BoxCollider::CheckCollision() //it's an SAT algorithm or something like that
{
	collisionObjs.clear();
	bool finelState = false;
	bool finelStateWithTrigger = false;

	for (auto& collider : AllColliders)
	{
		if (collider  == this)
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

		glm::vec3 posB = sumVec / (float)verticesB.size(); //avarage of pos_vertices sum is a center of the figure éîó
		
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


void BoxCollider::ResolveColision()
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

		glm::vec3 posBCenter = sumVec / (float)verticesB.size(); //avarage of pos_vertices sum is a center of the figure éîó
		glm::vec3 posB = Raycast::GetPointOfCollision(posA, posBCenter - posA, entity);


		resVec += posA - posB;
		resVec.z = 0.0f;
	}

	if (resVec == glm::vec3(0.0f))
		return;

	if (resVec == glm::vec3(0.0f))
		return;

	resVec /= glm::length(resVec);

	//TODO: some crazy math to increase speed when object near the center
	pos->SetPos(pos->GetPos() + resVec * 15.0f);
}

void BoxCollider::initVecPositions()
{
	float x = pos->GetPos().x;
	float y = pos->GetPos().y;
	flatVectors.clear();


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
