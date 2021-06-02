#include "ParticleSystem.hpp"

#include <iostream>




ParticleSystem::ParticleSystem(int count, sf::Vector2f emitter, sf::Time lifetime, parttype ptype)
{
	if (ptype == points)
		this->vertices = sf::VertexArray(sf::PrimitiveType::Points, count);
	else
		this->verticescirc = std::vector<sf::CircleShape>(count);

	this->lifetime = lifetime;
	this->emitter = emitter;
	this->particles = std::vector<particle>(count);
	this->ptype = ptype;
}

void ParticleSystem::update(sf::Time elapsedtime)
{
	for (int i = 0; i < particles.size(); ++i) {
		particle& p = particles[i];

		p.lifetime -= elapsedtime * float(rand() % 2);

		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i);

		float alpha =  (lifetime.asSeconds() / p.lifetime.asSeconds());
		auto c = getNextCol();

		if (ptype == points) {
			vertices[i].color.a = static_cast<sf::Uint8>(alpha * 255);
			vertices[i].position += p.velocity * elapsedtime.asSeconds();
		}
		else if (ptype == circle) {
			verticescirc[i].setPosition(verticescirc[i].getPosition() + p.velocity * elapsedtime.asSeconds());
			verticescirc[i].setFillColor(sf::Color(c.r, c.g, c.b, alpha * 255));
		}
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;
	//states.transform.scale(10.f, 10.f);
	//auto view = target.getDefaultView();
	//target.setView(target.getDefaultView());

	if (ptype == points)
		target.draw(vertices, states);
	else if (ptype == circle) {
		for (int i = 0; i < particles.size(); ++i) {
			target.draw(verticescirc[i], states);
		}
	}
		
	//target.setView(view);
}

sf::Color ParticleSystem::getNextCol()
{
	int ranin = rand() % 100;

	int sum = 0;
	for (int i = 0; i <= colcounts; i++) {
		sum += rands[i];
		if (ranin <= sum) {
			return ccolors[i];
		}
	}

	std::cerr << "ParticleSystem: No Random Color found!\n";
	return sf::Color();
}

void ParticleSystem::resetParticle(int index)
{
	if (ptype == points)
		vertices[index].position = emitter;
	else if (ptype == circle) {
		verticescirc[index].setPosition(emitter);
		verticescirc[index].setRadius(cradius);
		verticescirc[index].setOrigin(cradius / 2.f, cradius / 2.f);
		if(parttexture != nullptr)
		verticescirc[index].setTexture(parttexture);
	}

	if (strawangle.y != 0) {
		float angle = (std::rand() % strawangle.y + strawangle.x) * 3.141 / 180;
		float speed = (std::rand() % this->speed);
		particles[index].lifetime = lifetime + sf::milliseconds((rand() % lifetime.asMilliseconds() - lifetime.asMilliseconds() / 2));
		particles[index].velocity = { cos(angle) * speed, sin(angle) * speed };
	}
}

