#include "Inventory.h"
#include <iostream>

using namespace std;
using namespace sf;

//loads npc and sets its position
Inventory::Inventory()
{
	if (!font.loadFromFile("HARLOWSI.ttf"))
	{
		//handle error
	}

	inventory[0].setFont(font);
	inventory[0].setCharacterSize(20);
	inventory[0].setFillColor(sf::Color::Black);
	inventory[0].setString("400");

	inventory[1].setFont(font);
	inventory[1].setCharacterSize(20);
	inventory[1].setFillColor(sf::Color::Black);
	inventory[1].setString("200");

	highlight.setFillColor(Color::Red);
	highlight.setSize(Vector2f(33.f, 25.f));

}


Inventory::~Inventory()
{
}

void Inventory::draw(sf::RenderWindow &window)
{
	window.draw(highlight);
	for (int i = 0; i < 2; i++)
	{
		window.draw(inventory[i]);
	}
}

void Inventory::update(Vector2f c)
{
	//set position of inventory
	inventory[0].setPosition(c.x + 600, 80.f);
	inventory[1].setPosition(c.x + 600, 110.f);
	highlight.setPosition(c.x + 600, hlocation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		hlocation = 80.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		hlocation = 110.f;
	}
}