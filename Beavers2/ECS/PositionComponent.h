#pragma once
#include "Render.h"
#include "ECS.h"


class Transform : public Component
{
private:
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 rotation;

public:
	Transform();
	Transform(glm::vec3 newPos);
	Transform(glm::vec3 newPos, glm::vec3 newScale);
	Transform(glm::vec3 newPos, glm::vec3 newScale, glm::vec3 newRot);

	glm::vec3 GetPos();
	void SetPos(glm::vec3 newPos);

	glm::vec3 GetScale();
	void SetScale(glm::vec3 newScale);

	glm::vec3 GetRot();
	void SetRot(glm::vec3 newRot);

	void init() override;

	void update() override;
	

	~Transform();
};