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


