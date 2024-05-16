#pragma once
#include "ECS.h"
#include "UIIcon.h"
#include "UICollider.h"
#include "functional"
#include "TimeManager.h"

class UIButton : public UIIcon
{
private:
	std::vector<std::function<void()>> calls;
	UICollider* UIColl;
	
	float timeBetweenClicks; //in seconds
	float lastClickTime;

	bool isLocked; //meanes it stay darker if pressed
	bool gotClick;
	bool doCalls;
	bool isPressed;

	glm::vec4 startColor;
public:
	UIButton() : UIIcon() { isLocked = false; }
	UIButton(glm::vec2 newCoords, const char* pathTexture, float nowWidth, float nowHeight) : UIIcon(newCoords, pathTexture, nowWidth, nowHeight) { isLocked = false; }
	UIButton(glm::vec2 newCoords, const char* pathTexture, float nowWidth, float nowHeight, bool nowIsLocked) : UIIcon(newCoords, pathTexture, nowWidth, nowHeight) { isLocked = nowIsLocked; }

	void update() override;
	void init() override;

	void AddCall(std::function<void()> elem);

	void SetLockedStatus(bool locked);

	void SetColor(glm::vec4 nowColor) override
	{
		color = nowColor;
		startColor = color;
	}

	~UIButton();
private:
	void StartCalls();
	void LogicLockedButton();
	void LogicNotLockedButton();
};