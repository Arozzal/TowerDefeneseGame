#include "Framework.hpp"
#include "Wave.hpp"

void Framework::updateFrametime() {

	float lasttime = game.frametime;
	game.frametime = game.clock->getElapsedTime().asSeconds();


	game.clock->restart();
	
	//std::cout << "Fps: " << (1.f / (game.frametime)) << std::endl;

	if (game.frametime > 1)
		game.frametime = 0.1f;
}

void Framework::initGuiObjects()
{
	game.ui.moneytext = gui.addLabelToScreen("Money", { gui.getUisize().x, 0 });
	game.ui.wavetimer = gui.addLabelToScreen("Time", { gui.getUisize().x, 45 });
	game.ui.countedwaves = gui.addLabelToScreen("waves", { gui.getUisize().x, 90 });

	//Ui unit select Buttons.

	for (int i = 0; i < 8; i++) {
		int x = i % 5;
		int y = i == 0 ? 0 : i / 5;
		UiButton* button = new UiButton(gui.getUisize().x + 5 + x * 100, 150 + y * 100, 55, 55);
		gui.useDefaultDesing(button);
		button->setContent(Textures::getTexture(game.settings.unitimages[i]), 3.f);
		if (i == 6 || i == 7)
			button->setContent(Textures::getTexture(game.settings.unitimages[i]), 1.5f);
		button->setDataSize(3);
		button->setData((void*)i, 0);
		button->setSubText(std::to_string(game.settings.costs[i]) + '$');


		button->setData((void*)(int)button->getContent().getTextureRect().width, 1);
		button->setData((void*)(int)button->getContent().getTextureRect().height, 2);
		button->setEvent([this](Game& game, UiElement& own) {
			int ownid = (int)own.getData(0);
			game.settings.newunitxsize = (int)own.getData(1);
			game.settings.newunitysize = (int)own.getData(2);
			game.settings.setID = (Entity::types)ownid;
			gui.getStatsDialog()->makeTooltip(Entity::types(ownid));
			std::cout << "Ui: SetClickID to " << ownid << std::endl;
			game.settings.isUiUnitSelected = true;
		});
		gui.addToScreen(Interface::ui, *button);
	}

	//UI special select buttons

	for (int i = 0; i < 2; i++) {
		int x = i % 5;
		UiButton* button = new UiButton(gui.getUisize().x + 5 + x * 100, gui.getUisize().y - 100, 55, 55);
		gui.useDefaultDesing(button);
		button->setContent(Textures::getTexture(game.settings.objectimages[i]), 3.f);
		button->setDataSize(3);
		button->setData((void*)(i + 100), 0);
		button->setSubText(std::to_string((int)game.settings.constcooldowns[i]));
		button->setData((void*)(int)button->getContent().getTextureRect().width, 1);
		button->setData((void*)(int)button->getContent().getTextureRect().height, 2);
		if (i == 1)
			button->setContent(Textures::getTexture(game.settings.objectimages[i]), 1.5f);
		button->setEvent([this](Game& game, UiElement& own) {
			int ownid = (int)own.getData(0);
			game.settings.newunitxsize = (int)own.getData(1);
			game.settings.newunitysize = (int)own.getData(2);
			game.settings.setID = (Entity::types)ownid;
		});

		button->setUpdateEvent([this](Game& game, UiElement& own) {
			UiButton* ele = static_cast<UiButton*>(&own);
			ele->setSubText(std::to_string((int)game.settings.constcooldowns[int(own.getData(0)) - 100]));
			if (game.settings.constcooldowns[int(own.getData(0))] <= 0)
				ele->setDefaultColor(sf::Color(204, 0, 0, 255));
			else
				ele->setDefaultColor(sf::Color(128, 0, 0, 255));
		});
		gui.addToScreen(Interface::ui, *button);
	}

	//Next wave Button.

	UiButton* button = new UiButton(gui.getUisize().x + 20, 600, gui.getUiPos().x - 40, 100);
	button->setText("Next");
	gui.useDefaultDesing(button);
	button->setEvent([this](Game& game, UiElement& own) {
		//		if (game.getNearest({1.f,1.f}) == nullptr)
		game.settings.wavetimer = 0;
		game.settings.setID = Entity::normal;
	});

	gui.setScreen(Interface::mainmenu);
	gui.addToScreen(Interface::ui, *button);

	//Start Button.

	UiButton* button2 = new UiButton(game.window->getSize().x / 2.f - 250, 150, 500, 100);
	gui.useDefaultDesing(button2);
	button2->setText("Start");
	button2->setEvent([this](Game& game, UiElement& own) {
		game.settings.editmode = false;
		gui.setScreen(Interface::levelselectscreen);
	});
	gui.addToScreen(Interface::mainmenu, *button2);

	//Exit Button

	UiButton* button3 = new UiButton(game.window->getSize().x / 2.f - 250, 300, 500, 100);
	gui.useDefaultDesing(button3);
	button3->setText("Exit");
	button3->setEvent([this](Game& game, UiElement& own) {
		isRunning = false;
	});
	gui.addToScreen(Interface::mainmenu, *button3);

	//Editmode Button.

	UiButton* button4 = new UiButton(game.window->getSize().x / 2.f - 250, 450, 500, 100);
	gui.useDefaultDesing(button4);
	button4->setText("EditMode");
	button4->setEvent([this](Game& game, UiElement& own) {
		game.cleanLevel();
		game.settings.editmode = true;
		gui.setScreen(Interface::levelselectscreen);
	});
	gui.addToScreen(Interface::mainmenu, *button4);

	//Level select screen buttons.

	auto filelist = Maploader::getAllValideFilesFromFolder("sdlvl");

	int butposx = 100;
	int butposy = 100;
	for (std::string file : filelist) {
		UiButton* button = new UiButton(butposx, butposy, 200, 100);
		butposx += 300;
		file.resize(sizeof(file.c_str()) - 4);
		button->setText(file);
		gui.useDefaultDesing(button);
		button->setTextSize(30);
		button->setEvent([this](Game& game, UiElement& own) {
			std::cout << "derp";
			Maploader::loadGame("sdlvl/" + own.getText() + ".xml", game);
			game.settings.pathchanged = true;
			if (game.settings.editmode)
				gui.setScreen(Interface::uie);
			else
				gui.setScreen(Interface::ui);
		});

		gui.addToScreen(Interface::levelselectscreen, *button);
	}

	//UIE edit buttons.

	for (int i = 1; i < 5; i++) {
		int x = i % 5;
		int y = i == 0 ? 0 : i / 5;
		UiButton* button = new UiButton(gui.getUisize().x + 5 + x * 100, 150 + y * 100, 55, 55);
		gui.useDefaultDesing(button);
		button->setContent(Textures::getTexture(game.settings.unitimages[i]), 3.f);
		button->setDataSize(1);
		button->setData((void*)i, 0);
		button->setEvent([this](Game& game, UiElement& own) {
			int ownid = (int)own.getData(0);
			game.settings.newunitxsize = (int)own.getData(1);
			game.settings.newunitysize = (int)own.getData(2);
			game.settings.editblockid = (Entity::types)ownid;
			std::cout << "Ui: Set EditId to " << ownid << std::endl;
		});
		gui.addToScreen(Interface::uie, *button);
	}

	//Dialog for mob stats

	UiDialog* dialog = new UiDialog(gui.getUisize().x + 20, 350, 300, 200);
	gui.useDefaultDesing(dialog);
	dialog->setText(" Power 1\n Recharge Time 2\n Bullet Speed 3");
	dialog->makeTooltip(Entity::normal);
	dialog->setVisible(true);
	gui.setStatDialog(dialog);
	gui.addToScreen(Interface::ui, *dialog);

	//Messagebox to leave the screen.

	UiMessageBox* messagebox = new UiMessageBox(game.window->getSize().x / 2.f - 500.f, game.window->getSize().y / 2.f - 200.f, 1000.f, 400.f);
	gui.useDefaultDesing(messagebox);
	messagebox->setBackColor(sf::Color(127, 127, 127, 255));
	messagebox->setText("Do you want exit?");
	messagebox->setButton1Text("Yes");
	messagebox->setButton2Text("No");

	messagebox->setButton1Event([this](Game& game, UiElement& messagebox) {gui.setScreen(Interface::mainmenu); });
	messagebox->setButton2Event([this](Game& game, UiElement& messagebox) {
		if (game.settings.editmode == false)
			gui.setScreen(Interface::ui);
		else
			gui.setScreen(Interface::uie);
	});

	gui.addToScreen(Interface::messagebox, *messagebox);

	gui.setScreen(Interface::mainmenu);
}

