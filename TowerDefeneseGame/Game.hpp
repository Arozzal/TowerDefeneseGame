#pragma once
#include <SFML\Graphics.hpp>
#include "Map.hpp"
//#include "Render.hpp"
#include "Entity.hpp"

class Entity;
class Player;
class Mob;
class Unit;
class Bullet;
class Wave;
class UiButton;
class UiElement;
class Fort;
class AStar;
class Render;

struct Game{
	Map map;
	sf::View* view;
	sf::Clock* clock;
	sf::Event* event;
	sf::RenderWindow* window = nullptr;

	sf::Texture backtexture;
	sf::Sprite background;

	sf::Texture watertexture;
	sf::Sprite watersprite;

	sf::Shader shadering;
	sf::VertexArray* shader;
	sf::VertexArray* grid;

	AStar* astar;

	std::vector<Entity*> entitylist;
	std::vector<Wave*> wavelist;



	Render* render;
	sf::Shader floorshader;

	Fort* fort;
	bool inputblocked = false;
	float blocktimer = 0;

	struct Settings {
		int wavepos = -1;
		float zoom = 3.5f;
		bool editmode = false;
		bool pathchanged = false;
		bool isUiUnitSelected = false;
		int basehp = 10;
		int money = 100;
		float basetimer = 33;
		float wavetimer = 0;
		int wavecount = 0;
		float constcooldowns[2] = {
			60,
			60
		};
		Entity::types setID = Entity::types::normal;
		bool darkness = false;
		int editblockid = 1;
		int newunitxsize = 16;
		int newunitysize = 16;
		sf::Vector2i levelendpos;
		sf::Vector2i lastplacedblock = sf::Vector2i(-1,-1);
		sf::Vector2i startpos = sf::Vector2i(0, 3);
		std::string currentlevel;

		int* costs;

		sf::Vector2u windowsize;
		std::string* unitimages;
		std::string* objectimages;
	};
	struct Ui {
		sf::Text* moneytext;
		sf::Text* wavetimer;
		sf::Text* countedwaves;

		
		sf::Texture* currentplacedtexture = nullptr;
	};

	sf::Vector2f getMouseMapPos();
	sf::Vector2f getMouseUiPos();
	
	Ui ui;
	Settings settings;

	void cleanLevel();
	Mob* getNearest(sf::Vector2f pos, bool isflying = false);
	Unit* getNearestUnit(sf::Vector2f pos);

	float frametime;
};
