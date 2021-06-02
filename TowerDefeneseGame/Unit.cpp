#include "Unit.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "Bullets.hpp"
#include "Mob.hpp"
#include "EntityData.hpp"

Unit::Unit(int xpos, int ypos, types ID)
{
	entitytypeID = Unittype;


	auto stats = *(EntityData::getUnitData(ID));
	create(stats.texname);
	radius = stats.radius;

	if(ID == flying)
		canshotflying = true;
	
	if(ID == construction)
		isconstruction = true;

	if (ID == constructionatom)
		isconstruction = true;

	if (ID == atom)
		isconstruction = true;
	
	l = LightSystem::Light({ 200.f,200.f }, { 1.f,1.f }, sf::Color(255, 180, 130, 255));
	this->ID = ID;
	setPos({ xpos, ypos });
	
	radiuscricle.setRadius(radius);
	radiuscricle.setFillColor({ 255,0,0,100 });
	radiuscricle.setPointCount(50);
	radiuscricle.setPosition({(float)xpos * 16 - radius + sprite.getGlobalBounds().width / 2, (float)ypos * 16 - radius + sprite.getGlobalBounds().height / 2});

	setHp(10);
	maxhp = getHp();

	createHpBar(sprite.getGlobalBounds().width);
}


void Unit::update(Game & game)
{
	transform = sf::Transform();
	transform.scale(game.settings.zoom, game.settings.zoom);
	transform.rotate(rot, sprite.getPosition().x + 8, sprite.getPosition().y + 8);

	updateHpBar();

	if (isconstruction) {
		updateConstruction(game);
		return;
	}
	l.position = sf::Vector2f( sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f, sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f ) * game.settings.zoom;
	LightSystem::addLight(&l);
	anims.updateAll(game.frametime);
	sf::Vector2f mobpos;
	float absradius = 1000000.f;
	if (game.getNearest(sprite.getPosition(), canshotflying) != nullptr) {

		//if (game.getNearest(sprite.getPosition())->isFlying != canshotflying);

		mobpos = game.getNearest(sprite.getPosition(), canshotflying)->getSprite().getPosition() - sprite.getPosition();


		absradius = abs(sqrt(abs(mobpos.x) * abs(mobpos.x) + abs(mobpos.y) * abs(mobpos.y)));
	}
	if (absradius < radius) {
		float radians = atan2(mobpos.y, mobpos.x);
		float degrees = radians / 3.141 * 180;
		if (timer <= 0) {
			
			Bullet* bull;
			switch (ID) {
			case normal:
				bull = new BulletNormal(ID, getSpriteMiddle());
				break;
			case goo:
				bull = new BulletGoo(ID, getSpriteMiddle());
				break;
			case rocketthrower:
				bull = new BulletRocketThrower(ID, getSpriteMiddle());
				break;
			case lassertower:
				bull = new BulletLasser(ID, getSpriteMiddle());
				break;
			case flying:
				bull = new BulletNormal(ID, getSpriteMiddle());
				break;
			case bomb:
				bull = new BulletMega(ID, getSpriteMiddle());
				break;
			default:
				bull = new BulletNormal(ID, getSpriteMiddle());
			}
				
			bull->setPos(pos);
			bull->setFollow(game.getNearest(sprite.getPosition(), canshotflying));


			game.entitylist.push_back(bull);
			setTimer(2.f);
		}

		
		if (ID != lassertower) {
			transform = sf::Transform();
			transform.scale(game.settings.zoom, game.settings.zoom);
			rot = degrees + 90;
			transform.rotate(rot, sprite.getPosition().x + 8, sprite.getPosition().y + 8);
		}
	}

	
	updateTimer(game.frametime);
}

void Unit::updateConstruction(Game & game)
{
	if(ID == construction)
		if (game.settings.constcooldowns[0] > 0)
			game.settings.constcooldowns[0] -= game.frametime;
	if (ID == constructionatom)
		if (game.settings.constcooldowns[1] > 0)
			game.settings.constcooldowns[1] -= game.frametime;

}

void Unit::draw(Game& game)
{
	if(isMouseOver(game))
	game.render->drawTile(Render::aboveLight, radiuscricle);

	game.render->draw(Render::middle,sprite, transform);
	anims.drawAll(*game.window);

	if(hp != maxhp)
	drawHpBar(game);
}


