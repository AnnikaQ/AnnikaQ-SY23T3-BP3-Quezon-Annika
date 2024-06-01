#include "Player.h"
#include "Scene.h"
#include "SoundManager.h"

Player::~Player()
{

	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

void Player::start()
{
	//This is for the ship Player guy
	texture = loadTexture("gfx/player.png");

	//Variables innit?
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8; // 8 frames or 0.13 seconds
	currentReloadTime = 0;

	//Query the texture... sick B)
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");


}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		// Negative going up? Because of the coords. 0 x 0 is top left
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	//DECREMENT THE PLAYER RELOAD TIME WOAHHH
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		//Front Gun
		Bullet* bullet = new Bullet(x + width , y - 2 + height/2  ,1 ,0 ,10 ); 

		bullets.push_back(bullet);
		
		getScene()->addGameObject(bullet);
	
		bullet->start();
	

		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 2)
	{
		//Upper Gun
		Bullet* bullet2 = new Bullet(x + width - 50, y - 30 + height / 2, 1, 0, 10);

		bullets.push_back(bullet2);

		getScene()->addGameObject(bullet2);

		bullet2->start();

	}


	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 3)
	{
		//Lower Gun
		Bullet* bullet3 = new Bullet(x + width - 50, y + 20 + height / 2, 1, 0, 10);


		bullets.push_back(bullet3);


		getScene()->addGameObject(bullet3);


		bullet3->start();
	}
	

	//this deletes the bullets when they go offscreen
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			//Cache the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}


	
}

void Player::draw()
{
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}
