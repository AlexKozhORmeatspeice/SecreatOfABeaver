#include "Coursor.h"


std::shared_ptr<PositionComponent> Coursor::posBox;
Entity* Coursor::checkBox;
glm::vec3 Coursor::mousePos;

void Coursor::init()
{
	checkBox = &CreatObj();
	mousePos = glm::vec3(0.0f, 0.0f, 0.0f);

	checkBox->AddComponent<PositionComponent>();
	posBox = checkBox->GetComponent<PositionComponent>();

	checkBox->AddComponent<BoxCollider>(3.0f, 3.0f, false, false);
}

void Coursor::update()
{
	double xpos, ypos;

	GLFWSetMousePos(xpos, ypos);

	mousePos.x = xpos - GLFWGetWeidth() / 2; //need to translate coords from glfw to opengl
	mousePos.y = GLFWGetHeight() / 2 - ypos;

	posBox->SetPos(CamComponent::GetPos() + mousePos);

}

bool Coursor::GetCollision(Entity* collider)
{
	BoxCollider* coll1 = collider->GetComponent<BoxCollider>().get();
	BoxCollider* coll2 = checkBox->GetComponent<BoxCollider>()->GetColllidObj();

	if (coll1 != nullptr && coll2 != nullptr)
	{
		return coll1 == coll2;
	}

	std::cout << "NULL POINTER" << std::endl;

	return false;
}



