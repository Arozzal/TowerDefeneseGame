#pragma once
#include "Entity.hpp"
class Unit : public Entity
{
	int radius = 50;
	float rot = 0;
	bool canshotflying = false;
	bool isconstruction = false;
	sf::Transform transform;
	sf::CircleShape radiuscricle;
public:
	explicit Unit(int xpos, int ypos, types ID);
	void setRadius(int radius) { this->radius = radius; radiuscricle.setRadius(radius); }
	int getRadius() { return radius; }
	void update(Game& game) override;
	void updateConstruction(Game& game);
	void draw(Game& game) override;
};

