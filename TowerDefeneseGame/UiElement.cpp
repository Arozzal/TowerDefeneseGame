#include "UiElement.hpp"
#include "Game.hpp"

void UiElement::changeColor(sf::Color & col, char r, char g, char b)
{
	if (col.r - r < 0)
		col.r = 0;
	else if (col.r - r > 255)
		col.r = 255;
	else
		col.r -= r;

	if (col.g - g < 0)
		col.g = 0;
	else if (col.g - g > 255)
		col.g = 255;
	else
		col.g -= g;

	if (col.b - b < 0)
		col.b = 0;
	else if (col.b - b > 255)
		col.b = 255;
	else
		col.b -= b;
}

void UiElement::updateUiStats(Game& game)
{
	sf::Vector2i mpos = sf::Mouse::getPosition(*game.window);
	released = false;

	if (mpos.x > getPosition().x && mpos.x < getPosition().x + getWidth() && mpos.y > getPosition().y && mpos.y < getPosition().y + getHeight()) {
		setMouseOver(true);
	}
	else {
		if (klicked)
			released = true;
		setMouseOver(false);
	}

	if (mouseover) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (game.inputblocked == false) {
				setKlicked(true);
				game.inputblocked = true;
				game.blocktimer = 0.3f;
			}
		}
		else {
			if (klicked) {
				released = true;
				game.inputblocked = true;
				game.blocktimer = 0.3f;
			}
			setKlicked(false);
		}
	}

	if (updateevent != nullptr)
		updateevent(game, *this);
}

void UiElement::drawShadow(sf::RectangleShape& drawing, sf::RenderTarget& window)
{
	auto col = drawing.getFillColor();
	auto col2 = drawing.getOutlineColor();
	drawing.setFillColor({ 0,0,0,127 });
	drawing.setOutlineColor({ 0,0,0,127 });
	drawing.move(16, 16);
	window.draw(drawing);
	drawing.move(-16, -16);
	drawing.setFillColor(col);
	drawing.setOutlineColor(col2);
}
