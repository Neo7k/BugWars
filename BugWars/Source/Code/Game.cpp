#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
}

Game::~Game()
{
	for (auto obj : objects)
		delete obj;
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (int i = 0; i < objects.size(); i++)
		if (!objects[i]->disabled)
		{
			objects[i]->Update(dt);
		}
		else
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (!obj->disabled)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
}

void Game::OnBugsSpawned()
{
}
