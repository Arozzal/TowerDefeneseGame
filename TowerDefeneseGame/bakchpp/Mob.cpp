#include "Mob.hpp"
#include "Game.hpp"
#include "Fort.hpp"

AStar Mob::astar;
int Mob::mobcount = 0;
bool Mob::recalculate = true;
sf::Vector2i Mob::lastplpos(-1,-1);
Mob::Array2D Mob::closedlist;
std::priority_queue<Mob::Node> Mob::openlist;
/*
void Mob::calculateAStar(Game & game)
{
	std::cout << "AStar: Calculating new Path." << std::endl;
	openlist.swap(std::priority_queue<Node>());
	clearArr(game.map.getXSize(), game.map.getYSize());

	sf::Vector2i tpos = pos;
	lastmypos = pos;
	
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

				
				int diffend = abs(x - pos.x) + abs(y - pos.y);
				int countfields = closedlist[lastmypos.x][lastmypos.y].countedfields + 1;

				openlist.emplace(x, y, lastmypos.x, lastmypos.y,0, diffend);

			}
		}

		calccounter++;
		if (calccounter > 10000) {
			std::cerr << "AStar: Can't calculate new Path! " << std::endl;
			return;
		}

		if (openlist.empty()) {
			std::cerr << "AStar: Path dont exist! " << std::endl;
			existpath = false;
			return;
		}


		closedlist[openlist.top().posx][openlist.top().posy] = openlist.top();

		lastmypos.x = openlist.top().posx;
		lastmypos.y = openlist.top().posy;

		tpos.x = openlist.top().posx;
		tpos.y = openlist.top().posy;

		if (closedlist[tpos.x][tpos.y].posx == game.settings.levelendpos.x && closedlist[tpos.x][tpos.y].posy == game.settings.levelendpos.y) {
			break;
		}


		bool dublicatefound = false;

		openlist.pop();


		recalculate = false;
	}


	existpath = true;
	lastplpos = game.settings.levelendpos;
}
*/
void Mob::findNextAStar(Game & game)
{
	sf::Vector2i crpos = game.settings.levelendpos;
	auto clist = astar.getList();

	bool hasNotfound = true;
	int findcounter = 0;

	while (hasNotfound && blockarrived) {

		findcounter++;
		sf::Vector2i tf(crpos);

		crpos.x = clist[tf.x][tf.y].comefromex;
		crpos.y = clist[tf.x][tf.y].comefromey;

		int td = 0;
		if (abs(crpos.x - pos.x) <= 1)td++;
		if (abs(crpos.y - pos.y) <= 1)td++;

		if (crpos.x == -1) {
			recalculate = false;
			crpos = game.settings.levelendpos;
			return;
		}


		if (clist[crpos.x][crpos.y].comefromex == pos.x && clist[crpos.x][crpos.y].comefromey == pos.y || clist[crpos.x][crpos.y].comefromex == 0 && clist[crpos.x][crpos.y].comefromey == 0) {
			gotohere = crpos;
			hasNotfound = false;
			blockarrived = false;
		}

		if (findcounter > 1000) {
			std::cerr << "AStar: Found no Path in List!" << std::endl;
			break;
		}
	}
}

void Mob::moveToNextBlockAStar(Game & game)
{

	float xspeed = (gotohere.x * 16 - sprite.getPosition().x) * game.frametime;
	float yspeed = (gotohere.y * 16 - sprite.getPosition().y) * game.frametime;
	
	float length = sqrt(xspeed * xspeed + yspeed * yspeed);
	
	float radians = atan2(yspeed, xspeed);
	float degrees = radians / 3.141 * 180;



	if (abs(gotohere.x * 16 - sprite.getPosition().x) < 1 && abs(gotohere.y * 16 - sprite.getPosition().y) < 1) {
		blockarrived = true;
		sprite.setPosition(gotohere.x * 16, gotohere.y * 16);
	}
	else {
		this->transform = sf::Transform();
		transform.scale(game.settings.zoom, game.settings.zoom);
		

		posUpdate();
		sf::FloatRect tcollx = sprite.getGlobalBounds();
		tcollx.left += xspeed;

		sf::FloatRect tcolly = sprite.getGlobalBounds();
		tcollx.left += yspeed;

		

		xspeed /= length;
		yspeed /= length;
	
		if (slowed) {
			if (slowtimer <= 0) {
				slowed = false;
				sprite.setColor(sf::Color(255, 255, 255, 255));
			}
			xspeed *= 0.5f;
			yspeed *= 0.5f;
			slowtimer -= game.frametime;
		}

		sprite.move(xspeed * speed, yspeed * speed);


		transform.rotate(degrees, sf::Vector2f(sprite.getPosition().x + 8, sprite.getPosition().y + 8));
		
	}
	
}






