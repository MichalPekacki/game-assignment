#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Map
{
public:
	Map(const char*filename);
	~Map();

	void draw(sf::RenderWindow &window);

	vector<RectangleShape> platforms;

private:
	std::vector<std::vector<sf::Vector2i>>map; //Map Size put into map variable
	std::vector<sf::Vector2i>tempMap;
	sf::Texture tiletexture;
	sf::Sprite tiles;

};