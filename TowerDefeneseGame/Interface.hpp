#pragma once
#include <SFML\Graphics.hpp>
#include "UiButton.hpp"
#include "Game.hpp"
#include "UiDialog.hpp"

class Interface : public sf::Drawable , public sf::Transformable
{
public:
	enum Screen{
		ui,
		uie,
		mainmenu,
		messagebox,
		levelselectscreen
	};

private:

	Screen currentscreen;
	sf::Font gamefont;


	std::map<Screen, std::vector<UiElement*>> uimap;
	std::vector<sf::Text*> textvec;

	UiDialog* statsdialog;

	int unitxbutpos = 0;
	int unitybutpos = 0;

	sf::Vector2f pos;
	sf::Vector2f size;
public:
	Interface();

	void setStatDialog(UiDialog* dia) { this->statsdialog = dia; }
	UiDialog* getStatsDialog() { return statsdialog; }
	sf::Font& getFont() { return gamefont; }
	void setScreen(Screen scr) {currentscreen = scr;};
	Screen getScreen() { return currentscreen; }
	void addToScreen(Screen scr, UiElement& element) { uimap.at(scr).push_back(&element); }
	sf::Text* addLabelToScreen(std::string text, sf::Vector2f pos);

	void setPos(sf::Vector2f pos) { this->pos = pos; }
	void setSize(sf::Vector2f size) { this->size = size; }

	UiElement* useDefaultDesing(UiElement* ele);
	sf::Vector2f getUiPos() { return pos; }
	sf::Vector2f getUisize() { return size; }

	void update(Game& game);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Interface();
};


