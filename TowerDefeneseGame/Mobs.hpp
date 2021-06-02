#pragma once
#include "Mob.hpp"

class MobGreenTank : public Mob
{
public:
	MobGreenTank(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobSmallCar : public Mob 
{
public:
	MobSmallCar(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobVeryTinyCar : public Mob
{
public:
	MobVeryTinyCar(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobTankGray : public Mob
{
public:
	MobTankGray(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobSphere : public Mob
{
	bool hascreated = false;
public:
	MobSphere(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobPlane : public Mob
{
public:
	MobPlane(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class MobFlyingBomb : public Mob
{
	sf::Vector2f followunitpos;
	bool hasdamaged = false;
public:
	MobFlyingBomb(int xpos, int ypos);
	void update(Game& game) override;
	void draw(Game& game) override;
};