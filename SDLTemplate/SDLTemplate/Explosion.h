#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"

class Explosion :public GameObject
{
public:
	~Explosion();
	Explosion(int x, int y);
	void setPosition(int xPos, int yPos);

	void start();
	void update();
	void draw();


private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;
	int width;
	int height;
	float explosionTimer;
	float currentExplosionTimer;
};

