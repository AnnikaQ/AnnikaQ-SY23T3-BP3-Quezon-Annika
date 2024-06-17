#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	
}

void Enemy::start()
{
	//This is for the enemy GRRR >:(
	texture = loadTexture("gfx/enemy.png");

	//Variables innit?
	directionX = -1;
	directionY = 1;

	width = 0;
	height = 0;
	speed = 2;

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 40;


	reloadTime = 60;// 60 frames for 1 seconds
	currentReloadTime = 0;

	directionChangeTime = (rand() % 300) + 180; // 3 to 8 seconds
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime == 0)
	{
		float dx = 0;
		float dy = 1;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);


		SoundManager::playSound(sound);
	
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2,dx,dy,10, Side::ENEMY_SIDE);

		//for deletion
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);


		// reset timer
		currentReloadTime = reloadTime;
	}

	//this deletes the bullets when they go offscreen
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			//Cache the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}

}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{

	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
