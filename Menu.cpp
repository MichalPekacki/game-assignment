#include "Menu.h"
#include "Game.h"
#include <iostream>

using namespace std;
using namespace sf;

Menu::Menu(float width, float height)
{
	cTexture.loadFromFile("Controls.png");
	c.setTexture(cTexture);
	
	if (!font.loadFromFile("HARLOWSI.ttf"))
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Controls");
	menu[1].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;

}


Menu::~Menu()
{
}

void Menu::controls()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)){
		controlScreen = false;
		menuScreen = true;
	}
}

void Menu::draw(sf::RenderWindow &window)
{
	if (menuScreen == true)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
	}
	if (controlScreen == true)
	{
		window.draw(c);
		controls();
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);

	}
}

void Menu::choose(sf::RenderWindow &window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;

			case sf::Keyboard::Return:

				switch (GetPressedItem())
				{
				case 0:
					menuScreen = false;
					break;
				case 1:
					menuScreen = false;
					controlScreen = true;
					break;
				case 2:
					if (menuScreen == true)
					{
						window.close();
						break;
					}
				}


				break;

			}

			break;

		}
	}
}