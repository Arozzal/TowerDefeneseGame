#pragma once
#include <functional>
#include "UiElement.hpp"
class UiButton : public UiElement
{
	sf::Sprite consprite;

	sf::Text subtext;

	bool imageloaded = false;
	UiFunction eventmethod = nullptr;
public:
	explicit UiButton(int posx, int posy, int sizex, int sizey);
	explicit UiButton() {};
	void setContent(sf::Texture&, float scale = 1.f);
	sf::Sprite& getContent() { return consprite; }

	void setSubText(std::string str) { subtext.setString(str); }
	void setSubTextFont(sf::Font& font) { subtext.setFont(font); }
	void setSubTextSize(int size) { this->subtext.setCharacterSize(size); }

	void update(Game& game) override;
	void draw(sf::RenderTarget& window) override;
	void setEvent(UiFunction eventmethod) { this->eventmethod = eventmethod; }
};