void Framework::initEntityData()
{
	EntityData::UnitData unit1("Unit1",50);
	EntityData::addUnitData(unit1, Entity::types::normal);

	EntityData::UnitData unit2("Unit2", 75);
	EntityData::addUnitData(unit2, Entity::types::goo);

	EntityData::UnitData unit3("Unit3", 100);
	EntityData::addUnitData(unit3, Entity::types::bomb);

	EntityData::UnitData lassertower("LasserTower", 25);
	EntityData::addUnitData(lassertower, Entity::types::lassertower);

	EntityData::UnitData rocketthrower("RocketThrower", 65);
	EntityData::addUnitData(rocketthrower, Entity::types::rocketthrower);

	EntityData::UnitData unitflying("UnitFlying", 65);
	EntityData::addUnitData(unitflying, Entity::types::flying);

	EntityData::UnitData blockbuilder("BlockBuilder", 0);
	EntityData::addUnitData(blockbuilder, Entity::types::construction);

	EntityData::UnitData nuclearlauncher("NuclearConstruction", 0);
	EntityData::addUnitData(nuclearlauncher, Entity::types::constructionatom);


	EntityData::BulletData rocket(50, 2, "Rocket", "");
	EntityData::addBulletData(rocket, Entity::types::normal);

	EntityData::BulletData goo(35, 1, "GooBall", "slow");
	EntityData::addBulletData(goo, Entity::types::goo);

	EntityData::BulletData bomb(30, 1, "MegaBomb", "giant aoe Dmg!");
	EntityData::addBulletData(bomb, Entity::types::bomb);

	EntityData::BulletData bulletlassertower(0, 1, "", "Tiny aoe Dmg");
	EntityData::addBulletData(bulletlassertower, Entity::types::lassertower);

	EntityData::BulletData bulletrocketthrower(50, 1, "FireRocket", "");
	EntityData::addBulletData(bulletrocketthrower, Entity::types::rocketthrower);

	EntityData::BulletData bulletflying(250, 1, "Rocket", "Flying Bullet");
	EntityData::addBulletData(bulletflying, Entity::types::flying);

	EntityData::BulletData nuclearbomb(50, 10, "Atom Bomb", "");
	EntityData::addBulletData(nuclearbomb, Entity::types::constructionatom);
}

