#include "SavebleObj.h"
#include "SaveManager.h"

SavebleObj::SavebleObj()
{
	SaveManager::AddObj(this);
}

SavebleObj::~SavebleObj()
{
	SaveManager::DeleteObj(this);
}