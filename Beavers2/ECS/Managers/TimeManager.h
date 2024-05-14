#pragma once
#include "ECS.h"
#include <ctime>
#include <ratio>
#include <chrono>

class Time : public Component //works with seconds
{
private:
	static std::chrono::duration<double> nowTime;
	static std::chrono::duration<double> deltaTime;

	static std::chrono::system_clock::time_point startProgTime;
	static std::chrono::system_clock::time_point updateStart;
public:
	void init() override;

	void update() override;
	void lastDraw() override;

	static float GetDeltaTime();
	static float GetCurrentTime();
};