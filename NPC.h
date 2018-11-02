#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class NPC
{
public:
	NPC();
	~NPC();

	void update(Sprite n);
	void draw(sf::RenderWindow &window);

	bool questActive = false;
	int rewarded = 0;
	int qProgress = 0;

private:
	Sprite npc;
	Texture npcTexture;

	//quest requirements
	bool questFinished = false;

	enum Direction{ Left, Right };
	Vector2i source;

	Font font;
	Text speech[5];
	int tNum; //text identification number

	Clock ss;

};