#pragma once



#include <SFML\Graphics.hpp>

class Game;
class Render
{
public:
	enum Layer {
		below,
		floor,
		down,
		shadows,
		mobdown,
		blocks,
		middle,
		top,
		mobup,
		above,
		aboveLight
	};
private:
	struct drawObjects {
		sf::RenderTexture rtex;
		sf::Sprite rspr;
	};

	sf::RenderStates shaderstats;
	std::vector<drawObjects> layers;

public:
	void draw(Layer layer, sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates::Default);
	void drawTile(Layer layer, sf::Drawable& drawable, sf::RenderStates states = sf::RenderStates::Default);
	void drawShader(Layer layer, sf::Drawable& drawable, sf::Shader& shader, sf::RenderStates states = sf::RenderStates::Default);
	void drawAll(Game& game);
	void drawLast(Game& game);
	Render();
	~Render();
};

