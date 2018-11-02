#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void update();
	void draw(sf::RenderWindow &window);

	vector<Sprite> enemy;

	//number of enemies
	int enemyNum = 0;

private:
	Texture enemyTexture;

	//enemy speed
	float moveSpeed = 0.06f;
	Vector2f velocity = (Vector2f(0.f, 0.f));
	vector<Vector2f> location;

	enum Direction{ Left, Right };
	Vector2i source;

	Clock clock;
	Clock c;
	Clock ss;
};