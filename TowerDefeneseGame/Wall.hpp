#pragma once
#include "Entity.hpp"
class Wall : public Entity
{
	sf::Transform transform;
	bool secondform = false;
public:
	///brief pos multiplied with 16.
	Wall(int posx, int posy);

	virtual void update(Game& game) override;
	virtual void draw(Game& game) override;
	virtual ~Wall();
};

