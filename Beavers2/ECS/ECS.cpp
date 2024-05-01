#include "ECS.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Entity::update()
{
	for (auto& c : components) c->update();
}

void Entity::draw()
{
	for (auto& c : components) c->draw();
}

void Entity::destroy() { active = false; }


Entity::~Entity()
{
	for (auto& c : components)
	{
		delete c;
	}
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
			[](Entity* mEntity) { return  (mEntity == nullptr || !mEntity->isActive()); }),
		entities.end()
	);
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity();
	entities.emplace_back(e);

	return *e;
}

Manager::~Manager()
{		
	for (auto entity : entities)
	{
		delete entity;
	}
}
