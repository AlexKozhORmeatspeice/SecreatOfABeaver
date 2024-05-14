#include "TimeManager.h"


std::chrono::duration<double> Time::nowTime;
std::chrono::duration<double> Time::deltaTime;

std::chrono::system_clock::time_point Time::startProgTime;
std::chrono::system_clock::time_point Time::updateStart;

void Time::init()
{
	startProgTime = std::chrono::system_clock::now();

	deltaTime = std::chrono::system_clock::now() - startProgTime;
}

void Time::update()
{
	updateStart = std::chrono::system_clock::now();

	nowTime = std::chrono::system_clock::now() - startProgTime;
}


void Time::lastDraw()
{
	auto end = std::chrono::system_clock::now();

	deltaTime = end - updateStart;
	nowTime = std::chrono::system_clock::now() - startProgTime;

}

float Time::GetCurrentTime()
{
	return static_cast<float>(nowTime.count());
}

float Time::GetDeltaTime()
{
	return static_cast<float>(deltaTime.count());
}

