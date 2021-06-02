#include "Bullets.hpp"
#include "Game.hpp"

BulletNormal::BulletNormal(types ID, sf::Vector2f gotopos)
{
	create("Rocket");
	init(ID, gotopos);
	setSpeed(50);
	setDmg(2);
	hp = 1;
	deathanim = true;
	psys = new ParticleSystem(100, getSpriteMiddle(), sf::seconds(0.05f), ParticleSystem::circle);
	psys->setSpeed(20);
	psys->setColors(2, sf::Color(255, 1, 1, 255), sf::Color(1, 1, 1, 255));
	psys->setColRands(50.f, 50.f);
}

void BulletNormal::update(Game & game)
{
	if (followbullet()) {
		hp = -1;
		followmob->setHp(followmob->getHp() - 2);
		followmob = nullptr;
	}

	psys->setEmitter(sf::Vector2f(sprite.getPosition()));
	psys->update(sf::seconds(game.frametime));

	if (abs(diff.x) > 10.f || abs(diff.y) > 10.f) {
		moveAndRotateToPos(game, diff);
	}
	
}

void BulletNormal::draw(Game & game)
{
	game.render->draw(Render::middle, *psys, transform);
	game.render->draw(Render::middle, sprite, transform);
	game.render->draw(Render::middle, dessprite, transform);
}

///////////
//GooBall//
///////////

BulletGoo::BulletGoo(types ID, sf::Vector2f gotopos)
{
	init(ID, gotopos);
	create("GooBall");
	setSpeed(35);
	setDmg(1);
	hp = 1;
	
}

void BulletGoo::update(Game & game)
{
	if (followbullet()) {
		hp = -1;
		followmob->slow();
		followmob->setHp(followmob->getHp() - 2);
		followmob = nullptr;
	}

	if (abs(diff.x) > 10.f || abs(diff.y) > 10.f) {
		moveAndRotateToPos(game, diff);
	}
}

void BulletGoo::draw(Game & game)
{
	game.render->draw(Render::middle, sprite, transform);
	game.render->draw(Render::middle, dessprite, transform);
}

///////////////
//MegaBullets//
///////////////

BulletMega::BulletMega(types ID, sf::Vector2f gotopos)
{
	init(ID, gotopos);
	create("MegaBomb");
	setSpeed(30);
	setDmg(1);
	nofollowpos = { -1,-1 };
	this->gotopos = gotopos;
}

void BulletMega::update(Game & game)
{
	if (isCollidingPos(game)) {
		if (deathframecount == -1)
			explosionInit(game, 3, "BombExplosion", sprite.getPosition(), 1);
		
		explosion(game);
	}
	
	moveAndRotateToPos(game, diff);
}

void BulletMega::draw(Game & game)
{
	game.render->draw(Render::middle, sprite, transform);
	game.render->draw(Render::middle, dessprite, transform);
}

////////////////
//LasserBullet//
////////////////


BulletLasser::BulletLasser(types ID, sf::Vector2f gotopos)
{
	init(ID, gotopos);
	create("LasserTower");
	setSpeed(0);
	setDmg(1);
}

void BulletLasser::update(Game & game)
{
	if (deathframecount == -1)
		explosionInit(game, 4, "Electricity", getSpriteMiddle(), 2);

	explosion(game);
}

void BulletLasser::draw(Game & game)
{
	game.render->draw(Render::middle, sprite, transform);
	game.render->draw(Render::middle, dessprite, transform);
}

///////////////////////
//RocketThrowerBullet//
///////////////////////

BulletRocketThrower::BulletRocketThrower(types ID, sf::Vector2f gotopos)
{
	init(ID, gotopos);
	create("FireRocket");
	setSpeed(50);
	setDmg(2);
	deathanim = true;
	hp = 2;
}

void BulletRocketThrower::update(Game & game)
{
	if (followbullet()) {
		hp--;
		followmob->setHp(followmob->getHp() - 2);
		followmob->setDot(5.f);
		setSpeed(getSpeed() * 2);
		if (hp > 0)
			followmob = game.getNearest(sf::Vector2f(sprite.getPosition().x + rand() % 64 - 100, sprite.getPosition().y + rand() % 64 - 100));
		else
			followmob = nullptr;
	}

	if (abs(diff.x) > 10.f || abs(diff.y) > 10.f) {
		moveAndRotateToPos(game, diff);
	}
}

void BulletRocketThrower::draw(Game & game)
{
	game.render->draw(Render::middle, sprite, transform);
	game.render->draw(Render::middle, dessprite, transform);
}

//////////////////
//BulletAtomBomb//
//////////////////


BulletAtomBomb::BulletAtomBomb(types ID, sf::Vector2f gotopos)
{
	create("AtomRocket");
	init(ID, gotopos);
	setDmg(10);
	setSpeed(50);
	deathanim = true;
	hp = 1;
	psys = new ParticleSystem(100, sprite.getPosition() / 5.f, sf::seconds(0.35f), ParticleSystem::circle);
	psys->setSpeed(20);
	psys->setColors(2, sf::Color(255, 1, 1, 255), sf::Color(1, 1, 1, 255));
	psys->setColRands(50.f, 50.f);
}

void BulletAtomBomb::update(Game & game)
{

	psys->update(sf::seconds(game.frametime));

	if (isCollidingPos(game, gotopos)) {
		if (deathframecount == -1) {
			explosionInit(game, 6, "Explosion", sprite.getPosition(), 20);
			psys = new ParticleSystem(500, sprite.getPosition() / 5.f, sf::seconds(5), ParticleSystem::circle);
			psys->setSpeed(200);
			psys->setColors(2, sf::Color(255, 1, 1, 255), sf::Color(128, 128, 1, 255));
			psys->setColRands(50.f, 50.f);
			psys->setScale(sf::Vector2f(5.f, 5.f));
			psys->setEmitter(sprite.getPosition() / 5.f);
		}
		dessprite.setScale(10.f, 10.f);


		explosion(game, 16, 16);
	}
	else {
		psys->setEmitter(sprite.getPosition());
	}


	milees -= 1;
	moveAndRotateToPos(game, diff);
}

void BulletAtomBomb::draw(Game & game)
{
	
	if (psys != nullptr) {
		game.render->drawTile(Render::middle, *psys);
	}

	if (deathframecount == -1)
		game.render->draw(Render::middle, sprite, transform);

	game.render->draw(Render::above, dessprite, transform);
}
