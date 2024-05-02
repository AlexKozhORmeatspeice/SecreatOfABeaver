#include "ECS.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::update()
{
	for (auto& c : components) c->update();
	for (auto& c : components) c->lastUpdate();
}

void Entity::draw()
{
	for (auto& c : components) c->draw();
	for (auto& c : components) c->lastDraw();
}

void Entity::destroy() 
{ 
	active = false; 
}


Entity::~Entity()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Entity*> Manager::entities;
void Manager::update()
{
	for (auto& e : entities) e->update();
}

void Manager::draw()
{
	for (auto& e : entities) e->draw();
}

void Manager::refresh()
{
	entities.erase(
		std::remove_if(std::begin(entities),
			std::end(entities),
			[](Entity* mEntity) { return (!mEntity->isActive()); }),
		entities.end()
	);
}

Entity& Manager::addEntity()
{
	Entity* entity = new Entity();
	
	entities.emplace_back(entity);

	return *entity;
}

Manager::~Manager()
{		
}
