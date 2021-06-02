#pragma once
#include <iostream>

#include <SFML\Graphics.hpp>

#include "Animation.hpp"
#include "Textures.hpp"
#include "ParticleSystem.hpp"
#include "LightSystem.hpp"
#include "Render.hpp"

typedef std::pair < sf::RectangleShape*, sf::RectangleShape*> Hpbar;

class Game;
class Entity

{
protected:
	
	sf::Sprite sprite;

	sf::Sprite dessprite;

	Animation anims;
	LightSystem::Light l;
	float timer = 0;
	sf::Vector2i pos;

	sf::Transform transform;
	bool enableHpbar = false;
	bool candestroy = false;
	bool deathanim = false;
	int hp = 1;
	int hpbarwidth = 0;
	int maxhp = 0;
	int mymoney = 0;
	int deathphase = -1;
	float deathtimer = 0;

	Hpbar hpbar;
	

public:
	enum types {
		normal,
		goo,
		bomb,
		lassertower,
		rocketthrower,
		flying,
		construction,
		constructionatom,
		atom
	};

	enum entitytype {
		Bullettype,
		Mobtype,
		Unittype
	};

	sf::Vector2f getSpriteMiddle() { return sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f, sprite.getPosition().y + sprite.getGlobalBounds().height / 2.f); }
	sf::Vector2f getSpriteMiddle(const sf::Sprite& spr) { return sf::Vector2f(spr.getPosition().x + spr.getGlobalBounds().width / 2.f, spr.getPosition().y + spr.getGlobalBounds().height / 2.f); }
	types ID;
	entitytype entitytypeID;
	entitytype getEntityTypeID() { return entitytypeID; }
	ParticleSystem* psysdeath = nullptr;
	types getType() { return ID; }

	void drawDeathParticle(Render& rend) { if (psysdeath != nullptr) rend.drawTile(Render::aboveLight, *psysdeath); }
	void createHpBar(int width = 0);
	void updateHpBar();
	void drawHpBar(Game& game);
	int getMyMoney() { return mymoney; }
	bool isMouseOver(Game& game);
	bool isDiffToPosSmallerThen(sf::Vector2f diff, sf::Vector2i end, sf::Sprite* sprite = nullptr);
	bool canDestroy();
	virtual void update(Game& game) = 0;
	virtual void draw(Game& game) = 0;
	void setHp(int hp) { this->hp = hp; }
	int getHp() { return this->hp; }
	void create(sf::Color);
	void create(std::string);
	void setPos(sf::Vector2i pos) { this->pos = pos; sprite.setPosition(pos.x * 16, pos.y * 16); }
	void posUpdate() { pos.x = (int)(sprite.getPosition().x / 16); pos.y = (int)sprite.getPosition().y / 16; }
	void drawShadow(Render& window, sf::Transform& tr, Render::Layer layer);
	sf::Sprite& getSprite() { return this->sprite; }
	int getDiffA(sf::Vector2i pos) { return abs(pos.x - this->pos.x) + abs(pos.y - this->pos.y); }
	sf::Vector2i getPos() { return this->pos; }
	void updateTimer(float time) { timer -= time; }
	void setTimer(float time) { timer = time; }
	virtual ~Entity() { std::cout << "Entity: Destroyed at X: " << pos.x << " Y: " << pos.y << std::endl; }
};

