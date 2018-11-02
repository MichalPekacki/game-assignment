#include "Player.h"
#include <iostream>

using namespace std;
using namespace sf;

//creating the player and setting starting position
Player::Player()
{
	playerTexture.loadFromFile("PlayerTexture.png");

	player.setTexture(playerTexture);
	player.setPosition(Vector2f(35, 100));
}


Player::~Player()
{
}

//drawing the player
void Player::draw(sf::RenderWindow &window)
{
	window.draw(player);
}

void Player::update(sf::RenderWindow &window, bool u)
{	
	Time time = clock.getElapsedTime();

	Event event;

	//Update sprite animation
	if (right == false && u == false)
	{
		source.y = UpL;
	}
	if (right == true && u == false)
	{
		source.y = UpR;
	}

	if (u == true)
	{
		if (right == true)
		{
			source.y = Right;
		}
		else
			source.y = Left;
	}

	if (ss.getElapsedTime().asMilliseconds() > 50.f)
	{
		source.x++;
		if (source.x * 32 >= playerTexture.getSize().x)
			source.x = 0;

		ss.restart();
	}

	player.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	//Respawn Timer
	if (respawn == true)
	{
		if (time.asMilliseconds() >= 6000) //Respawn timer set to 6 seconds? i think
		{
			respawn = false;
			clock.restart();
		}
	}
	else
	{
		clock.restart();
	}
}