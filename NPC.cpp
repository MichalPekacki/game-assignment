#include "NPC.h"
#include <iostream>

using namespace std;
using namespace sf;

//loads npc and sets its position
NPC::NPC()
{
	npcTexture.loadFromFile("NpcTexture.png");
	npc.setTexture(npcTexture);
	npc.setPosition(175, 256);

	if (!font.loadFromFile("HARLOWSI.ttf"))
	{
		//handle error
	}

	speech[0].setFont(font);
	speech[0].setCharacterSize(17);
	speech[0].setFillColor(sf::Color::Black);
	speech[0].setString("'Press F to interact'");

	speech[1].setFont(font);
	speech[1].setCharacterSize(17);
	speech[1].setFillColor(sf::Color::Black);
	speech[1].setString("Hello, if you kill 3 enemies I will reward you. ( press Y/N )");

	speech[2].setFont(font);
	speech[2].setCharacterSize(17);
	speech[2].setFillColor(sf::Color::Black);
	speech[2].setString("That's fantastic, come back for your reward when you are finished.");

	speech[3].setFont(font);
	speech[3].setCharacterSize(17);
	speech[3].setFillColor(sf::Color::Black);
	speech[3].setString("That's a shame, but if you ever change your mind be sure to see me again.");

	speech[4].setFont(font);
	speech[4].setCharacterSize(17);
	speech[4].setFillColor(sf::Color::Black);
	speech[4].setString("Ah, I'm glad to see you back. Here is your reward.");

}


NPC::~NPC()
{
}

//draws npc
void NPC::draw(sf::RenderWindow &window)
{
	window.draw(npc);

	if (tNum == 1)
	{
		window.draw(speech[0]);
	}
	if (tNum == 2)
	{
		window.draw(speech[1]);
	}
	if (tNum == 3)
	{
		window.draw(speech[2]);
	}
	if (tNum == 4)
	{
		window.draw(speech[3]);
	}
	if (tNum == 5)
	{
		window.draw(speech[4]);
	}
}

void NPC::update(Sprite n)
{
	//Texture + spritesheet
	if (n.getPosition().x > npc.getPosition().x)
		source.y = Right;
	else
		source.y = Left;
	
	if (ss.getElapsedTime().asMilliseconds() > 50.f)
	{
		source.x++;
		if (source.x * 32 >= npcTexture.getSize().x)
			source.x = 0;

		ss.restart();
	}

	npc.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
	
	//if player collides with npc
	if (n.getGlobalBounds().intersects(npc.getGlobalBounds()) && questActive == false && rewarded == 0)
	{
		if (tNum != 2 && tNum != 3 && tNum != 4)
		{
			tNum = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			tNum = 2;
			//if quest is finished but player hasnt been rewarded, reward the player
			if (questFinished == true && rewarded == 0)
			{
				tNum = 5;
				rewarded = 1;
			}
		}
		if (tNum == 2)
		{
			//if quest hasnt been finished and isnt active you can accept its quest
			if (questFinished == false && questActive == false)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
				{
					tNum = 3;
					questActive = true;
				}
				//you can decline to activate quest
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					tNum = 4;
				}
			}
		}
	}
	else if (!n.getGlobalBounds().intersects(npc.getGlobalBounds()))
	{
		tNum = 0;
	}

	//quest goal, what player needs to do to finish the quest
	if (questActive == true)
	{
		if (qProgress == 3)
		{
			questFinished = true;
			questActive = false;
		}
	}

	//set position of text according to player
	speech[0].setPosition(npc.getPosition().x - 100, 425);
	speech[1].setPosition(npc.getPosition().x - 100, 425);
	speech[2].setPosition(npc.getPosition().x - 100, 425);
	speech[3].setPosition(npc.getPosition().x - 100, 425);
	speech[4].setPosition(npc.getPosition().x - 100, 425);
}