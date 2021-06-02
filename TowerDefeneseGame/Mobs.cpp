#include "Mobs.hpp"
#include "Fort.hpp"
#include "Unit.hpp"
#include "Game.hpp"

////////////////
//MobGreenTank//
////////////////

MobGreenTank::MobGreenTank(int xpos, int ypos)
{
	create("TankNormal");
	setHp(7);
	Mobinit(xpos, ypos, 16, Mob::normal);
	mymoney = 30;
	setFlying(false);
}

void MobGreenTank::update(Game & game)
{
	posUpdate();
	updateLight(game);
	checkForAstarAndUpdate(game);

	if (isDiffToPosSmallerThen({ 32,32 }, game.settings.levelendpos)) {
		hp = -1;
		damgeFord(1, game);
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive)
		updateDot(game);

	updateHpBar();
}

void MobGreenTank::draw(Game & game)
{
	drawMobEffects(game);
}

///////////////
//MobSmallCar//
///////////////

MobSmallCar::MobSmallCar(int xpos, int ypos)
{
	create("Car");
	setHp(5);
	Mobinit(xpos, ypos, 12, Mob::small);
	mymoney = 15;
	setFlying(false);
}

void MobSmallCar::update(Game & game)
{
	posUpdate();
	updateLight(game);
	checkForAstarAndUpdate(game);

	if (isDiffToPosSmallerThen({ 32,32 }, game.settings.levelendpos)) {
		hp = -1;
		damgeFord(2, game);
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive)
		updateDot(game);

	updateHpBar();
}

void MobSmallCar::draw(Game & game)
{
	drawMobEffects(game);
}

//////////////////
//MobVeryTinyCar//
//////////////////


MobVeryTinyCar::MobVeryTinyCar(int xpos, int ypos)
{
	
	setHp(4);
	create("CarTiny");
	Mobinit(xpos, ypos, 8, Mob::tiny);
	sprite.setOrigin(-4, -4);

	mymoney = 10;
	
	speed = 1.25f;
	setFlying(false);
}

void MobVeryTinyCar::update(Game & game)
{
	posUpdate();
	updateLight(game);
	checkForAstarAndUpdate(game);

	if (isDiffToPosSmallerThen({ 32,32 }, game.settings.levelendpos)) {
		hp = -1;
		damgeFord(2, game);
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive)
		updateDot(game);

	updateHpBar();
}

void MobVeryTinyCar::draw(Game & game)
{
	drawMobEffects(game);
}

///////////////
//MobTankGray//
///////////////

MobTankGray::MobTankGray(int xpos, int ypos)
{
	setHp(25);
	create("TankStrong");
	Mobinit(xpos, ypos, 24, Mob::strong);

	mymoney = 50;

	speed = 0.75f;
	setFlying(false);
}

void MobTankGray::update(Game & game)
{
	posUpdate();
	updateLight(game);
	checkForAstarAndUpdate(game);

	if (isDiffToPosSmallerThen({ 32,32 }, game.settings.levelendpos)) {
		hp = -1;
		damgeFord(2, game);
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive)
		updateDot(game);

	updateHpBar();
}

void MobTankGray::draw(Game & game)
{
	drawMobEffects(game);
}

/////////////
//MobSphere//
/////////////


MobSphere::MobSphere(int xpos, int ypos)
{
	setHp(12);
	create("Sphere");
	Mobinit(xpos, ypos, 16, Mob::sphere);

	mymoney = 35;

	speed = 0.75f;
	setFlying(false);
}

void MobSphere::update(Game & game)
{
	posUpdate();
	updateLight(game);
	checkForAstarAndUpdate(game);



	if (isDiffToPosSmallerThen({ 32,32 }, game.settings.levelendpos)) {
		hp = -1;
		damgeFord(1, game);
	}

	if (hp <= 0 && hascreated == false) {
		createMobs(5, game);
		hascreated = true;
	}

	if (existpath) {
		findNextAStar(game);
		moveToNextBlockAStar(game);
	}

	if (isdotactive)
		updateDot(game);

	updateHpBar();
}

void MobSphere::draw(Game & game)
{
	drawMobEffects(game);
}

////////////
//MobPlane//
////////////

MobPlane::MobPlane(int xpos, int ypos)
{
	setHp(5);
	create("PlaneNormal");
	Mobinit(xpos, ypos, 16, Mob::planenormal);

	mymoney = 45;

	speed = 0.65f;
	setFlying(true);
}

void MobPlane::update(Game & game)
{
	planeMovement(game);
	updateLight(game);

	if (isDiffToPosSmallerThen(sf::Vector2f(32, 64), game.settings.levelendpos)) {
		hp = -1;
		damgeFord(2, game);
	}

	updateHpBar();
}

void MobPlane::draw(Game & game)
{
	drawMobEffects(game);
}

////////////////
//MobFlyingMob//
////////////////

MobFlyingBomb::MobFlyingBomb(int xpos, int ypos)
{
	setHp(5);
	create("FlyingBomb");
	Mobinit(xpos, ypos, 16, Mob::flyingbomb);

	mymoney = 45;

	speed = 0.35f;
	setFlying(true);
}

void MobFlyingBomb::update(Game & game)
{
	Unit* funit = game.getNearestUnit(sprite.getPosition());

	if (funit != nullptr && hasdamaged == false) {
		followunitpos = funit->getSprite().getPosition();
		sf::Vector2f diff = followunitpos - sprite.getPosition();

		if (diff.x < 16.f && diff.y < 16.f) {
			funit->setHp(funit->getHp() - 1);
			setHp(-1);
			hasdamaged = true;
		}

		float length = sqrt(diff.x * diff.x + diff.y * diff.y);

		diff.x /= length;
		diff.y /= length;

		sprite.move(diff * 0.33f);
	}

	updateHpBar();
}

void MobFlyingBomb::draw(Game & game)
{
	drawMobEffects(game);
}
