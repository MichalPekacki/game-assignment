#include "Shooting.h"
#include <iostream>

using namespace std;
using namespace sf;

//only textures the bullets
Shooting::Shooting()
{
	bulletsTexture.loadFromFile("Bullet.png");
}


Shooting::~Shooting()
{
}

//draws every bullet to screen
void Shooting::draw(RenderWindow &window)
{
	for (int i = 0; i < bulletAmount; i++)
	{
		window.draw(bullets[i]);
	}
}

void Shooting::update(Sprite n)
{
	Time time = clock.getElapsedTime();
	t = c.restart();

	//sets which direction player is facing
	if (Keyboard::isKeyPressed(Keyboard::Right)){
		faceR = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)){
		faceR = false;
	}

	//Shooting
	if (time.asMilliseconds() >= hipfire) //Time delay for bullet spawn
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			bulletAmount = bulletAmount + 1;

			//Create a bullet
			Sprite bullet;
			bullet.setPosition(Vector2f(n.getPosition().x, n.getPosition().y));//better bullet positionsing when we have graphics
			bullet.setTexture(bulletsTexture);

			//Create corresponding direction using a vector
			int i;
			if (faceR == true)
			{
				i = 1;
			}
			else if (faceR == false)
			{
				i = 2;
			}

			//stores bullet in bullets vector
			bullets.push_back(bullet);
			bulletDirection.push_back(i);

			clock.restart();
		}
	}

	//Update Bullet Movement
	for (int i = 0; i < bulletAmount; i++)
	{
		if (bulletDirection[i] == 1)
		{
			bullets[i].move(bulletSpeed * t.asSeconds(), 0.f);
		}
		else if (bulletDirection[i] == 2)
		{
			bullets[i].move(-bulletSpeed * t.asSeconds(), 0.f);
		}
	}

	//getting bullet type
	switch (ttype)
	{
	case(0):
	{
		hipfire = 400;
		break;
	}
	case(1):
	{
		hipfire = 200;
		break;
	}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		ttype = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		ttype = 1;
	}
}