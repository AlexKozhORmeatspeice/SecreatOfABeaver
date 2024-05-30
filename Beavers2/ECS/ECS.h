#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "iostream"

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;

	return lastID++;
}

template <typename T> 
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComp = 32;

using ComponentBitSet = std::bitset<maxComp>;
using ComponentArray = std::array<Component*, maxComp>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void lastUpdate() {}

	virtual void firstDraw() {}
	virtual void draw() {}
	virtual void lastDraw() {}

	virtual ~Component() {}
private:
};


class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update();
	void draw();

	bool isActive() const { return active; }
	void destroy();

	template <typename T, typename ... TArgs> 
	T* AddComponent(TArgs&&...mArgs)
	{
		T* c = new T(std::forward<TArgs>(mArgs)...);
		c->entity = this;

		std::unique_ptr<Component> uPtr{ c };

		components.emplace_back(std::move(uPtr));
		
		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;
		
		c->init();

		return c;
	}

	template <typename T, typename T2>
	T2* AddComponentAsObject(Component* comp)
	{
		comp->entity = this;

		std::unique_ptr<Component> uPtr{ comp };

		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = comp;
		componentBitSet[GetComponentTypeID<T>()] = true;

		comp->init();

		return static_cast<T2*>(comp);
	}


	template <typename T> 
	bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	template <typename T> 
	T* GetComponent()
	{
		if (HasComponent<T>())
		{
			auto ptr(componentArray[GetComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}
		else
		{
			return nullptr;
		}
		
	}

	~Entity();
};

class Manager
{
private:
	static std::vector<std::unique_ptr<Entity>> entities;

public:
	void update();

	void draw();

	static void refresh();

	static Entity& addEntity();

	~Manager();
};