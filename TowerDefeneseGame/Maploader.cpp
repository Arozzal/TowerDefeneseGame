#include "Maploader.hpp"
#include "Game.hpp"
#include "Mobs.hpp"
#include "Wall.hpp"
#include "Wave.hpp"

using namespace tinyxml2;

XMLDocument* Maploader::doc = nullptr;
XMLNode*     Maploader::node = nullptr;
XMLElement*  Maploader::coasts = nullptr;
XMLElement*  Maploader::wavelist = nullptr;
XMLElement*  Maploader::settings = nullptr;
XMLElement*  Maploader::levels = nullptr;
XMLElement*  Maploader::costfirstvalue = nullptr;


void Maploader::loadGame(std::string filename, Game& game)
{
	game.cleanLevel();
	game.settings.levelendpos = { 3,11 };

	delete doc;
	doc = new XMLDocument();
	doc->LoadFile(filename.c_str());

	node = doc->FirstChild();

		


	coasts = node->FirstChildElement("coasts");
	wavelist = node->FirstChildElement("wavelist");
	settings = node->FirstChildElement("settings");
	levels = node->FirstChildElement("levels");
	costfirstvalue = coasts->FirstChildElement("value");


	
	float basetimer;
	int startmoney;
	settings->QueryFloatAttribute("basetimer", &basetimer);
	game.settings.basetimer = basetimer;
	settings->QueryIntAttribute("money", &startmoney);
	game.settings.money = startmoney;


	



	XMLElement* level = levels->FirstChildElement("level");
	int lvlxsize;
	int lvlysize;
	level->QueryIntAttribute("xsize", &lvlxsize);
	level->QueryIntAttribute("ysize", &lvlysize);




	std::string str = level->GetText();
	byte* arr = new byte[lvlxsize * lvlysize];
	arr = (byte*)&str.front();
	
	game.map.load(arr, lvlxsize, lvlysize);


	game.settings.costs = new int[10];
	
	for (int i = 0; costfirstvalue != nullptr;++i) {
		int output;
		costfirstvalue->QueryIntText(&output);
		
		game.settings.costs[i] = output;

		costfirstvalue = costfirstvalue->NextSiblingElement("value");
	}

	XMLElement* wave = wavelist->FirstChildElement("wave");

	int wavecounter = 0;

	while (wave != nullptr) {
		wavecounter++;
		XMLElement* wp = wave->FirstChildElement("wp");
		Wave* wavesd = new Wave();
		

		while (wp != nullptr) {
			std::string type = wp->Attribute("type");

			float time;
			wp->QueryFloatAttribute("time", &time);

			sf::Vector2i pos(-99,-99);
			wp->QueryIntAttribute("posx", &pos.x);
			wp->QueryIntAttribute("posy", &pos.y);

			if (pos.x == -99) {
				pos.x = 0;
			}

			if (pos.y == -99) {
				pos.y = 3;
			}

			if (type == "small") {
				wavesd->addWave(wavepart(time, new MobSmallCar(pos.x,pos.y)));
			}
			else if (type == "normal") {
				wavesd->addWave(wavepart(time, new MobGreenTank(pos.x, pos.y)));		
			}																			
			else if (type == "strong") {												
				wavesd->addWave(wavepart(time, new MobTankGray(pos.x, pos.y)));			
			}																			
			else if (type == "tiny") {													
				wavesd->addWave(wavepart(time, new MobVeryTinyCar(pos.x, pos.y)));		
			}																			
			else if (type == "sphere") {												
				wavesd->addWave(wavepart(time, new MobSphere(pos.x, pos.y)));			
			}																			
			else if (type == "planenormal") {											
				wavesd->addWave(wavepart(time, new MobPlane(pos.x, pos.y)));	
			}
			else if (type == "flyingbomb") {
				wavesd->addWave(wavepart(time, new MobFlyingBomb(pos.x, pos.y)));
			}
			else {
				std::cerr << "Maploader: Unknow Mobtype " + type << std::endl;
			}



			wp = wp->NextSiblingElement("wp");
		}


		game.wavelist.push_back(wavesd);
		wave = wave->NextSiblingElement("wave");
	}

	game.settings.wavecount = wavecounter;
	game.settings.wavetimer = game.settings.basetimer;


	game.settings.unitimages = new std::string[8]{
		std::string("Unit1"),
		std::string("Unit2"),
		std::string("Unit3"),
		std::string("LasserTower"),
		std::string("RocketThrower"),
		std::string("UnitFlying"),
		std::string("BlockBuilder"),
		std::string("NuclearConstruction")
	};

	game.settings.objectimages = new std::string[2]{
		std::string("Platform"),
		std::string("AtomRocket"),
	};
	std::string terrainpath = "";

	if (settings->Attribute("tileset") != nullptr) {
		terrainpath = settings->Attribute("tileset");
		game.map.setTexture(terrainpath);
	}else {
		std::cerr << "Maploader: No Terrain Path found!" << std::endl;
	}
	
	if (settings->Attribute("floor") != nullptr) {
		game.backtexture.loadFromFile(settings->Attribute("floor"));
		game.background.setTexture(game.backtexture);
	}
	else {
		std::cerr << "Maploader: No Floor Terrain Path fount!" << std::endl;
	}

	if (settings->Attribute("darkness") != nullptr) {
		std::string darkness = settings->Attribute("darkness");

		if(darkness == "true")
		game.settings.darkness = true;
	}



	game.watertexture.loadFromFile("images/watterterrain.png");
	game.watersprite.setTexture(game.watertexture);
	


	game.settings.currentlevel = filename;
}

void Maploader::iniWindow(Game & game)
{
	std::string isfull = settings->Attribute("fullscreen");
	if (isfull == "true") {
		game.window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 16), "Game", sf::Style::None);
	}
	else {
		game.window = new sf::RenderWindow(sf::VideoMode(1600, 900, 16), "Game", sf::Style::Close);
	}
	game.window->setVerticalSyncEnabled(true);
	game.window->setFramerateLimit(30);
}

std::vector<std::string> Maploader::getAllValideFilesFromFolder(std::string path)
{
	DIR* dir;
	dirent* pdir;
	std::vector<std::string> files;
	dir = opendir(path.c_str());

	while (pdir = readdir(dir)) {
		if (pdir->d_name[0] == '.' || pdir->d_name[1] == '.')
			continue;
		files.push_back(pdir->d_name);
		std::cout << pdir->d_name << std::endl;
	}

	return files;
}

void Maploader::clean()
{
	delete doc;
}

/*void Maploader::getFiles(std::string dir, std::vector<std::string>& files)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}*/


void Maploader::saveByteArr(std::string filename, byte* data, int sizex, int sizey)
{

	XMLElement* levels = node->FirstChildElement("levels");
	XMLElement* level = levels->FirstChildElement("level");

	std::string derp;
	

	for (int i = 0; i < sizex * sizey; ++i) {
		char d = data[i] + '0';
		derp.push_back(d);
	}

	level->SetText(derp.c_str());

	std::cout << "Maploader: Savepath " << filename << std::endl;
	doc->SaveFile(filename.c_str());
}