Mob::Mob(int xpos, int ypos, Mobtypes ID)
{
	entitytypeID = Mobtype;

	int hpbarwidth = 16;

	switch (ID) {
	case normal:
		mymoney = 30;
		setHp(7);
		create("TankNormal");
		break;
	case small:
		mymoney = 15;
		setHp(5);
		hpbarwidth = 12;
		create("Car");
		speed = 1.5f;
		break;
	case tiny:
		mymoney = 10;
		setHp(4);
		create("CarTiny");
		sprite.setOrigin({ -4,-4 });
		speed = 1.25f;
		hpbarwidth = 8;
		break;
	case strong:
		mymoney = 50;
		setHp(25);
		create("TankStrong");
		speed = 0.75f;
		hpbarwidth = 24;
		break;
	case sphere:
		mymoney = 35;
		setHp(12);
		create("Sphere");
		speed = 0.75f;
		iscontainer = true;
		break;
	case planenormal:
		mymoney = 45;
		setHp(5);
		create("PlaneNormal");
		speed = 0.65f;
		isflying = true;
		break;
	default:
		std::cerr << "Mob: " << "Not defined Mob Type!" << std::endl;
	}
	
	l = LightSystem::Light({ 200.f,200.f }, { 1.f,1.f }, sf::Color(255, 180, 130, 255));

	if (isflying) 
		moblayer = Render::mobup;
	else
		moblayer = Render::mobdown;

	deathanim = true;
	mobcount++;
	
	setPos({ xpos, ypos });



	maxhp = getHp();
	createHpBar(hpbarwidth);
	myclosedlist = Array2D(closedlist);
}


void Mob::clearArr(int xsize, int ysize)
{
	closedlist.clear();
	Node node(-1,-1,-1,-1,-1,-1);

	for (int x = 0; x < xsize; x++) {
		closedlist.emplace_back();
		for (int y = 0; y < ysize; y++) {
			closedlist[x].push_back(node);
		}
	}
}



void Mob::planeMovement(Game& game) {

	sprite.move({ speed * 50 * game.frametime, 0 });
	posUpdate();
	this->transform = sf::Transform();
	transform.scale(game.settings.zoom, game.settings.zoom);
	

	if (getPos().x >= game.map.getXSize()) {
		if (firstrouteisflown == false) {
			speed = -speed * 2;
			sprite.setScale(-1, 1);
			sprite.setPosition(sprite.getPosition().x, game.settings.levelendpos.y * 16);

			firstrouteisflown = true;
		}
	}

	if (isDiffToPosSmallerThen(sf::Vector2f(32, 64), game.settings.levelendpos)) {
		hp = -1;
		game.fort->setHp(game.fort->getHp() - 2);
	}

	updateHpBar();
}

void Mob::update(Game& game)
{
	posUpdate();


	if (hp <= 0) {
		if (iscontainer) {
			for (int i = -2; i < 3; ++i) {
				Mob* mob = new Mob(pos.x, pos.y, Mob::tiny);
				mob->setCostumSpeed(1.25f + 0.25f * i);
				game.entitylist.emplace_back(mob);
			}
			iscontainer = false;
		}
		return;
	}
	
	if (canDestroy() == false) {
		l.position = sf::Vector2f(sprite.getPosition().x + sprite.getTextureRect().width / 2.f, sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f) * game.settings.zoom;
		LightSystem::addLight(&l);
	}

	if (isflying) {
		planeMovement(game);
		return;
	}
	


	if (isDiffToPosSmallerThen({32,32}, game.settings.levelendpos)){
		sf::Vector2f speed = (sf::Vector2f(game.settings.levelendpos) * 16.f - sprite.getPosition()) * game.frametime;

		hp = -1;
		game.fort->setHp(game.fort->getHp() - 2);

		return;
	}
	


	if (game.settings.levelendpos != lastplpos || game.settings.pathchanged)
		recalculate = true;


	if (recalculate) {
		//calculateAStar(game);
		if (astar.calculateAStar(game, getPos())) {
			lastplpos = game.settings.levelendpos;
			recalculate = false;
			game.settings.pathchanged = false;
			notfound = false;
		}
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive) {
		if (psysdot == nullptr) {
			psysdot = new ParticleSystem(100, getSpriteMiddle(), sf::seconds(3), ParticleSystem::circle);
			psysdot->setColors(2, sf::Color(128, 1, 1, 1), sf::Color(255, 128, 1, 256));
			psysdot->setTexture("FireParticle");
			psysdot->setColRands(33.f, 80.f);
			psysdot->setSpeed(10);
			psysdot->setCircleRadius(1.5f);
		}
		
		psysdot->update(sf::seconds(game.frametime));
		psysdot->setEmitter(getSpriteMiddle());

		int thistime = (int)dottimer;
		dottimer -= game.frametime;

		if ((int)dottimer != thistime) {
			hp -= 1;
		}

		if (dottimer <= 0) {
			isdotactive = false;
			sprite.setColor({ 255,255,255,255});
			delete psysdot;
			psysdot = nullptr;
		}
	}


	
	posUpdate();
	updateHpBar();
}

void Mob::draw(Game& game)
{
	if (isFlying()) {
		drawShadow(*game.render, transform, moblayer);
	}


	game.render->draw(moblayer, sprite, transform);
	if (enableHpbar) {
		game.render->drawTile(Render::aboveLight, *hpbar.second);
		game.render->drawTile(Render::aboveLight, *hpbar.first);
	}
	anims.drawAll(*game.window);

	if (psysdeath != nullptr) {
		psysdeath->update(sf::seconds(game.frametime));
		psysdeath->setEmitter(sprite.getPosition());
	}

	if (hp <= 0) {
		drawDeathParticle(*game.render);
		game.render->draw(moblayer, dessprite, transform);
	}

	if (psysdot != nullptr)
		game.render->draw(moblayer, *psysdot, transform);
}



