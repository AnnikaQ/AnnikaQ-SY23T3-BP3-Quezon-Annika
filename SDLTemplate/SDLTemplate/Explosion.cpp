#include "Explosion.h"
#include "Scene.h"
#include "Enemy.h"
#include "SoundManager.h"

Explosion::~Explosion()
{
}

Explosion::Explosion(int x, int y)
{
	this->setPosition(x, y);

}

void Explosion::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

void Explosion::start()
{
	//EXPLOSION MWAHHAHA
	texture = loadTexture("gfx/explosion.png");

	//Variables innit?
	
	width = 96;
	height = 96;
	explosionTimer = 5; // i felt 5 was appropriate
	currentExplosionTimer = 0;

	sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 20;

	//Query the texture... sick B)
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	
}

void Explosion::update()
{
	if (explosionTimer > 0)
	{
		explosionTimer--;
	}
	else
	{
		SoundManager::playSound(sound);
		delete this;
	}
}

void Explosion::draw()
{
	blit(texture, x, y);
}


