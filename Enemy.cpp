#include "Enemy.h"
#include <iostream>

using namespace std;
using namespace sf;

////////////////////////////////////////
////loads enemies in random position
////////////////////////////////////////
Enemy::Enemy()
{
	enemyTexture.loadFromFile("EnemyTexture.png");

	//enemy positions
	Vector2f i = Vector2f(320, 192);
	location.push_back(i);
	i = Vector2f(400, 192);
	location.push_back(i);
	i = Vector2f(740, 192);
	location.push_back(i);
	i = Vector2f(1012, 287);
	location.push_back(i);
	i = Vector2f(1522, 287);
	location.push_back(i);
}


Enemy::~Enemy()
{
}

////////////////////////////////////////
////Draws all enemies to the screen
////////////////////////////////////////
void Enemy::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < enemyNum; i++)
	{
		window.draw(enemy[i]);
	}
}

void Enemy::update()
{
	Time time = clock.getElapsedTime();
	Time t = c.getElapsedTime();
	c.restart();
	
	if (time.asMilliseconds() >= 1000) //Time based direction change
	{
		moveSpeed = moveSpeed * (-1);
		clock.restart();
	}
	//sets each enemy's velocity to movement speed
	velocity.x = moveSpeed * t.asMilliseconds();

	//setting each enemy's movement to velocity(required for movement/ speed can be changed in header file in moveSpeed)
	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i].move(velocity.x, velocity.y);
	}

	//Texture +spritesheet
	if (velocity.x > 0)
		source.y = Right;
	else
		source.y = Left;

	if (ss.getElapsedTime().asMilliseconds() > 50.f)
	{
		source.x++;
		if (source.x * 32 >= enemyTexture.getSize().x)
			source.x = 0;

		ss.restart();
	}

	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i].setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
	}

	//spawn enemies every time enemy number goes equal to or below 0
	if (enemyNum <= 0)
	{
		enemyNum = 5;
		for (int i = 0; i < enemyNum; i++)
		{
			Sprite e;

			e.setTexture(enemyTexture);
			e.setPosition(location[i]);

			enemy.push_back(e);
		}
	}
}