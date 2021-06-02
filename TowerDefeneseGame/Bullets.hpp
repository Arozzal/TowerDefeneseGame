#pragma once
#include "Bullet.hpp"

class BulletNormal : public Bullet
{
public:
	BulletNormal(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class BulletGoo : public Bullet
{
public:
	BulletGoo(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class BulletMega : public Bullet
{
public:
	BulletMega(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class BulletLasser : public Bullet
{
public:
	BulletLasser(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class BulletRocketThrower : public Bullet {
public:
	BulletRocketThrower(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};

class BulletAtomBomb : public Bullet {
public:
	BulletAtomBomb(types ID, sf::Vector2f gotopos);
	void update(Game& game) override;
	void draw(Game& game) override;
};