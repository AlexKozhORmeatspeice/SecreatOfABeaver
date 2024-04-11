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
using ComponentArray = std::array<std::shared_ptr<Component>, maxComp>;

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
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update();

	void draw();
	bool isActive() const { return active; }
	void destroy();

	

	template <typename T, typename ... TArgs> 
	T& AddComponent(TArgs&&...mArgs)
	{
		std::shared_ptr<T> c = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
		c.get()->entity = this;

		std::unique_ptr<Component> uPtr{ c.get() };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c.get()->init();

		return *c.get();
	}

	template <typename T> 
	bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	template <typename T> 
	std::shared_ptr<T> GetComponent()
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return std::static_pointer_cast<T>(ptr);
	}

	~Entity();
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update();

	void draw();

	void refresh();

	Entity& addEntity();

	~Manager();
};