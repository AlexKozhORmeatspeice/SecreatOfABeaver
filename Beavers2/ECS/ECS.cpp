#include "ECS.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::update()
{
	for (auto& c : components) c->update();
	for (auto& c : components) c->lastUpdate();
}

void Entity::draw()
{
	for (auto& c : components) c->firstDraw();
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
std::vector<std::unique_ptr<Entity>> Manager::entities;
void Manager::update()
{
	for (const auto& e : entities) e->update();
}

void Manager::draw()
{
	for (const auto& e : entities) e->draw();
}

void Manager::refresh()
{
	entities.erase(
		std::remove_if(std::begin(entities),
			std::end(entities),
			[](std::unique_ptr<Entity>& mEntity) { return (!mEntity->isActive()); }),
		entities.end()
	);
}

Entity& Manager::addEntity()
{
	Entity* entity = new Entity();
	
	std::unique_ptr<Entity> uPtr{ entity };

	entities.emplace_back(std::move(uPtr));

	return *entity;
}

Manager::~Manager()
{		
	for (auto& entity : entities)
	{
		entity.reset();
	}
}
