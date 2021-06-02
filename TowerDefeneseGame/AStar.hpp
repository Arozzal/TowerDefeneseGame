#pragma once
#include <queue>
#include "Game.hpp"
class AStar
{
	struct Node {
		int posx;
		int posy;
		int coust;
		int comefromex;
		int comefromey;

		int difftoend;
		int countedfields;
		Node(int posx, int posy, int comefromex, int comefromey, int countedfields, int difftoend) {
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
	bool existpath;
	std::priority_queue<Node> openlist;
	sf::Vector2i lastpos;
	Array2D closedlist;
	void clearArr(int xsize, int ysize);
public:
	AStar();
	bool calculateAStar(Game & game, sf::Vector2i startpos);
	Array2D& getList() { return closedlist; }
	virtual ~AStar();
};

