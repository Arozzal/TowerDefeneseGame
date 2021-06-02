#include "Map.hpp"

Map::Map(int sizex, int sizey, std::string path)
{
	this->sizex = sizex;
	this->sizey = sizey;
	data = new byte[sizex * sizey];
	memset(data, 0, sizex * sizey * sizeof(byte));
	data[3] = 1;
	isused = new bool[sizex * sizey];
	memset(isused, 0, sizex * sizey * sizeof(bool));

	if (path != "") {
		maptexture.loadFromFile(path);
		mapsprite.setTexture(maptexture);
	}
}

byte Map::getTileId(int x, int y)
{
	byte id = 0;

	if (at(x, y-1, true) == 0){
		id |= 0b1;
	}

	if (at(x + 1, y, true) == 0) {
		id |= 0b10;
	}

	if (at(x, y + 1, true) == 0) {
		id |= 0b100;
	}

	if (at(x - 1, y, true) == 0) {
		id |= 0b1000;
	}

	return id;
}

byte Map::getTileIdWatter(int x, int y)
{
	byte  id = 0;
	if (at(x - 1, y, true) == 0) {
		if (at(x, y - 1, true) == 0) {
			id = 0;
		}else if (at(x, y + 1, true) == 0) {
			id = 6;
		}
		else {
			id = 3;
		}

		return id;
	}else if (at(x + 1, y, true) == 0) {
		if (at(x, y - 1, true) == 0) {
			id = 2;
		}
		else if (at(x, y + 1, true) == 0) {
			id = 8;
		}
		else {
			id = 5;
		}

		return id;
	}
	else {
		if (at(x, y - 1, true) == 0) {
			id = 1;
		}
		else if (at(x, y + 1, true) == 0) {
			id = 7;
		}
		else {
			id = 4;
		}

		return id;
	}


	return byte();
}

sf::Sprite & Map::getTileById(int id)
{
	int xpos = id % 4;
	int ypos = id / 4;

	mapsprite.setTextureRect({ xpos * 16, ypos * 16, 16, 16 });
	return mapsprite;
}

sf::Sprite & Map::getTileById(int id, sf::Sprite & tex, int frame)
{
	int xpos = id % 3;
	int ypos = id / 3;


	tex.setTextureRect({ xpos * 16 + frame * 16 * 3, ypos * 16, 16, 16 });
	return tex;
}

void Map::load(byte* arr, int sizex, int sizey)
{
	delete[] data;
	delete[] isused;

	this->sizex = sizex;
	this->sizey = sizey;

	data = new byte[sizex * sizey];

	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {


			if (arr[y * sizex + x] >= '0')
				arr[y * sizex + x] -= '0';

			std::cout << arr[y * sizex + x];

			data[y * sizex + x] = arr[y * sizex + x];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	

	isused = new bool[sizex * sizey];
	memset(isused, 0, sizex * sizey * sizeof(bool));
}

void Map::setSize(int x, int y)
{
	Map(x,y);
}

void Map::iterateOverMap(std::function<void(int x, int y)> function)
{
	for (int y = 0; y < getYSize(); y++) {
		for (int x = 0; x < getXSize(); x++) {
			function(x, y);
		}
	}
}

bool Map::isColliding(Map & map, sf::FloatRect & box, sf::Vector2i pos)
{
	
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			if (map(pos.x + x, pos.y + y) != 0) {
				if (box.intersects(sf::FloatRect( (pos.x + x) * 16,(pos.y + y) * 16,16,16 )))
					return true;
			}
		}
	}


	return false;
}

bool Map::isOutside(int x, int y)
{
	
	return (x < 0 || x > getXSize() || y < 0 || y > getYSize());
}

bool Map::isUsed(int x, int y, int xlength, int ylength)
{
	for (int fx = 0; fx < xlength; ++fx) {
		for (int fy = 0; fy < ylength; ++fy) {
			if (isOutside(x + fx, y + fy))
				return true;
			if (isValidePosition(x + fx, y + fy) == false)
				return true;
			if (isused[(y + fy) * sizex + (x + fx)])
				return true;
		}
	}

	return false;
}

void Map::useField(int x, int y, bool use, int xlength, int ylength)
{
	for (int fx = 0; fx < xlength; ++fx) {
		for (int fy = 0; fy < ylength; ++fy) {
			isused[(fy + y) * sizex + (fx + x)] = use;
		}
	}
}


byte & Map::operator()(int x, int y)
{
	if (x < 0 || x > getXSize() || y < 0 || y > getYSize()) {
		std::cout << "Map: outside Array range X: " << x << " Y: " << y << std::endl;
		return nullbyte;
	}

	return data[y * sizex + x];
}

bool Map::isValidePosition(int x, int y)
{
	if (at(x, y) == 1 || at(x, y) == 3)
		return true;
	return false;
}

byte Map::at(int x, int y, bool noerr)
{
	if (x < 0 || x >= getXSize() || y < 0 || y >= getYSize()) {
		if(noerr == false)
		std::cout << "Map: outside Array range X: " << x << " Y: " << y << std::endl;
		return -1;
	}

	return data[y * sizex + x];
}

Map::~Map()
{
	delete[] data;
	delete[] isused;
}
