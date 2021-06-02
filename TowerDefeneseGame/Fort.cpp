#include "Fort.hpp"
#include "Game.hpp"


Fort::Fort(Game& game)
{
	create("Fort");

	hpbarwidth = sprite.getGlobalBounds().width;
	setHp(sprite.getGlobalBounds().width);
	maxhp = sprite.getGlobalBounds().width;
	
	createHpBar(sprite.getGlobalBounds().width);
	update(game);
}

void Fort::update(Game & game)
{
	sprite.setPosition(sf::Vector2f(game.settings.levelendpos.x - 1, game.settings.levelendpos.y - 1) * 16.f);
	updateHpBar();
}

void Fort::draw(Game & game)
{
	game.render->drawTile(Render::middle, *hpbar.second);
	game.render->drawTile(Render::middle, *hpbar.first);
	game.render->drawTile(Render::middle, sprite);
}


Fort::~Fort()
{
}