Framework::Framework()
{
	Textures::addTexture("images/explosion.png", "Explosion");
	Textures::addTexture("images/electricity.png", "Electricity");
	Textures::addTexture("images/bombexplosion.png", "BombExplosion");
	Textures::addTexture("images/Cartiny.png", "CarTiny");
	Textures::addTexture("images/Car.png", "Car");
	Textures::addTexture("images/sphere.png", "Sphere");
	Textures::addTexture("images/tank1.png", "TankNormal");
	Textures::addTexture("images/tank2.png", "TankStrong");
	Textures::addTexture("images/unit1.png", "Unit1");
	Textures::addTexture("images/unit2.png", "Unit2");
	Textures::addTexture("images/unit3.png", "Unit3");
	Textures::addTexture("images/lassertower.png", "LasserTower");
	Textures::addTexture("images/Rocket.png", "Rocket");
	Textures::addTexture("images/GooBall.png", "GooBall");
	Textures::addTexture("images/Megabomb.png", "MegaBomb");
	Textures::addTexture("images/bulletdummy.png", "PartCirc");
	Textures::addTexture("images/Rocketthrower.png", "RocketThrower");
	Textures::addTexture("images/Firerocket.png", "FireRocket");
	Textures::addTexture("images/fireparticle.png", "FireParticle");
	Textures::addTexture("images/plane1.png", "PlaneNormal");
	Textures::addTexture("images/towerflyingnormal.png", "UnitFlying");
	Textures::addTexture("images/platform.png", "Platform");
	Textures::addTexture("images/fort.png", "Fort");
	Textures::addTexture("images/blockbuilder.png", "BlockBuilder");
	Textures::addTexture("images/ice_floor.png", "IceFloor");
	Textures::addTexture("images/wall.png", "Wall");
	Textures::addTexture("images/walldestroyed.png", "WallDestroyed");
	Textures::addTexture("images/light.png", "Light");
	Textures::addTexture("images/AtomRocket.png", "AtomRocket");
	Textures::addTexture("images/constructionnuclearrocket.png", "NuclearConstruction");
	Textures::addTexture("images/flyingBomb.png", "FlyingBomb");							

	initEntityData();
	
	logstream.open("log/log.txt");
	logstream.flags(std::ios::app);

	std::cerr.rdbuf(logstream.rdbuf());

	LightSystem::init(1600, 900);

	game.floorshader.loadFromFile("shader.frag", sf::Shader::Fragment);

	game.settings.windowsize = sf::Vector2u(1600, 900);
	Maploader::loadGame("test4.xml", game);
	Maploader::iniWindow(game);
	
	//Interpolation inter(game.window->getSize().x, game.window->getSize().y);


	int sizymap = game.map.getYSize();
	int sizxmap = game.map.getXSize();

	game.window->setFramerateLimit(30);
	game.window->setVerticalSyncEnabled(true);
	game.event = new sf::Event;
	
	game.astar = new AStar();
	

	auto animtemp = new Animation::Animphase("images/explosion.png", 5, 0.5f);
	animtemp->size = sf::Vector2i(16, 16);

	auto animtemp2 = new Animation::Animphase("images/electricity.png", 5, 0.5f);
	animtemp2->size = sf::Vector2i(32, 32);

	Animation::addToMainList(*animtemp, "explosion");
	Animation::addToMainList(*animtemp2, "electricity");

	
	game.render = new Render();
	


	game.shader = new sf::VertexArray[game.map.getXSize() * game.map.getYSize()];

	game.grid = new sf::VertexArray[game.map.getXSize() + game.map.getYSize()];
	
	


	for (int y = 0; y < game.map.getXSize(); y++) {
		game.grid[y] = sf::VertexArray(sf::PrimitiveType::Lines, 2);
		game.grid[y][0].position = { y * 16.f, 0 };
		game.grid[y][1].position = { y * 16.f, game.map.getYSize() * 16.f };
		game.grid[y][0].color = { 128, 0, 0, 255 };
		game.grid[y][1].color = { 128, 0, 0, 255 };
	}

	for (int x = 0; x < game.map.getYSize(); x++) {
		int yadd = game.map.getXSize();
		game.grid[x + yadd] = sf::VertexArray(sf::PrimitiveType::Lines, 2);
		game.grid[x + yadd][0].position = { 0, x * 16.f };
		game.grid[x + yadd][1].position = { game.map.getXSize() * 16.f, x * 16.f };
		game.grid[x + yadd][0].color = { 128, 0, 0, 255 };
		game.grid[x + yadd][1].color = { 128, 0, 0, 255 };
	}			

	
	for (int y = 2; y < sizymap * 16;y+=16) {
		for (int x = 2; x < sizxmap*16; x+=16) {

			int i = y / 16 * sizxmap + x / 16;

			game.shader[i] = sf::VertexArray(sf::PrimitiveType::Quads, 4);

			game.shader[i][0].position = { x + 0.f , y + 0.f};
			game.shader[i][1].position = { x + 16.f, y + 0.f};
			game.shader[i][2].position = { x + 16.f, y + 16.f};
			game.shader[i][3].position = { x + 0.f , y + 16.f};

			for (int d = 0; d < 4; d++) {
				game.shader[i][d].color = { 0,0,0,200 };
			}

		}
	}

	game.view = new sf::View(sf::Vector2f( 0,0 ), sf::Vector2f(game.map.getXSize(), game.map.getYSize()));
	
	game.settings.editmode = true;

	game.clock = new sf::Clock;
	
	game.fort = new Fort(game);

	gui.setPos(sf::Vector2f(game.window->getSize().x - game.map.getXSize() * 16 * game.settings.zoom , 0));
	gui.setSize(sf::Vector2f(game.window->getSize().x - gui.getUiPos().x, game.window->getSize().y));

	initGuiObjects();
}

