#include "Bullet.hpp"
#include "Game.hpp"





void Bullet::init(types ID, sf::Vector2f gotopos)
{
	/*
	entitytypeID = Bullettype;
	this->ID = ID;
	switch (ID) {
	case normal:
		this->speed = 50;
		this->follow = true;
		create("Rocket");
		dmg = 2;
		psys = new ParticleSystem(50, sprite.getPosition(), sf::seconds(0.05f), ParticleSystem::circle);
		psys->setSpeed(20);
		psys->setColors(2, sf::Color(255, 1, 1, 1), sf::Color(1, 1, 1, 1));
		psys->setColRands(50.f, 50.f);
		break;
	case goo:
		this->speed = 35;
		this->follow = true;
		create("GooBall");
		slow = true;
		dmg = 1;
		break;
	case bomb:
		this->speed = 30;
		this->follow = false;
		create("MegaBomb");
		desspr.setTexture(Textures::getTexture("Explosion"));
		slow = false;
		dmg = 1;
		flagexploding = true;
		break;
	case lassertower:
		this->speed = 0;
		this->follow = false;
		desspr.setTexture(Textures::getTexture("Electricity"));
		slow = false;
		dmg = 1;
		break;
	case rocketthrower:
		this->speed = 50;
		this->follow = true;
		create("FireRocket");
		desspr.setTexture(Textures::getTexture("Explosion"));
		slow = false;
		dmg = 1;
		flagexploding = true;
		candot = true;
		break;
	case flying:
		this->speed = 250;
		this->follow = true;
		create("Rocket");
		dmg = 1;
	case atom:
		this->speed = 30;
		this->follow = false;
		create("AtomRocket");
		desspr.setTexture(Textures::getTexture("Explosion"));
		dmg = 50;
		flagexploding = true;
		break;
	default:
		std::cerr << "Bullet: " << "Not defined Mob Type!" << std::endl;
	}

	*/
	
	nofollowpos = { -1,-1 };
	this->gotopos = gotopos;
	sprite.setOrigin(sprite.getGlobalBounds().width /2.f,sprite.getGlobalBounds().height / 2.f);
}

void Bullet::explosionInit(Game & game, int framecount, std::string tex, sf::Vector2f position, int explosiondmg)
{
	this->explosiondmg = explosiondmg;
	deathframecount = framecount;
	dessprite.setTexture(Textures::getTexture(tex));
	dessprite.setPosition(position);
}

void Bullet::explosion(Game& game, int sizex, int sizey)
{
	if (milees <= 0) {
		milees = 5;
		frame++;
	}

	dessprite.setTextureRect({ frame * sizex, 0, sizex, sizey });
	dessprite.setOrigin(dessprite.getTextureRect().width / 2.f, dessprite.getTextureRect().height / 2.f);

	if (ID == atom)
		dessprite.setScale(20.f, 20.f);

	if (hasdamaged == false) {
		for (auto ent : game.entitylist) {
			if (ent->getEntityTypeID() == entitytype::Mobtype) {

				if(ent->getSprite().getGlobalBounds().intersects(dessprite.getGlobalBounds())){
					ent->setHp(ent->getHp() - explosiondmg);
				}
				hasdamaged = true;
			}
		}
	}

	milees--;

	if (frame >= deathframecount) {
		hp = -1;
	}
}


bool Bullet::isCollidingPos(Game& game)
{
	if (nofollowpos == sf::Vector2f(-1, -1)) {
		Mob* thismob = game.getNearest(sprite.getPosition());
		sf::Vector2f gpos = thismob->getSprite().getPosition();
		nofollowpos = gpos;
	}
	diff = nofollowpos - sprite.getPosition();
	if (abs(diff.x) < 16 && abs(diff.y) < 16) {
		return true;
	}

	return false;
}

bool Bullet::isCollidingPos(Game & game, sf::Vector2f pos)
{
	diff = pos - sprite.getPosition();
	if (abs(diff.x) < 16 && abs(diff.y) < 16) {
		return true;
	}
	return false;
}

bool Bullet::followbullet()
{
	if (followmob != nullptr) {
		enemysize.x = followmob->getSprite().getGlobalBounds().width / 2;
		enemysize.y = followmob->getSprite().getGlobalBounds().height / 2;

		diff = followmob->getSprite().getPosition() + enemysize - sprite.getPosition();

		if (abs(diff.x) < 16 && abs(diff.y) < 16) {
			return true;
		}
	}

	return false;
}

void Bullet::moveAndRotateToPos(Game& game, sf::Vector2f& pos)
{
	float radians = atan2(pos.y, pos.x);
	float degrees = radians / 3.141 * 180;

	float length = sqrt(pos.x * pos.x + pos.y * pos.y);

	pos.x /= length;
	pos.y /= length;

	sprite.move(pos * game.frametime * float(speed));
	sprite.setRotation(degrees + 90);
}

void Bullet::checkOutside(Game & game)
{
	if (game.map.isOutside(pos.x, pos.y)) {
		hp = -1;
	}
}

/*void Bullet::BulletDraw(Game& game)
{
	if (psys != nullptr) {
		game.render->draw(Render::middle, *psys, transform);
	}


	if (sprite.getTexture() == nullptr) {
		std::cerr << "Bullet: Texture ist nullptr!" << std::endl;
	}
}
*/
