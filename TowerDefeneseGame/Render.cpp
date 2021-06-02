#include "Render.hpp"
#include "Game.hpp"


Render::Render()
{
	layers = std::vector<drawObjects>(aboveLight + 1);
	for (int i = below; i <= aboveLight; i++) {
		layers[i].rtex.create(1920, 1680);
		layers[i].rspr.setTexture(layers[i].rtex.getTexture());
	}
}

void Render::draw(Layer layer, sf::Drawable& drawable, sf::RenderStates states) 
{
	//states.transform.transformPoint(states.transform.)
	layers[layer].rtex.draw(drawable, states);
}

void Render::drawTile(Layer layer, sf::Drawable & drawable, sf::RenderStates states)
{
	states.transform.scale(3.5f, 3.5f);
	layers[layer].rtex.draw(drawable, states);
}

void Render::drawShader(Layer layer, sf::Drawable & drawable, sf::Shader& shader, sf::RenderStates states)
{
	shader.setUniform("selfsprite", sf::Shader::CurrentTexture);
	states.shader = &shader;
	states.transform.scale(3.5f, 3.5f);
	layers[layer].rtex.draw(drawable, states);
}

void Render::drawAll(Game& game)
{
	
	for (int i = below; i <= above; i++) {
		//layers[i].rspr.setScale(game.settings.zoom, game.settings.zoom);
		game.window->draw(layers[i].rspr);
	}

	for (int i = below; i <= above; i++) {
		layers[i].rtex.display();
	}

	for (int i = below; i <= above; i++) {
		layers[i].rtex.clear(sf::Color(0, 0, 0, 0));
	}

}

void Render::drawLast(Game & game)
{
	game.window->draw(layers[aboveLight].rspr);
	layers[aboveLight].rtex.display();
	layers[aboveLight].rtex.clear(sf::Color(0, 0, 0, 0));
}



Render::~Render()
{
}
