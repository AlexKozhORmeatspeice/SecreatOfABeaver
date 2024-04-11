#include "System.h"

bool GameInit()
{
	return true;
}

bool GameIter(std::unique_ptr<Manager> & manager)
{
	manager->update();

	return true;
}

void GameStop()
{

}