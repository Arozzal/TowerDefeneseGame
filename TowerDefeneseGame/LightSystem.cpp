#include "LightSystem.hpp"
#include "Game.hpp"


void LightSystem::init(int xsize, int ysize)
{
	get().lightMapTexture.create(xsize, ysize);
	get().lightmap.setTexture(get().lightMapTexture.getTexture());
	
	get().lightTexture.loadFromFile("images/light.png");
	get().lightTexture.setSmooth(true);
	get().lightmap.setPosition(0, 0);

	get().light.setTexture(get().lightTexture);
	get().light.setTextureRect(sf::IntRect(0, 0, 300, 300));
	get().light.setOrigin(150.f, 150.f);
	get().lightmap.setTextureRect(sf::IntRect(0, 0, 1600, 900));
	//get().lights.push_back(Light(sf::Vector2f(300, 300), sf::Vector2f(0.9f, 0.9f), sf::Color(255, 180, 130, 255)));
}

void LightSystem::update()
{

	auto &ls = get();
	ls.lightMapTexture.clear(sf::Color(100, 100, 160));

	for (int i = 0; i < ls.lights.size(); ++i) {
		ls.light.setScale(ls.lights[i]->scale);
		ls.light.setColor(ls.lights[i]->color);
		ls.light.setPosition(ls.lights[i]->position);

		ls.lightMapTexture.draw(ls.light, sf::BlendAdd);
	}

	ls.lightMapTexture.display();
	ls.lights.clear();
}

void LightSystem::draw(Game & game)
{
	game.window->draw(get().lightmap, sf::BlendMultiply);
}

LightSystem::LightSystem()
{
}


LightSystem::~LightSystem()
{
}
