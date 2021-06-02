#include "Wall.hpp"
#include "Game.hpp"
#include "Mob.hpp"

Wall::Wall(int posx, int posy)
{
	create("Wall");
	sprite.setPosition(posx * 16, posy * 16);

	
	hp = 10;
	maxhp = 10;
	hpbarwidth = 24;
	createHpBar(hpbarwidth);
}

void Wall::update(Game & game)
{

	transform = sf::Transform();
	transform.scale(game.settings.zoom, game.settings.zoom);

	if (game.map(getPos().x, getPos().y + 1) != 0 || game.map(getPos().x, getPos().y - 1) != 0) {
		transform.rotate(90, sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f, sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f);
	}
	else {
		transform.rotate(0, sprite.getPosition().x, sprite.getPosition().y);
	}

	if (secondform) {
		return;
	}


	Mob* ent = game.getNearest(sprite.getPosition(), false);

	if (ent != nullptr) {
		if (ent->getDiffA(pos) == 0 && ent->getHp() > 0) {
			hp -= ent->getHp();
			ent->setHp(-1);
			if (hp <= 0) {
				secondform = true;
				hp = 999;
				sprite.setTexture(Textures::getTexture("WallDestroyed"));
			}
		}
	}



	posUpdate();
	updateHpBar();
}

void Wall::draw(Game & game)
{
	game.render->draw(Render::down, sprite, transform);
	
	if (secondform == false && hp != maxhp) {
		game.render->drawTile(Render::middle, *hpbar.second);
		game.render->drawTile(Render::middle, *hpbar.first);
	}
}


Wall::~Wall()
{
}
