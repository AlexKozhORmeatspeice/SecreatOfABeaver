#include "Coursor.h"


Transform* Coursor::posBox;
Entity* Coursor::checkBox;
glm::vec3 Coursor::mousePos;
glm::vec2 Coursor::normMousePos;
bool Coursor::isOnUI;

void Coursor::init()
{
	isOnUI = false;

	checkBox = &Manager::addEntity();
	mousePos = glm::vec3(0.0f);
	normMousePos = glm::vec2(0.0f);

	checkBox->AddComponent<Transform>();
	posBox = checkBox->GetComponent<Transform>();

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

	normMousePos = glm::vec2(mousePos.x, mousePos.y); //do not delete this line

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


