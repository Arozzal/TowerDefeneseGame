#pragma once
#include <vector>
#include "Entity.hpp"

typedef std::pair<float, Entity*> wavepart;

class Wave
{
	std::vector<wavepart> wavelist;
	int currentpos;
	float currenttimer;
	bool end = false;

public:
	explicit Wave();
	explicit Wave(wavepart waves[], int size) { setWave(waves, size); resetwaves(); }
	void setWave(std::vector<wavepart> wavelist) { this->wavelist = wavelist; }
	void setWave(wavepart waves[], int size);
	void addWave(wavepart wave) { wavelist.push_back(wave); }
	void update(Game& game);
	void resetwaves();
	virtual ~Wave();
};

