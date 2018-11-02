#pragma once
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Shooting
{
public:
	Shooting();
	~Shooting();

	void draw(RenderWindow &window);
	void update(Sprite n);

	vector<Sprite> bullets;

	bool faceR = true; //which way is character facing
	int bulletAmount = 0; //amount of bullets
	vector<int> bulletDirection; //vector containing direction of each bullet as they can be different

private:
	Texture bulletsTexture;

	float bulletSpeed = 500.f;
	int ttype = 0;
	int hipfire = 400;

	Clock clock;
	Clock c;
	Time t;
};