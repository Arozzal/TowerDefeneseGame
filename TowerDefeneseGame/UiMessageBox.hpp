#pragma once

#include <SFML\Graphics.hpp>
#include "UiElement.hpp"
#include "UiButton.hpp"
#include "Game.hpp"

class UiMessageBox : public UiElement
{

	sf::RectangleShape messagesquare;

	UiButton button1;
	UiButton button2;

	std::function<void(Game& game, UiElement& own)> evmethodbutton1;
	std::function<void(Game& game, UiElement& own)> evmethodbutton2;

	bool firstClicked;
	bool secondClicked;
public:

	UiMessageBox(float posx, float posy, float sizex, float sizey);
	~UiMessageBox();

	virtual void setFont(sf::Font* font)override;
	virtual void setTextSize(int size)override;
	virtual void setBorder(int bordersize)override;
	virtual void setBorderColor(sf::Color col)override;
	virtual void setDefaultColor(sf::Color color) override;

	void setButton1Text(std::string text) { button1.setText(text); }
	void setButton2Text(std::string text) { button2.setText(text); }

	void setButton1Event(std::function<void(Game& game, UiElement& own)> em) { evmethodbutton1 = em; button1.setEvent(em); }
	void setButton2Event(std::function<void(Game& game, UiElement& own)> em) { evmethodbutton2 = em; button2.setEvent(em); }

	void setBackColor(sf::Color col) { this->messagesquare.setFillColor(col); }
	void update(Game& game) override;
	void draw(sf::RenderTarget& window) override;
};