void Framework::run()
{
	updateFrametime();
	srand(time(NULL));

	sf::Event::EventType evtype = sf::Event::Count;

	if (gui.getScreen() == Interface::ui || gui.getScreen() == Interface::uie) {
		while (game.window->pollEvent(*game.event)) {

			if (game.event->type == sf::Event::Closed)
				isRunning = false;

			if (game.inputblocked == false)
				evtype = game.event->type;
			else
				evtype = sf::Event::Count;

			if (game.settings.editmode)
				updateEditMode(evtype);
			else {
				
				update(evtype);
			}
		}

		if(game.settings.editmode == false)
		updateMainGame();
	}


		

	
	
	if (game.inputblocked) {
		if (game.blocktimer <= 0)
			game.inputblocked = false;

		game.blocktimer -= game.frametime;
	}

	gui.update(game);
	LightSystem::update();

	game.window->clear(sf::Color(30, 30, 30, 127));

	if (gui.getScreen() == Interface::ui || gui.getScreen() == Interface::messagebox || gui.getScreen() == Interface::uie) {
		draw();
	}

	
	game.window->draw(gui);
	game.window->display();
}



void Framework::update(sf::Event::EventType type)
{

		if (game.event->type == sf::Event::KeyReleased && game.event->key.code == sf::Keyboard::Escape) {
			gui.setScreen(Interface::messagebox);
			game.settings.isUiUnitSelected = false;
		}

		switch (game.event->type) {
			

		case sf::Event::MouseButtonReleased:

			sf::Vector2f mousepos = game.getMouseMapPos() / 16.f;

			std::cout << mousepos.x << " " << mousepos.y  << std::endl; 

			if (game.event->type == sf::Event::MouseButtonReleased) {
				if (game.event->mouseButton.button == sf::Mouse::Button::Right)
					game.settings.isUiUnitSelected = false;


				else if (game.settings.setID == 100 && game.map(mousepos.x, mousepos.y) == 0 &&
					game.getNearest({ 0,0 }) == nullptr  && game.settings.constcooldowns[0] <= 0) {
					
					game.settings.constcooldowns[0] = 300.f;
					game.map(mousepos.x, mousepos.y) = 3;
					game.settings.lastplacedblock = (sf::Vector2i)mousepos;
					if (game.astar->calculateAStar(game, { 0,3 })) {
						game.map(mousepos.x, mousepos.y) = 3;
						game.settings.pathchanged = true;
					}
					else {
						game.map(mousepos.x, mousepos.y) = 0;
						game.settings.constcooldowns[0] = 0;
					}
					
				}
				else if (game.settings.setID == 101  && game.settings.constcooldowns[1] <= 0){
					auto bul = new BulletAtomBomb(Entity::atom, game.getMouseMapPos());
					bul->setPos({ 0, 0 });
					game.entitylist.push_back(bul);
					game.settings.constcooldowns[1] = 300;
				}

				else if (game.map.isValidePosition(mousepos.x, mousepos.y) && game.map.isUsed(mousepos.x, mousepos.y, game.settings.newunitxsize / 16.f, game.settings.newunitysize / 16.f) == false) {
					


					if (game.settings.money >= game.settings.costs[game.settings.setID]) {
						game.entitylist.push_back(new Unit(mousepos.x, mousepos.y, game.settings.setID));
						game.settings.money -= game.settings.costs[game.settings.setID];
						sf::FloatRect sprsize = game.entitylist.back()->getSprite().getGlobalBounds();
						game.map.useField(mousepos.x, mousepos.y, true,game.settings.newunitxsize / 16.f, game.settings.newunitysize / 16.f);
					}
				}
			}
			break;
		}
}


