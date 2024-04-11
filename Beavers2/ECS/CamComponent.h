#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "Renderer.h"



class CamComponent : public Component
{
private:
	std::shared_ptr<PostitionComponent> pos;
	glm::mat4 proj;
public:
	void init() override;

	glm::vec3 GetPos();
	glm::mat4 GetProj();

	~CamComponent();
};