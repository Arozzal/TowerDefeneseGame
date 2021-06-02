#pragma once
#include<SFML\Graphics.hpp>
class Textures
{
	static std::map<std::string, sf::Texture*>* texturemap;
public:
	Textures() = delete;

	static void addTexture(std::string texture, std::string name);
	static sf::Texture& getTexture(std::string name);

	~Textures();
};

