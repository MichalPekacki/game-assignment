#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Player
{
public:
	Player();
	~Player();

	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window, bool u);

	Sprite player;

	//number of lives, respawn boolean for enemy hit delay after respawning
	int lives = 3;
	bool respawn = false;
	bool right = true;

private:
	Texture playerTexture;

	enum Direction{ Left, Right, UpL, UpR };
	Vector2i source;

	Clock clock;
	Clock ss;
};