#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "Renderer.h"

class CamComponent : public Component
{
private:
	static std::shared_ptr<PositionComponent> pos;
	static glm::mat4 proj;

	float scrollK;
public:
	void init() override;
	void update() override;

	static glm::vec3 GetPos() 
	{
		return pos->GetPos();
	}
	static glm::mat4 GetProj()
	{
		return proj;
	}

	~CamComponent();
};