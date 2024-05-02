#pragma once
#include "ECS.h"
#include "UIIcon.h"
#include "UICollider.h"
#include "ctime"

class UIButton : public UIIcon
{
private:
	std::vector<void (*)()> calls;
	UICollider* UIColl;
	
	unsigned int timeBetweenClicks = 1; //in seconds
	unsigned int lastClickTime;

	bool gotClick;
	bool doCalls;

	glm::vec4 startColor;
public:
	UIButton() : UIIcon() {}
	UIButton(glm::vec2 newCoords, const char* pathTexture, float nowWidth, float nowHeight) : UIIcon(newCoords, pathTexture, nowWidth, nowHeight) {}

	void update() override;
	void init() override;

	void AddCall(void (*)());

	~UIButton();
private:
	void StartCalls();
};