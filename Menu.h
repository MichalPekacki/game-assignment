#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

#define MAX_NUMBER_OF_ITEMS 3
class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

	void choose(sf::RenderWindow &window);
	void controls();
	bool menuScreen = true;
	bool controlScreen = false;

private:
	Sprite c;
	Texture cTexture;

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
