#include "Player.h"

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

	//Query the texture... sick B)
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


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
}

void Player::draw()
{
	blit(texture, x, y);
}
