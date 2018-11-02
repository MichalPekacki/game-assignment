#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Player.h"
#include "NPC.h"
#include "Shooting.h"
#include "Enemy.h"
#include "Map.h"
#include "HUD.h"
#include "Inventory.h"

using namespace std;
using namespace sf;

////////////////////////////////////////
////initializes window(size to be changed)
////////////////////////////////////////
void Game::initialise() //Set up the game window
{
	this->screenDimensions = Vector2i(640, 480);
	this->cameraPosition = Vector2f(0, 0);
	
	this->_window.create(VideoMode(this->screenDimensions.x, this->screenDimensions.y), "Game");
	this->view.reset(FloatRect(0, 0, this->screenDimensions.x, this->screenDimensions.y));
	this->view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
}

////////////////////////////////////////
////creates instances of classes in game
////////////////////////////////////////
void Game::loadContent()
{
	this->_menu = new Menu(this->_window.getSize().x, this->_window.getSize().y);
	this->_player = new Player();
	this->_npc = new NPC();
	this->_bullets = new Shooting();
	this->_enemy = new Enemy();
	this->_map = new Map("Map.txt");
	this->_hud = new HUD();
	this->_inventory = new Inventory();

	this->fin.setSize(Vector2f(500.f, 5.f));
	this->fin.setPosition(1600, 0);

	this->gwTexture.loadFromFile("GameWin.png");
	this->goTexture.loadFromFile("GameOver.png");
	this->gameWin.setTexture(gwTexture);
	this->gameOver.setTexture(goTexture);

	this->onP = false;
	this->win = false;
	this->lose = false;
	this->velocity = (Vector2f(0.f, 0.f));
}

////////////////////////////////////////
////calls all update functions from classes
////////////////////////////////////////
void Game::update()
{
	this->_player->update(this->_window, this->onP);
	this->_npc->update(this->_player->player);
	this->_bullets->update(this->_player->player);
	this->_enemy->update();
	this->_hud->update(this->_player->player, this->_player->lives);
	this->_inventory->update(this->cameraPosition);

	//Camera update to follow player
	this->cameraPosition.x = this->_player->player.getPosition().x + 10 - (this->screenDimensions.x / 2);
	this->cameraPosition.y = this->_player->player.getPosition().y + 10 - (this->screenDimensions.y / 2);
	
	if (this->cameraPosition.x < 0)
		this->cameraPosition.x = 0;
	if (this->cameraPosition.y < 0)
		this->cameraPosition.y = 0;

	view.reset(FloatRect(this->cameraPosition.x, this->cameraPosition.y, this->screenDimensions.x, this->screenDimensions.y));

	this->_window.setView(this->view);

	//quest reward
	if (this->_npc->rewarded == 1)
	{
		this->_player->lives = this->_player->lives + 2;
		this->_npc->rewarded = 2;
	}

	//Player movement set to velocity
	this->_player->player.move(this->velocity.x, this->velocity.y);
}
////////////////////////////////////////
////Handle player input
////////////////////////////////////////
void Game::input()
{
	Event event;
	
	//Update sprite animation
	if (Keyboard::isKeyPressed(Keyboard::Right)){
		this->velocity.x = 100.f * this->time.asSeconds();
		this->_player->right = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)){
		this->velocity.x = -100.f * this->time.asSeconds();
		this->_player->right = false;
	}
	else
		this->velocity.x = 0;

	//Jumping input
	while (this->_window.pollEvent(event)){
		if (event.type == Event::KeyReleased && this->onP == true){
			if (event.key.code == Keyboard::Up){
				this->onP == false;
				this->velocity.y = -150.f * this->time.asSeconds();
				cout << velocity.y << endl;
				cout << this->_player->player.getPosition().y << endl;
			}
		}
	}
}

