#pragma once
#include "ECS.h"
#include "PositionComponent.h"
#include "Renderer.h"



class CamComponent : public Component
{
private:
	static std::shared_ptr<PostitionComponent> pos;
	static glm::mat4 proj;
public:
	void init() override;

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