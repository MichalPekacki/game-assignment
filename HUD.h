#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class HUD
{
public:
	HUD();
	~HUD();

	void update(Sprite n, int l);
	void draw(sf::RenderWindow &window);

private:
	Font font;
	Text info;

};