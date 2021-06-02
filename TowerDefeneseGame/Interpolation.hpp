#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Interpolation
{
	std::vector<sf::Color> pixelvec;
	int width;
	int height;
public:
	Interpolation(int width, int height);
	~Interpolation();
};

