#include "SaveManager.h"


std::vector <SavebleObj*> SaveManager::objs;
const std::string SaveManager::nameOfFile = "Data.txt";

void SaveManager::LoadData()
{
	for (auto obj : objs)
	{
		obj->LoadData();
	}
}
void SaveManager::SaveData()
{
	for (auto obj : objs)
	{
		obj->SaveData();
	}
}

void SaveManager::DeleteObj(SavebleObj* obj)
{
	auto it = std::find(objs.begin(), objs.end(), obj);
	if (it != objs.end())
	{
		objs.erase(it);
	}

}
void SaveManager::AddObj(SavebleObj* obj)
{
	objs.push_back(obj);
}

void SaveManager::ClearData()
{
	std::ofstream out;
	out.open(SaveManager::nameOfFile, std::ofstream::out);
	if(out.is_open())
		out << "";
	
	out.close();
}