#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>; 
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:	
	Entity * entity;
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() {}

};

class Entity
{

private:
	Manager& manager;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitset;
public:
	Entity(Manager& mManager) : manager(mManager){}
bool active = true;
	void Update()
	{
		for (auto& c : components)c->Update();
		
	}
	void Draw() 
	{
		for (auto& c : components)c->Draw();
	}
	bool isActive() const { return active; }
	void Destroy() { active = false; }

	bool HasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}
	void AddGroup(Group mGroup);
	void RemoveGroup(Group mGroup){
		groupBitset[mGroup] = false;
	}

	
	template <typename T> bool HasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		c->Init();
		return *c;
	}


	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};




class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*> , maxGroups> groupedEntites;
public:
	void Update() {
		for (auto& e : entities) e->Update();
	}
	void Draw()
	{
		for (auto& e : entities) e->Draw();
	}

	void refresh()
	{
		for(auto i(0u) ; i < maxGroups ; i++)
		{
			auto& v(groupedEntites[i]);
			v.erase(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity){
					return !mEntity->isActive() || !mEntity->HasGroup(i);
				}),
				std::end(v));
			
			
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity) 
			{
				return !mEntity->isActive();
			}), std::end(entities));
	}
	void AddGroup(Entity* mEntity , Group mGroup)
	{
		groupedEntites[mGroup].emplace_back(mEntity);
	}
	std::vector<Entity*>& GetGroup(Group mGroup)
	{
		return groupedEntites[mGroup];
	}
	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};