void Framework::updateMainGame()
{
	std::vector<Entity*>::size_type size = game.entitylist.size();

	for (std::vector<Entity*>::size_type i = 0; i < size; ++i) {
		game.entitylist[i]->update(game);

		if (game.entitylist[i]->canDestroy()) {
			game.settings.money += game.entitylist[i]->getMyMoney();
			try {
				if (game.entitylist[i]->entitytypeID == Entity::Unittype)
					game.map.useField(game.entitylist[i]->getPos().x , game.entitylist[i]->getPos().y, false,  
						game.entitylist[i]->getSprite().getGlobalBounds().width / 16.f, game.entitylist[i]->getSprite().getGlobalBounds().height / 16.f);

				delete game.entitylist[i];
				game.entitylist[i] = nullptr;
				game.entitylist.erase(game.entitylist.begin() + i);
				size--;
			}
			catch (std::out_of_range) {
				std::cerr << "Framework: out of range" << std::endl;
			}
		}
	}


	if (game.settings.wavetimer <= 0) {
		if (game.settings.wavepos < game.settings.wavecount - 1)
			game.settings.wavepos++;


		game.settings.wavetimer = game.settings.basetimer;
	}

	game.settings.wavetimer -= game.frametime;

	game.fort->update(game);

	if (game.settings.wavepos >= 0)
		game.wavelist[game.settings.wavepos]->update(game);



	game.ui.wavetimer->setString("Time: " + std::to_string((int)game.settings.wavetimer) + "s");
	game.ui.countedwaves->setString("Waves: " + std::to_string(game.settings.wavepos + 1) + "/" + std::to_string(game.settings.wavecount));


	game.ui.moneytext->setString("Money: " + std::to_string(game.settings.money) + "$");
	
}


