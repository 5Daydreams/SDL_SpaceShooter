#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	std::cout << "Component ID: " << lastID << std::endl;
	return lastID++;
}

template<typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
private:

	bool active = true;
	std::vector<std::unique_ptr<Component>> componentsList;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;

public:
	void Update()
	{
		for (std::unique_ptr<Component>& component : componentsList)
		{
			component->Update();
		}
	}

	void Draw()
	{
		for (std::unique_ptr<Component>& component : componentsList)
		{
			component->Draw();
		}
	}

	bool IsActive() const { return active; }

	void Destroy()
	{
		active = false;
	}

	template <typename T> bool HasComponent() const
	{
		return componentBitset[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs)
	{
		T* component(new T(std::forward<TArgs>(mArgs)...));
		component->entity = this;
		std::unique_ptr<Component> uPtr{ component };
		componentsList.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = component;
		componentBitset[GetComponentTypeID<T>()] = true;

		component->Init();
		return *component;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};


class ECSManager
{
private:
	std::vector<std::unique_ptr<Entity>> entitiesList;

public:
	void Update()
	{
		for (std::unique_ptr<Entity>& entity : entitiesList)
		{
			entity->Update();
		}
	}

	void Draw()
	{
		for (std::unique_ptr<Entity>& entity : entitiesList)
		{
			entity->Draw();
		}
	}

	void Refresh()
	{
		entitiesList.erase(
			std::remove_if(std::begin(entitiesList),
				std::end(entitiesList),
				[](const std::unique_ptr<Entity>& mEntity)
				{
					return !mEntity->IsActive();
				}),
			std::end(entitiesList));
	}

	Entity& AddEntity()
	{
		Entity* entity = new Entity();
		std::unique_ptr<Entity> uPtr{ entity };

		entitiesList.emplace_back(std::move(uPtr));

		return *entity;
	}

	int GetCount()
	{
		return entitiesList.size();
	}
};
