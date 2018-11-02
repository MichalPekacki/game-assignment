#include "HUD.h"
#include <iostream>

using namespace std;
using namespace sf;

//loads npc and sets its position
HUD::HUD()
{
	if (!font.loadFromFile("HARLOWSI.ttf"))
	{
		//handle error
	}

	info.setFont(font);
	info.setCharacterSize(15);
	info.setFillColor(sf::Color::Black);

}


HUD::~HUD()
{
}

void HUD::draw(sf::RenderWindow &window)
{
	window.draw(info);
}

void HUD::update(Sprite n, int l)
{
	String slives = to_string(l);
	info.setString(slives);

	//set position of text according to player
	info.setPosition(n.getPosition().x - 2, n.getPosition().y - 15);
}