void Framework::updateEditMode(sf::Event::EventType type)
{
	sf::Vector2f mousepos = game.getMouseMapPos() / 16.f;

	if (game.event->type == sf::Event::KeyReleased && game.event->key.code == sf::Keyboard::Escape) {
		gui.setScreen(Interface::messagebox);
	}

	switch (type) {
		case sf::Event::MouseButtonReleased:
			if(game.event->mouseButton.button == sf::Mouse::Button::Left)
				game.map(mousepos.x, mousepos.y) = game.settings.editblockid;
			if (game.event->mouseButton.button == sf::Mouse::Button::Right)
				game.map(mousepos.x, mousepos.y) = 0;
			break;
		case sf::Event::KeyReleased:
			if (game.event->key.code == sf::Keyboard::Escape) {
				Maploader::saveByteArr(game.settings.currentlevel, game.map.getFirst(), game.map.getXSize(), game.map.getYSize());
			}
			break;
	}

}

void Framework::draw()
{
	game.view->reset({ 0,0,1600,900 });
	game.view->zoom(1 / game.settings.zoom);
	game.view->setCenter( 1600 / (game.settings.zoom * 2), 900 / (game.settings.zoom * 2));

	game.window->setView(*game.view);

	for (int y = 0; y < game.map.getYSize(); y++) {
		for (int x = 0; x < game.map.getXSize(); x++) {
			game.background.setPosition(x * 16, y * 16);
			
			//game.background.setColor({ unsigned char (rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255),255 });

			game.render->drawShader(Render::floor, game.background, game.floorshader);
			
		}
	}
	
	for (int y = 0; y < game.map.getYSize(); y++) {
		for (int x = 0; x < game.map.getXSize(); x++) {
			if (game.map(x, y) != 1 && game.map(x, y) != 3)continue;
			game.render->drawTile(Render::shadows, game.shader[y * game.map.getXSize() + x]);
		}
	}

	static float watterframe = 0;

	for (int y = 0; y < game.map.getYSize(); y++) {
		for (int x = 0; x < game.map.getXSize(); x++) {
			if (game.map(x, y) != 2)continue;

				watterframe += game.frametime;
			if (watterframe >= 3 || watterframe < 0)
				watterframe = 0;

			sf::Sprite spr(game.map.getTileById(game.map.getTileIdWatter(x, y), game.watersprite, watterframe));
			spr.setPosition(x * 16, y * 16);

			game.render->drawTile(Render::blocks, spr);
		}
	}

	
	sf::Sprite spr;

	for (int y = 0; y < game.map.getYSize(); y++) {
		for (int x = 0; x < game.map.getXSize(); x++) {

			if (game.map(x, y) == 3) {
				spr = sf::Sprite(Textures::getTexture("Platform"));
				spr.setPosition(x * 16, y * 16);
				game.render->drawTile(Render::blocks, spr);
			}

			if (game.map(x, y) != 1)continue;

			spr = (game.map.getTileById(game.map.getTileId(x, y)));
			spr.setPosition(x * 16, y * 16);

			//spr.setColor({ byte(rand() % 255), byte(rand() % 255), byte(rand() % 255),255 });
			game.render->drawTile(Render::blocks, spr);
		}
	}
	


	for (Entity* entity : game.entitylist) {
		entity->draw(game);
	}

	game.fort->draw(game);
	
	sf::Sprite msspr;

	if (game.settings.isUiUnitSelected) {
		msspr.setTexture(Textures::getTexture(game.settings.unitimages[game.settings.setID]));
		sf::Vector2i mspos(game.getMouseUiPos());
		mspos -= sf::Vector2i(mspos.x % 16 - msspr.getGlobalBounds().width / 2.f, mspos.y % 16 - msspr.getGlobalBounds().height / 2.f);
		msspr.setPosition(mspos.x - msspr.getGlobalBounds().width / 2.f, mspos.y - msspr.getGlobalBounds().height / 2.f);
		game.render->drawTile(Render::aboveLight, msspr);
		for (int i = 0; i < game.map.getXSize() + game.map.getYSize(); i++) {
			game.render->drawTile(Render::aboveLight, game.grid[i]);
		}
	}


	game.window->setView(game.window->getDefaultView());
	game.render->drawAll(game);
	if(game.settings.darkness)
	LightSystem::draw(game);
	game.render->drawLast(game);
}


Framework::~Framework()
{
	
	for (Entity* entity : game.entitylist) {
		delete entity;
	}

	for (Wave* wave : game.wavelist) {
		delete wave;
	}


	delete[] game.settings.costs;
	delete[] game.shader;
	delete[] game.settings.unitimages;
	delete[] game.grid;

	delete game.event;
	delete game.view;
	delete game.clock;
	delete game.window;
	delete game.render;

	Maploader::clean();

	logstream.close();
}