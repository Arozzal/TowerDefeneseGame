#pragma once
#include <string>
#include <sys\types.h>
#include "dirent.h"
#include <vector>
#include <string>
#include "tinyxml2\tinyxml2.h"



class Game;

class Maploader
{
	Maploader() = delete;

	static tinyxml2::XMLDocument* doc;
	static tinyxml2::XMLNode*    node;
	static tinyxml2::XMLElement* coasts;
	static tinyxml2::XMLElement* wavelist;
	static tinyxml2::XMLElement* settings;
	static tinyxml2::XMLElement* levels;
	static tinyxml2::XMLElement* costfirstvalue;

public:

	static void loadGame(std::string, Game& game);
	static void iniWindow(Game& game);
	//static void getFiles(std::string dir, std::vector<std::string>& vec);

	static void saveByteArr(std::string filename, unsigned char* data,int sizex,int sizey);
	static std::vector<std::string> getAllValideFilesFromFolder(std::string path);
	static void clean();
};

