#pragma once
#include "ECS.h"

class SavebleObj
{
public:
	virtual void SaveData() {};
	virtual void LoadData() {};

	SavebleObj();
	~SavebleObj();
};