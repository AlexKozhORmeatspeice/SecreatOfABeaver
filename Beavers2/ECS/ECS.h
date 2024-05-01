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
	virtual void draw() {}

	virtual ~Component() {}
private:
};


class Entity
{
private:
	bool active = true;
	std::vector<Component*> components;

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

		components.emplace_back(c);
		
		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;
		
		c->init();

		return c;
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
	static std::vector<Entity*> entities;

public:
	void update();

	void draw();

	void refresh();

	static Entity& addEntity();

	~Manager();
};