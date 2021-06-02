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
		planenormal
	};



	struct Node {
		int posx;
		int posy;
		int coust ;
		int comefromex;
		int comefromey;

		int difftoend;
		int countedfields;
		Node(int posx, int posy, int comefromex, int comefromey,int countedfields ,int difftoend) {
			this->posx = posx;
			this->posy = posy;
			this->comefromex = comefromex;
			this->comefromey = comefromey;
			this->difftoend = difftoend;
			this->countedfields = countedfields;
			this->coust = countedfields;
		}

		friend bool operator<(const Node &n1, const Node &n2) {
			return n1.coust > n2.coust;
		}
	};

	typedef std::vector < std::vector<Node>> Array2D;
private:
	static AStar astar;
	static int mobcount;
	static bool recalculate;
	static sf::Vector2i lastplpos;

	static Array2D closedlist;
	static std::priority_queue<Node> openlist;

	Array2D myclosedlist;
	ParticleSystem* psysdot = nullptr;

	bool isflying = false;
	bool slowed = false;
	bool isdotactive = false;
	bool notfound = true;
	bool existpath = true;
	bool blockarrived = true;
	bool iscontainer = false;
	bool firstrouteisflown = false;

	float slowtimer = 0;
	float dottimer = 0;

	float speed = 1;
	
	void planeMovement(Game& game);
	void calculateAStar(Game& game);
	void findNextAStar(Game& game);
	void moveToNextBlockAStar(Game& game);
	
	Render::Layer moblayer;

	sf::Vector2i lastmypos;
	sf::Vector2i gotohere;
	sf::Transform transform;
public:
	explicit Mob(int xpos, int ypos, Mobtypes ID);
	~Mob() { mobcount--; }

	bool isFlying() { return isflying; }

	void slow() { slowtimer = 3.f; slowed = true; sprite.setColor(sf::Color(0, 128, 0, 255)); }
	void setDot(float ticks) { dottimer = ticks; isdotactive = true; sprite.setColor(sf::Color(255, 128, 0, 255)); }
	void setCostumSpeed(float speed) { this->speed = speed; }
	void clearArr(int xsize, int ysize);
	void update(Game& game) override;
	void draw(Game& game) override;
	
};

