#pragma once
#include "Entity.hpp"
class Fort : public Entity
{

public:
	explicit Fort(Game& game);
	virtual void update(Game& game) override;
	virtual void draw(Game& game) override;
	~Fort();
};

