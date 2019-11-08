#include "Power.h"
#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
	N = true;
}


GameObjectManager::~GameObjectManager()
{
	while (gameObjects.size() > 0)
	{
		GameObject* go = null;
		go = gameObjects[gameObjects.size() - 1];
		gameObjects.pop_back();
		if (go != null)
		{
			delete go;
		}
	}
}

void GameObjectManager::Update(double deltaTime)
{
	UpdateGameObjects(deltaTime);
}

void GameObjectManager::UpdateGameObjects(double deltaTime)
{
	

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == null || gameObjects[i]->getState() == EDead)
		{
			GameObject* delGo = gameObjects[i];
			gameObjects.erase(gameObjects.begin() + i);
			delete delGo;
			i--;
		}
		else if (gameObjects[i]->getState() == EActive)
		{
			gameObjects[i]->Update(deltaTime);
		}
	}
}

void GameObjectManager::addGameObject(GameObject* obj)
{
	gameObjects.push_back(obj);
	Log("Added GameObject");
}
