#include "Animation.hpp"

std::map<std::string, Animation::Animphase> Animation::mainanimlist;


void Animation::addToMainList(Animphase & anim, std::string name)
{
	mainanimlist.insert(Animpair(name, anim));
}

void Animation::addAnimPhase(std::string name)
{
	auto item = mainanimlist.find(name)->second;
	mylist.insert(Animpair(name, item));
}

void Animation::setAnimLayer(std::string name, Layer id)
{
	layer[id] = &mylist.find(name)->second;
}

void Animation::enableLayer(bool state, Layer id)
{
	enabledlayer[id] = state;
}

void Animation::updateAll(float frametime)
{
	for (int i = 0; i < 3; i++) {
		if (enabledlayer[i] == true)
			layer[i]->update(frametime);
	}
}

void Animation::drawAll(sf::RenderWindow & window)
{
	for (int i = 0; i < 3; i++) {
		if (enabledlayer[i] == true)
			window.draw(layer[i]->getImage());
	}
}
