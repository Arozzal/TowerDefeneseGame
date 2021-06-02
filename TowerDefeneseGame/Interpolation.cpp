#include "Interpolation.hpp"


Interpolation::Interpolation(int width, int height)
{
	pixelvec = std::vector<sf::Color>(width * height);

	this->height = height;
	this->width = width;

	for (int y = 0; y < height; y+=16){
		for (int x = 0; x < width; x += 16){
			pixelvec[y * width + x].g = rand() % 32;
		}
	}

	for (int y = 0; y < height; y ++) {
		for (int x = 0; x < width; x ++) {
			unsigned char tempinter1 = (y + y % 16) * width + x - x % 16;
			unsigned char tempinter2 = (y + y % 16) * width + x + x % 16;
			pixelvec[y * width + x].g = rand() % 32;
		}
	}
}

Interpolation::~Interpolation()
{
}
