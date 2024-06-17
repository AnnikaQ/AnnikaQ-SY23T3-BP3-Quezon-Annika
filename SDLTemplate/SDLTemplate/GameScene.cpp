#include "GameScene.h"
#include "Explosion.h"
#include "SoundManager.h"



GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
	backgroundTexture = nullptr;

}

GameScene::~GameScene()
{
	delete player;

	if (backgroundTexture) {
		SDL_DestroyTexture(backgroundTexture); 
	}
	
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300; //spawn time of 5 seconds

	SDL_Surface* backgroundSurface = IMG_Load("gfx/background.png");
	if (backgroundSurface) {
		backgroundTexture = SDL_CreateTextureFromSurface(app.renderer, backgroundSurface);
		SDL_FreeSurface(backgroundSurface);
	}

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}

	
}

void GameScene::draw()
{

	SDL_RenderClear(app.renderer);

	
	if (backgroundTexture) {
		SDL_RenderCopy(app.renderer, backgroundTexture, NULL, NULL);
	}

	Scene::draw();

	drawText(370, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(370, 370, 255, 255, 255, TEXT_CENTER, "GAMEOVER!!");
	}

	SDL_RenderPresent(app.renderer);
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
						points++;
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

	enemy->setPosition(100 + (rand() % 450), 100);
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

		Explosion* explosion = new Explosion(enemy->getPositionX(), enemy->getPositionY());
		this->addGameObject(explosion);
		delete enemy;
	}
}


