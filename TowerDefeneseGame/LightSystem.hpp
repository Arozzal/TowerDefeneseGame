#pragma once
#include <SFML\Graphics.hpp>

class Game;
class LightSystem
{
private:
	sf::Texture lightTexture;
	sf::Sprite light;

	sf::RenderTexture lightMapTexture;
	sf::Sprite lightmap;
public:
	struct Light
	{
		sf::Vector2f position;
		sf::Vector2f scale;
		sf::Color color;
		Light() {}
		Light(sf::Vector2f nposition, sf::Vector2f nscale, sf::Color ncolor) :
			position(nposition),
			scale(nscale),
			color(ncolor)
		{
		}
	};
private:
	std::vector<Light*> lights;

public:
	
	

	static LightSystem& get() {
		static LightSystem lsys;
		return lsys;
	}

	static Light* addLight(Light* light) { get().lights.push_back(light); return light; }
	static void init(int xsize, int ysize);
	static void update();
	static void draw(Game& game);
	LightSystem();
	~LightSystem();
};

