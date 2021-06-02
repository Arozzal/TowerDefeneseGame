#pragma once
#include <functional>
#include <SFML\Graphics.hpp>
class Game;
class UiElement;
typedef std::function<void(Game& game, UiElement& own)> UiFunction;


class UiElement
{
	UiFunction updateevent = nullptr;
	sf::RectangleShape image;
	sf::Color defaultcolor;
	bool mouseover = false;
	bool klicked = false;
	bool released = false;
	void** data;	
protected:
	sf::Text text;
public:
	void setSize(float sizex, float sizey) { image.setSize({ sizex, sizey }); }
	virtual void setPosition(float posx, float posy) { image.setPosition(posx, posy); }

	void setText(std::string text) { this->text.setString(text); }
	std::string getText() { return text.getString(); }
	virtual void setFont(sf::Font* font) { this->text.setFont(*font); }
	virtual void setTextSize(int size) { text.setCharacterSize(size); }
	virtual void setBorder(int bordersize) { image.setOutlineThickness(bordersize); }
	virtual void setBorderColor(sf::Color col) { image.setOutlineColor(col); }
	virtual void setColor(sf::Color color) { image.setFillColor(color); }
	virtual void setDefaultColor(sf::Color color) { this->defaultcolor = color; image.setFillColor(color); }
	void resetColor() { image.setFillColor(defaultcolor); }
	

	sf::Color getDefaultColor() { return defaultcolor; }

	void changeColor(sf::Color& col, char r, char g, char b);
	void setDataSize(int size) { this->data = new void*[size]; }
	void setData(void* data, int pos) { this->data[pos] = data; }
	void* getData(int pos) { return this->data[pos]; }

	void setUpdateEvent(UiFunction func) { this->updateevent = func; }

	bool isMouseOver() { return mouseover; }
	bool isKlicked() { return klicked; }

	bool isReleased() { return released; }

	void setMouseOver(bool over) { this->mouseover = over; if(over == false)setKlicked(false); }
	void setKlicked(bool klicked) { this->klicked = klicked; }

	float getWidth() { return image.getGlobalBounds().width; }
	float getHeight() { return image.getGlobalBounds().height; }

	sf::RectangleShape getImage() { return image; }

	sf::Vector2f getPosition() { return image.getPosition(); }

	void updateUiStats(Game& game);
	void drawShadow(sf::RectangleShape&, sf::RenderTarget&);

	virtual void draw(sf::RenderTarget& window) { window.draw(image); }
	virtual void update(Game& game) = 0;
};

