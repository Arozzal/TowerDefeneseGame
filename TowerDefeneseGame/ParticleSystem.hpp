#pragma once
#include <sfml\Graphics.hpp>
#include "Textures.hpp"
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	enum parttype {
		points,
		circle
	};
private:

	struct particle {
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	std::vector<particle> particles;
	

	sf::Vector2f emitter;
	sf::VertexArray vertices;
	std::vector<sf::CircleShape> verticescirc;
	sf::Time lifetime;
	sf::Vector2i strawangle = {0, 360};
	sf::Color* ccolors;
	sf::Texture* parttexture = nullptr;
	float* rands;
	int colcounts;
	parttype ptype;


	int speed;
	float cradius = 2;

	sf::Color getNextCol();
	void resetParticle(int index);
public:
	explicit ParticleSystem(int count, sf::Vector2f emitter, sf::Time lifetime, parttype ptype = points);
	void update(sf::Time elapsedtime);
	void setEmitter(sf::Vector2f emitter) { this->emitter = emitter; }
	void setStrawAngle(sf::Vector2i angle) { strawangle = angle; }
	void setSpeed(int speed) { this->speed = speed; }
	void setTexture(std::string path) { this->parttexture = &Textures::getTexture(path); }
	void setColors(int colcounts, sf::Color col1, sf::Color col2 = { 0,0,0,0 }, sf::Color col3 = { 0,0,0,0 }, sf::Color col4 = { 0,0,0,0 }, sf::Color col5 = { 0,0,0,0 }) { this->colcounts = colcounts;
																																											ccolors = new sf::Color[5]{ col1, col2, col3, col4, col5 }; }
	void setColRands(float f1, float f2 = 0, float f3 = 0, float f4 = 0, float f5 = 0) { rands = new float[5] {f1, f2, f3, f4, f5}; }
	void setCircleRadius(float radius) { this->cradius = radius; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

