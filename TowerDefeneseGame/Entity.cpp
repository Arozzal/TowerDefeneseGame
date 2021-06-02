#include "Entity.hpp"
#include <SFML\Graphics.hpp>
#include "Game.hpp"

void Entity::createHpBar(int width)
{
	hpbar.first = nullptr;
	hpbar.second = nullptr;

	if (width == 0)
		width = sprite.getGlobalBounds().width;

	hpbarwidth = width;

	hpbar.first = new sf::RectangleShape({ float(width), 3 });
	hpbar.second = new sf::RectangleShape({ float(width), 3 });

	hpbar.first->setFillColor({ 102,244,127,255 });
	hpbar.second->setFillColor({ 242,82,85,255 });

	hpbar.first->setOrigin({ float(width) / 2, 3 / 2 });
	hpbar.second->setOrigin({ float(width) / 2, 3 / 2 });
	enableHpbar = true;
}

void Entity::updateHpBar()
{
	hpbar.second->setPosition(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2 , sprite.getPosition().y - (hpbar.second->getGlobalBounds().height * 0.5  + 3));
	hpbar.first->setPosition(hpbar.second->getPosition());
	hpbar.first->setSize({ float(hpbarwidth) / maxhp * hp,3.f });
}

void Entity::drawHpBar(Game & game)
{
	if (enableHpbar) {
		game.render->drawTile(Render::aboveLight, *hpbar.second);
		game.render->drawTile(Render::aboveLight, *hpbar.first);
	}
}

bool Entity::isMouseOver(Game& game)
{
	sf::Vector2f mpos = (sf::Vector2f)sf::Mouse::getPosition(*game.window);
	mpos /= game.settings.zoom;


	if (mpos.x > sprite.getPosition().x && mpos.x < sprite.getPosition().x + sprite.getGlobalBounds().width
		&& mpos.y > sprite.getPosition().y && mpos.y < sprite.getPosition().y + sprite.getGlobalBounds().height) {
		return true;
	}
	return false;
}

bool Entity::isDiffToPosSmallerThen(sf::Vector2f diff, sf::Vector2i pos, sf::Sprite * sprite)
{
	if (sprite == nullptr) {
		sprite = &this->sprite;
	}

	sf::Vector2f difftoend = sf::Vector2f(pos) * 16.f - sprite->getPosition();
	difftoend.x = abs(difftoend.x);
	difftoend.y = abs(difftoend.y);

	if (difftoend.x < diff.x && difftoend.y < diff.y) {
		return true;
	}
	return false;
}

bool Entity::canDestroy()
{
	if (hp > 0)
		return false;

	if (deathanim == false)
		return true;


	if (deathphase == -1){
		dessprite.setTexture(Textures::getTexture("Explosion"));
		psysdeath = new ParticleSystem(50, { sprite.getPosition().x + sprite.getTextureRect().width / 2.f, sprite.getPosition().y + sprite.getTextureRect().height / 2.f }, sf::seconds(5), ParticleSystem::circle);
		psysdeath->setColors(2, sf::Color(102, 1, 1, 1), sf::Color(102, 1, 1, 1));
		psysdeath->setColRands(33.f, 100.f);
		psysdeath->setSpeed(100);
		deathtimer = 2;
		deathphase = 0;
	}

	if (timer <= 0) {
		deathtimer = 2;
		deathphase++;
	}

	if (deathphase >= 6) {
		delete psysdeath;
		psysdeath = nullptr;
		return true;
	}
	
	dessprite.setPosition(sprite.getPosition().x - sprite.getOrigin().x + sprite.getGlobalBounds().width / 2.f, 
						  sprite.getPosition().y - sprite.getOrigin().y + sprite.getGlobalBounds().height / 2.f);
	dessprite.setTextureRect({ deathphase * 16, 0, 16, 16 });
	dessprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	

	deathtimer--;
	return false;
}


void Entity::create(sf::Color col)
{
	anims.addAnimPhase("explosion");
}

void Entity::create(std::string path)
{
	transform.scale(3.5f, 3.5f);
	sprite.setTexture(Textures::getTexture(path));
}

void Entity::drawShadow(Render& window, sf::Transform& tr, Render::Layer layer)
{
	sprite.move(4.f, 4.f);
	sf::Color col = sprite.getColor();
	sprite.setColor(sf::Color(0, 0, 0, 128));
	window.draw(layer, sprite, tr);
	sprite.move(-4.f, -4.f);
	sprite.setColor(col);
}

