#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class GameObject;

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID()
{
	static ComponentTypeID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentTypeID getComponentTypeID() noexcept
{
	static ComponentTypeID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	Component(){}
	Component(GameObject* owner) { Owner = owner; }
	GameObject* Owner;

	virtual void Init() {}
	virtual void Update(double deltaTime) {}

	virtual ~Component() {}
};
#endif


#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;

enum goState { EActive, EPaused, EDead };

class GameObject
{
public:
	GameObject() {	state = EActive;}
	~GameObject() {}

	void Destroy()  { state = EDead; Log("GameObject Destroyed"); }
	void Pause()	{ state = EPaused; }
	void Activate() { state = EActive; }

	goState getState() const { return state; }

	void Update(double deltaTime){
		if (state == EActive) { updateComponents(deltaTime); }
	}

	void updateComponents(double deltaTime) {
		for (auto& comp : Components) { comp->Update(deltaTime); }
	}

	template<typename T> bool hasComponent() {
		return ComponentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* comp(new T(std::forward<TArgs>(mArgs)...));
		comp->Owner = this;
		std::unique_ptr<Component> uPtr{ comp };
		Components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = comp;
		componentBitSet[getComponentTypeID<T>()] = true;

		comp->Init();
		return *comp;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	string Tag = "";

protected:
	std::vector<std::unique_ptr<Component>> Components;
	goState state;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};
#endif