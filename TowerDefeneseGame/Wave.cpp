#include "Wave.hpp"
#include "Game.hpp"


Wave::Wave()
{
	currentpos = 0;
	currenttimer = 0;
}
void Wave::setWave(wavepart waves[], int size)
{
	wavelist = std::vector<wavepart>();

	int d = sizeof(waves);

	for (int i = 0; i < size;++i) {
		wavelist.push_back(waves[i]);
	}

}

void Wave::update(Game & game)
{
	if (end)
		return;

	if (currenttimer <= 0) {
		game.entitylist.push_back(wavelist[currentpos].second);
		wavelist[currentpos].second = nullptr;

		if (currentpos == wavelist.size() - 1) {
			end = true;
			return;
		}

		currentpos++;
		currenttimer = wavelist[currentpos].first;
	}


	currenttimer -= game.frametime;
}

void Wave::resetwaves()
{
	currentpos = 0;
	currenttimer = wavelist[0].first;
}

Wave::~Wave()
{
	for (auto entity : wavelist) {
		delete entity.second;
	}
}
