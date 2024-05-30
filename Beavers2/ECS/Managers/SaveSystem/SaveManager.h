#pragma once
#include "ECS.h"
#include "SavebleObj.h"
#include "fstream"

class SaveManager : public Component
{
private:
	static std::vector <SavebleObj*> objs;
	
public:
	static const std::string nameOfFile;
	static void LoadData();
	static void SaveData();

	static void DeleteObj(SavebleObj* obj);
	static void AddObj(SavebleObj* obj);

	static void ClearData();


};