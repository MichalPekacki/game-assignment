#include "Map.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;
using namespace sf;

Map::Map(const char*filename)
{
	std::ifstream openfile(filename); //Open the map text file
	tempMap.clear();
	map.clear();

	if (openfile.is_open())
	{
		std::string tileLocation;
		openfile >> tileLocation;
		tiletexture.loadFromFile(tileLocation);
		tiles.setTexture(tiletexture);
		while (!openfile.eof())
		{
			std::string str, value;
			std::getline(openfile, str);
			std::stringstream stream(str); //Store the str value (the text file line) in stream


			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					std::string xx = value.substr(0, value.find(',')); //Get the value before comma
					std::string yy = value.substr(value.find(',') + 1); //Get value after comma before space

					int x, y, i, j;

					for (i = 0; i < xx.length(); i++)
					{
						if (!isdigit(xx[i]))
							break;
					}

					for (j = 0; j < yy.length(); j++)
					{
						if (!isdigit(yy[j]))
							break;
					}

					x = (i == xx.length()) ? atoi(xx.c_str()) : -1; //convert string to int, if not equal set to -1
					y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

					tempMap.push_back(sf::Vector2i(x, y));
				}
			}

			map.push_back(tempMap);
			tempMap.clear();
		}
	}

	//Collition platform create
	for (int i = 0; i < 11; i++)
	{
		RectangleShape r;
		r.setFillColor(Color::Black);
		platforms.push_back(r);
	}

	//Collision platfrom position + size
	platforms[0].setPosition(Vector2f(33.f, 290.f));
	platforms[0].setSize(Vector2f(190.f, 10.f));
	platforms[1].setPosition(Vector2f(257.f, 226.f));
	platforms[1].setSize(Vector2f(190.f, 10.f));
	platforms[2].setPosition(Vector2f(642.f, 226.f));
	platforms[2].setSize(Vector2f(190.f, 10.f));
	platforms[3].setPosition(Vector2f(897.f, 322.f));
	platforms[3].setSize(Vector2f(190.f, 10.f));
	platforms[4].setPosition(Vector2f(1441.f, 322.f));
	platforms[4].setSize(Vector2f(190.f, 10.f));
	//bridge
	platforms[5].setPosition(Vector2f(447.f, 226.f));
	platforms[5].setRotation(36.f);
	platforms[5].setSize(Vector2f(85.f, 10.f));
	platforms[6].setPosition(Vector2f(517.f, 274.f));
	platforms[6].setSize(Vector2f(65.f, 10.f));
	platforms[7].setPosition(Vector2f(582.f, 274.f));
	platforms[7].setRotation(-36.f);
	platforms[7].setSize(Vector2f(85.f, 10.f));
	//small platforms
	platforms[8].setPosition(Vector2f(1152.f, 322.f));
	platforms[8].setSize(Vector2f(33.f, 10.f));
	platforms[9].setPosition(Vector2f(1248.f, 322.f));
	platforms[9].setSize(Vector2f(33.f, 10.f));
	platforms[10].setPosition(Vector2f(1344.f, 322.f));
	platforms[10].setSize(Vector2f(33.f, 10.f));
}


Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				tiles.setPosition(j * 32, i * 32); //Set position of tiles (32 pixels)
				tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
				window.draw(tiles);
			}
		}
	}

	//platforms for collision
	/*for (int i = 0; i < platforms.size(); i++)
	{
		window.draw(platforms[i]);
	}*/
}