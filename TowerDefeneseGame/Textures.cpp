#include "Textures.hpp"
#include <iostream>

std::map<std::string, sf::Texture*>* Textures::texturemap = nullptr;



void Textures::addTexture(std::string texturepath, std::string name)
{
	if (texturemap == nullptr) {
		texturemap = new std::map<std::string, sf::Texture*>;
	}

	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(texturepath);
	(*texturemap)[name] = texture;

}

sf::Texture & Textures::getTexture(std::string name)
{
	if (texturemap->find(name) == texturemap->end())
		std::cerr << "Textures: " << name << " not exist" << std::endl;

	return *texturemap->at(name);
}

Textures::~Textures()
{
}
