#pragma once
#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include "Map.hpp"
#include "Mob.hpp"
#include "Unit.hpp"
#include "Bullets.hpp"
#include "UiButton.hpp"
#include "UiMessageBox.hpp"
#include "Animation.hpp"
#include "Maploader.hpp"
#include "Textures.hpp"
#include "ParticleSystem.hpp"
#include "Fort.hpp"
#include "Interface.hpp"
#include "AStar.hpp"
#include "Wall.hpp"
#include "LightSystem.hpp"
#include "Render.hpp"
#include "UiDialog.hpp"
#include "EntityData.hpp"
#include "Interpolation.hpp"

#include <memory>
#include <fstream>

class Framework
{
	Game game;
	Interface gui;
	std::ofstream logstream;
public:
	
	bool isRunning = true;

	void updateFrametime();
	void initGuiObjects();
	void initEntityData();
	explicit Framework();
	void run();
	
	void update(sf::Event::EventType);
	void updateMainGame();
	void updateEditMode(sf::Event::EventType);
	void draw();
	virtual ~Framework();
};