////////////////////////////////////////
////checks for collision
////////////////////////////////////////
void Game::collision()
{
	//gravity
	if (this->onP == false)
	{
		this->velocity.y += 0.5f * this->time.asSeconds();
	}

	//bullet-enemy
	for (int i = 0; i < this->_bullets->bulletAmount; i++)
	{
		for (int j = 0; j < this->_enemy->enemyNum; j++)
		{
			//Checks for callision between every bullet and enemy
			if (this->_bullets->bullets[i].getGlobalBounds().intersects(this->_enemy->enemy[j].getGlobalBounds()))
			{
				//deletes enemy and b ullet which collided
				this->_bullets->bullets.erase(this->_bullets->bullets.begin() + i);
				this->_enemy->enemy.erase(this->_enemy->enemy.begin() + j);
				this->_bullets->bulletDirection.erase(this->_bullets->bulletDirection.begin() + i);
				this->_bullets->bulletAmount = this->_bullets->bulletAmount - 1;
				this->_enemy->enemyNum = this->_enemy->enemyNum - 1;

				//quest update
				if (this->_npc->questActive == true)
				{
					this->_npc->qProgress = this->_npc->qProgress + 1;
				}

				break;
			}
		}
	}

	//player-enemy
	for (int i = 0; i < this->_enemy->enemyNum; i++)
	{
		//check for player colliding with every enemy
		if (this->_player->player.getGlobalBounds().intersects(this->_enemy->enemy[i].getGlobalBounds()) && this->_player->respawn == false)
		{
			//accesses player veriable (lives) and take one away
			this->_player->lives = this->_player->lives - 1;
			//A timer within player classes stops player-enemy collision for limited time
			this->_player->respawn = true;
		}
	}

	//player-platform
	int count = 0;
	for (int i = 0; i < this->_map->platforms.size(); i++)
	{
		if (this->_player->player.getGlobalBounds().intersects(this->_map->platforms[i].getGlobalBounds()))
		{
			this->onP = true;
			this->velocity.y = 0;
		}
		else
			count++;
	}
	if (count == this->_map->platforms.size())
		this->onP = false;
}

////////////////////////////////////////
////End Game
////////////////////////////////////////
void Game::endCondition()
{
	if (this->_player->player.getPosition().x > fin.getPosition().x)
	{
		this->win = true; //winning at end of screen
	}

	//Map fall if player falls of bottom lives = 0
	if (this->_player->player.getPosition().y > this->_window.getSize().y)
	{
		this->_player->lives = 0;
	}

	if (this->_player->lives <= 0)
	{
		this->lose = true; //game over
	}
}

void Game::drawEndGame()
{
	this->gameWin.setPosition(this->cameraPosition);
	this->gameOver.setPosition(this->cameraPosition);
	
	this->_window.clear();

	if (this->win == true)
		this->_window.draw(this->gameWin);
	if (this->lose == true)
		this->_window.draw(this->gameOver);

	this->_window.display();

	if (this->eg.getElapsedTime().asMilliseconds() > 3000.f)
	{
		this->_window.close();
	}
}

////////////////////////////////////////
////Calls functions from classes to draw their objects on the screen
////////////////////////////////////////
void Game::display()
{
	this->_window.clear(Color(85, 180, 255));

	this->_map->draw(this->_window);
	this->_npc->draw(this->_window);
	this->_bullets->draw(this->_window);
	this->_enemy->draw(this->_window);
	this->_player->draw(this->_window);
	this->_hud->draw(this->_window);
	this->_inventory->draw(this->_window);

	this->_window.display();
}

////////////////////////////////////////
////Calls the menu class to draw the menu and let player choose an option
////////////////////////////////////////
void Game::menu()
{
	this->_menu->choose(this->_window);

	this->_window.clear();
	this->_menu->draw(this->_window);
	this->_window.display();
}

////////////////////////////////////////
////main game loop sets up window in initialise and loads contents(player etc) then goes to loop
////calling updates from classes in update, checks for collision(in progress), checks for lives = 0 and displays content
////////////////////////////////////////
void Game::runGameLoop()
{
	this->initialise();
	this->loadContent();

	sf::Clock tclock;
	sf::Time tprevtime = tclock.restart();

	while (this->_window.isOpen())
	{		
		this->time = tclock.getElapsedTime() - tprevtime;
		tprevtime = tclock.getElapsedTime();
		
		while (this->_menu->menuScreen == true || this->_menu->controlScreen == true)
		{
			this->menu();
		}
		this->input();
		this->update();
		this->collision();
		this->endCondition();
		this->display();
		this->eg.restart();
		while (win == true || lose == true)
		{
			this->drawEndGame();
		}
	}
}

/////////////////Stuff for me to do and general notes
//tweak movement and jump
//tweak collision