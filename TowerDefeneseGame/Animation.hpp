#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	struct Animphase {
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		int rowstart = 0;
		int colstart = 0;

		int animcount;

		int currentanimpos = -1;
		
		float currenttimetonextphase = 0;
		float timetonextphase = 1;

		Animphase(std::string path, int animcount, float timetonextphase = 1, int rowstart = 0, int colstart = 0) {
			image.loadFromFile(path);
			texture.loadFromImage(image);
			sprite.setTexture(texture);

			this->animcount = animcount;
			this->rowstart = rowstart;
			this->colstart = colstart;
			this->timetonextphase = timetonextphase;
		}

		sf::Vector2i size;
		void update(float frametime) {

			currenttimetonextphase -= frametime;

			if (currenttimetonextphase <= 0) {
				currenttimetonextphase = timetonextphase;
				currentanimpos++;
				if (currentanimpos > animcount) {
					currentanimpos = 0;
				}
			}

			sprite.setTextureRect(sf::IntRect(size.x * (colstart + currentanimpos), rowstart * size.y, size.x, size.y));
		}

		sf::Sprite& getImage() {
			return sprite;
		}
	};

	enum Layer {
		down,
		middle,
		top
	};

	static std::map<std::string, Animphase> mainanimlist;

	static void addToMainList(Animphase&, std::string);


private:
	Animphase* layer[3];

	bool enabledlayer[3] = {0,0,0};

	std::map<std::string, Animphase> mylist;

public:
	void addAnimPhase(std::string name);

	void setAnimLayer(std::string name, Layer);
	void enableLayer(bool, Layer);

	void updateAll(float frametime);
	void drawAll(sf::RenderWindow& window);
};

typedef std::pair<std::string, Animation::Animphase> Animpair;