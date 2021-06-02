#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <functional>
typedef unsigned char byte;

class Map
{
	byte* data = nullptr;
	bool* isused = nullptr;

	int sizex;
	int sizey;
	byte nullbyte = 0;
	sf::Texture maptexture;
	sf::Sprite mapsprite;
public:
	explicit Map(int sizex, int sizey, std::string path = "");
	Map() {}

	int getXSize() { return sizex; }
	int getYSize() { return sizey; }
	int getSize() { return sizex * sizey; }
	byte getTileId(int x, int y);
	byte getTileIdWatter(int x, int y);
	sf::Sprite& getTileById(int id);
	sf::Sprite& getTileById(int id, sf::Sprite&, int frame = 0);

	void load(byte*, int , int);
	void setSize(int x, int y);
	void setTexture(std::string path) { maptexture.loadFromFile(path); mapsprite.setTexture(maptexture);};

	void iterateOverMap(std::function<void(int x, int y)> function);

	static bool isColliding(Map& map, sf::FloatRect& box, sf::Vector2i pos);

	bool isOutside(int x, int y);


	bool isUsed(int x, int y, int xlength = 1, int ylength = 1);
	void useField(int x, int y, bool use, int xlength = 1, int ylength = 1);

	byte* getFirst() { return data; }
	byte& operator()(int x, int y);
	bool isValidePosition(int x, int y);
	byte at(int x, int y, bool noerr = false);

	~Map();
};

