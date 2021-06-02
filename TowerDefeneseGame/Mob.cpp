#include "Mob.hpp"
#include "Mobs.hpp"
#include "Game.hpp"
#include "Fort.hpp"

AStar Mob::astar;
int Mob::mobcount = 0;
bool Mob::recalculate = true;
sf::Vector2i Mob::lastplpos(-1,-1);

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

void Mob::updateLight(Game& game)
{
	if (canDestroy() == false) {
		l.position = sf::Vector2f(sprite.getPosition().x + sprite.getTextureRect().width / 2.f, sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f) * game.settings.zoom;
		LightSystem::addLight(&l);
	}
}

void Mob::checkForAstarAndUpdate(Game& game)
{
	if (game.settings.levelendpos != lastplpos || game.settings.pathchanged)
		recalculate = true;


	if (recalculate) {
		if (astar.calculateAStar(game, getPos())) {
			lastplpos = game.settings.levelendpos;
			recalculate = false;
			game.settings.pathchanged = false;
		}
	}
}

void Mob::updateDot(Game & game)
{
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
		sprite.setColor({ 255,255,255,255 });
		delete psysdot;
		psysdot = nullptr;
	}
}

void Mob::damgeFord(int dmg, Game& game)
{
	if (damagedFord == false) {
		game.fort->setHp(game.fort->getHp() - dmg);
		damagedFord = true;
	}
}

void Mob::createMobs(int count, Game & game)
{
	for (int i = -count / 2; i < count - count / 2; ++i) {
		Mob* mob = new MobVeryTinyCar(pos.x, pos.y);
		mob->setCostumSpeed(1.25f + 0.25f * i);
		game.entitylist.emplace_back(mob);
	}
}






void Mob::Mobinit(int xpos, int ypos, int hpbarwidth, Mobtypes ID)
{
	entitytypeID = Mobtype;
	

	l = LightSystem::Light({ 200.f,200.f }, { 1.f,1.f }, sf::Color(255, 180, 130, 255));

	deathanim = true;
	mobcount++;
	
	setPos({ xpos, ypos });



	maxhp = getHp();
	createHpBar(hpbarwidth);
	//myclosedlist = Array2D(closedlist);
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
}

void Mob::updateMob(Game& game)
{
	posUpdate();



	
	

	if (isflying) {
		planeMovement(game);
		return;
	}
	
	
	posUpdate();
	updateHpBar();
}

void Mob::drawMobEffects(Game& game)
{
	if (isFlying()) {
		drawShadow(*game.render, transform, moblayer);
	}

	game.render->draw(moblayer, sprite, transform);

	drawHpBar(game);

	if (psysdeath != nullptr) {
		psysdeath->update(sf::seconds(game.frametime));
		psysdeath->setEmitter(getSpriteMiddle());
	}

	if (hp <= 0) {
		drawDeathParticle(*game.render);
		game.render->draw(moblayer, dessprite, transform);
	}

	if (psysdot != nullptr)
		game.render->draw(moblayer, *psysdot, transform);
}



