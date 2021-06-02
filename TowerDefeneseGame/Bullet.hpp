#pragma once
#include "Mob.hpp"
#include "Entity.hpp"
#include "ParticleSystem.hpp"
class Bullet : public Entity
{
	bool follow;
	bool expanim;
	bool hasdamaged = false;
	bool flagexploding = false;
	bool candot = false;

	
	int explosiondmg = 0;
	int speed;
	int dmg;
	
	bool slow = false;
	types ID;
	

	
	sf::Vector2f enemysize;
	

	

	sf::Sprite desspr;
	


	

protected:
	int frame = -1;
	int milees = 0;
	int deathframecount = -1;

	ParticleSystem* psys = nullptr;

	Mob* followmob = nullptr;

	sf::Vector2f diff;
	sf::Vector2f gotopos;
	sf::Vector2f nofollowpos;

	bool isCollidingPos(Game& game);
	bool isCollidingPos(Game& game, sf::Vector2f);
	bool followbullet();

	void moveAndRotateToPos(Game& game,sf::Vector2f& pos);
public:
	void init(types ID, sf::Vector2f gotopos);

	void explosionInit(Game& game, int framecount, std::string tex, sf::Vector2f position, int explosiondmg);
	void explosion(Game& game, int sizex = 32, int sizey = 32);

	void setFollow(Mob* mob) { this->followmob = mob; }
	void setSpeed(int speed) { this->speed = speed; }
	void setDmg(int dmg) { this->dmg = dmg; }

	void checkOutside(Game& game);

	int getSpeed() { return speed; }


	virtual ~Bullet() { delete psys; }
};