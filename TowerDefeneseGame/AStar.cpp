#include "AStar.hpp"



AStar::AStar()
{
}

void AStar::clearArr(int xsize, int ysize)
{
	closedlist.clear();
	Node node(-1, -1, -1, -1, -1, -1);

	for (int x = 0; x < xsize; x++) {
		closedlist.emplace_back();
		for (int y = 0; y < ysize; y++) {
			closedlist[x].push_back(node);
		}
	}
}

bool AStar::calculateAStar(Game & game, sf::Vector2i startpos)
{
	std::cout << "AStar: Calculating new Path." << std::endl;

	std::priority_queue<Node> node;

	openlist.swap(node);
	clearArr(game.map.getXSize(), game.map.getYSize());

	sf::Vector2i tpos = startpos;
	lastpos = startpos;

	closedlist[tpos.x][tpos.y].comefromex = 0;
	closedlist[tpos.x][tpos.y].comefromey = 0;
	closedlist[tpos.x][tpos.y].countedfields = 0;
	closedlist[tpos.x][tpos.y].coust = 0;

	int calccounter = 0;


	while (true) {
		for (int y = tpos.y - 1; y < tpos.y + 2; y++) {
			for (int x = tpos.x - 1; x < tpos.x + 2; x++) {

				if (x < 0 || x >= game.map.getXSize() || y < 0 || y >= game.map.getYSize())continue;

				if (closedlist[x][y].coust != -1)continue;
				if (game.map(x, y) != 0)continue;

				if (abs(tpos.x - x) == 1 && abs(tpos.y - y) == 1)continue;


				int diffend = abs(x - startpos.x) + abs(y - startpos.y);
				int countfields = closedlist[lastpos.x][lastpos.y].countedfields + 1;

				openlist.emplace(x, y, lastpos.x, lastpos.y, 0, diffend);

			}
		}

		calccounter++;
		if (calccounter > 10000) {
			std::cerr << "AStar: Can't calculate new Path! " << std::endl;
			return false;
		}

		if (openlist.empty()) {
			std::cerr << "AStar: Path dont exist! " << std::endl;
			existpath = false;
			return false;
		}


		closedlist[openlist.top().posx][openlist.top().posy] = openlist.top();

		lastpos.x = openlist.top().posx;
		lastpos.y = openlist.top().posy;

		tpos.x = openlist.top().posx;
		tpos.y = openlist.top().posy;

		if (closedlist[tpos.x][tpos.y].posx == game.settings.levelendpos.x && closedlist[tpos.x][tpos.y].posy == game.settings.levelendpos.y) {
			break;
		}


		bool dublicatefound = false;

		openlist.pop();

	}


	existpath = true;
	return true;
}

AStar::~AStar()
{
}
