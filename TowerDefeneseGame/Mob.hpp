#pragma once
#include "Entity.hpp"
#include "AStar.hpp"
#include <queue>



class Mob : public Entity
{
public:
	enum Mobtypes {
		normal,
		small,
		strong,
		tiny,
		sphere,
		planenormal,
		flyingbomb
	};


	
	//typedef std::vector < std::vector<Node>> Array2D;
private:
	static AStar astar;
	static int mobcount;
	static bool recalculate;
	static sf::Vector2i lastplpos;

	bool damagedFord = false;
	
protected:
	//Array2D myclosedlist;
	ParticleSystem* psysdot = nullptr;

	bool isflying = false;
	bool slowed = false;
	bool isdotactive = false;
	bool existpath = true;
	bool blockarrived = true;
	bool firstrouteisflown = false;

	float slowtimer = 0;
	float dottimer = 0;

	float speed = 1;
	
	void setFlying(bool cfyl) { moblayer = cfyl ? Render::mobup : Render::mobdown; isflying = cfyl; }
	void planeMovement(Game& game);
	void findNextAStar(Game& game);
	void moveToNextBlockAStar(Game& game);

	void updateLight(Game& game);
	void checkForAstarAndUpdate(Game& game);
	void updateDot(Game& game);
	void damgeFord(int dmg, Game& game);
	void createMobs(int count, Game& game);

	Render::Layer moblayer;

	sf::Vector2i lastmypos;
	sf::Vector2i gotohere;
public:
	void Mobinit(int xpos, int ypos, int hpbarwidth, Mobtypes ID);

	bool isFlying() { return isflying; }

	void slow() { slowtimer = 3.f; slowed = true; sprite.setColor(sf::Color(0, 128, 0, 255)); }
	void setDot(float ticks) { dottimer = ticks; isdotactive = true; sprite.setColor(sf::Color(255, 128, 0, 255)); }
	void setCostumSpeed(float speed) { this->speed = speed; }
	void updateMob(Game& game) ;
	void drawMobEffects(Game& game) ;
	
	virtual ~Mob() { mobcount--; }
};

