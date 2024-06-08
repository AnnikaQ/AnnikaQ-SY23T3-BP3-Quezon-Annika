#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawnTimer = 300;
	spawnTime = 300; //spawn time of 5 seconds

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}

	
	
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	
	checkSpawn();
	doCheckCollision();
	
	
}

void GameScene::checkSpawn()
{

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}

		currentSpawnTimer = spawnTime;
	}
}

void GameScene::doCheckCollision()
{

	for (int i = 0; i < objects.size(); i++)
	{
		//CAST TO BULLET. C++ function, attempts to cast the object to the class type we want it to be
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//Check if cast was successful 

		if (bullet != NULL)
		{
			// If the bullet collides with the enemy
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			// If the bullet collides with the Player, check against THE GIANT ENEMY SPIDER (not really)
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{

				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						despawnEnemy(currentEnemy);
						// IF YOU DON'T DESPAWN YOU DIE OUGH
						break;
					}


				}
			}
		}
	}
}

void GameScene::spawn()
{
	enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1260, 200 + (rand() % 250));
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}
