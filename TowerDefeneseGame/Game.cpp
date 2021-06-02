#include "Game.hpp"
#include "Mob.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Unit.hpp"

sf::Vector2f Game::getMouseMapPos()
{
	sf::Vector2i mpos = sf::Mouse::getPosition(*window);
	return sf::Vector2f(window->mapPixelToCoords(mpos)) / settings.zoom;
}

sf::Vector2f Game::getMouseUiPos()
{
	sf::Vector2i mpos = sf::Mouse::getPosition(*window);
	return sf::Vector2f(window->mapPixelToCoords(mpos));
}

void Game::cleanLevel()
{
	bool temp = settings.editmode;
	for (Entity* entity : entitylist) {
		delete entity;
		entity = nullptr;
	}

	for (Wave* wave : wavelist) {
		delete wave;
		wave = nullptr;
	}
	wavelist.clear();
	entitylist.clear();

	settings = Game::Settings();
	settings.editmode = temp;
	settings.pathchanged = true;

	delete[] settings.unitimages;
	delete[] settings.costs;
}

Mob* Game::getNearest(sf::Vector2f pos, bool isflying)
{
	
	Mob* en = nullptr;
	

	float mainpos = sqrt(pow(pos.x, 2) + pow(pos.y, 2));

	float lastposdiff = 9999999.f;

	for (Entity* entity : entitylist) {
		if (entity->getEntityTypeID() != Entity::Mobtype)
			continue;

		Mob* tempmob = static_cast<Mob*>(entity);

		if (tempmob->isFlying() != isflying)continue;

		float thispossdiff = abs(abs(sqrt(pow(entity->getSprite().getPosition().x, 2) + pow(entity->getSprite().getPosition().y, 2))) - abs(mainpos));

		if (thispossdiff < lastposdiff) {
			lastposdiff = thispossdiff;
			en = tempmob;
		}
	}

	return en;
}

Unit* Game::getNearestUnit(sf::Vector2f pos)
{
	Unit* unit = nullptr;


	float mainpos = sqrt(pow(pos.x, 2) + pow(pos.y, 2));

	float lastposdiff = 9999999.f;

	for (Entity* entity : entitylist) {
		if (entity->getEntityTypeID() != Entity::Unittype)
			continue;

		Unit* tempunit = static_cast<Unit*>(entity);

		float thispossdiff = abs(abs(sqrt(pow(entity->getSprite().getPosition().x, 2) + pow(entity->getSprite().getPosition().y, 2))) - abs(mainpos));

		if (thispossdiff < lastposdiff) {
			lastposdiff = thispossdiff;
			unit = tempunit;
		}
	}

	return unit;
}



