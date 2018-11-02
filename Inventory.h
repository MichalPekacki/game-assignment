#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void update(Vector2f c);
	void draw(sf::RenderWindow &window);

private:
	Font font;
	Text inventory[2];

	int hlocation = 80.f;

	RectangleShape highlight;
};