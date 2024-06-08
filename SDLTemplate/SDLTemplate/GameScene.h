#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "init.h"
#include "draw.h"


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	//Enemy spawning logic

	float spawnTime;
	float currentSpawnTimer;

	std::vector < Enemy*> spawnedEnemies;

	void checkSpawn();
	void doCheckCollision();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;

	SDL_Texture* backgroundTexture;
};

