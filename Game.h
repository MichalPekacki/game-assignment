#include <SFML/Graphics.hpp>

class Menu;
class Player;
class NPC;
class Shooting;
class Enemy;
class Map;
class HUD;
class Inventory;

using namespace std;
using namespace sf;

class Game
{
public:
	void runGameLoop();

private:
	void initialise();
	void loadContent();
	void update();
	void input();
	void collision();
	void endCondition();
	void drawEndGame();
	void display();
	void menu();

private:
	RenderWindow _window;
	View view;
	Vector2f cameraPosition;
	Vector2i screenDimensions;

	bool lose;
	bool win;
	RectangleShape fin;
	Sprite gameWin;
	Sprite gameOver;
	Texture gwTexture;
	Texture goTexture;
	Clock eg;

	Menu *_menu;
	Player *_player;
	NPC *_npc;
	Shooting *_bullets;
	Enemy *_enemy;
	Map *_map;
	HUD *_hud;
	Inventory *_inventory;

	Time time;
	bool onP;
	Vector2f velocity;

};