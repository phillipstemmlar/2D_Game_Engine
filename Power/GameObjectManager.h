#pragma once

#ifndef GO_MANAGER_H
#define GO_MANAGER_H

#include "Power.h"

class GameObject;

class GameObjectManager
{
private:
	std::vector<GameObject*> gameObjects;
	bool N;
protected:
	void UpdateGameObjects(double deltaTime);

public:
	GameObjectManager();
	~GameObjectManager();

	void Update(double deltaTime);
	void addGameObject(GameObject* obj);
	//remove GameObject by calling go.Destroy();
};

#endif