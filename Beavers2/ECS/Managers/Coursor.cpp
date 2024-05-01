#include "Coursor.h"


PositionComponent* Coursor::posBox;
Entity* Coursor::checkBox;
glm::vec3 Coursor::mousePos;

void Coursor::init()
{
	checkBox = &Manager::addEntity();
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
	
	mousePos.x = 2 * (mousePos.x + (GLFWGetWeidth() / 2)) / (GLFWGetWeidth()) - 1; //liner normalization from -1 to 1 (opengl coords)
	mousePos.y = 2 * (mousePos.y + (GLFWGetHeight() / 2)) / (GLFWGetHeight()) - 1; //liner normalization from -1 to 1 (opengl coords)

	glm::mat4 proj = CamComponent::GetProj();
	glm::mat4 view = glm::translate(glm::mat4(1.0f), CamComponent::GetPos());

	glm::vec4 mousePos4 = glm::vec4(mousePos.x, mousePos.y, mousePos.z, 1.0f);
	mousePos4 = view * glm::inverse(proj) * mousePos4; //first transoform from opengl coords to camera, than from camera to world space

	mousePos = glm::vec3(mousePos4.x, mousePos4.y, mousePos4.z);

	posBox->SetPos(mousePos);
}

Coursor::~Coursor()
{

}


