#include "UiButton.hpp"


#include "Game.hpp"


UiButton::UiButton(int posx, int posy, int sizex, int sizey)
{
	setSize(sizex, sizey);
	setPosition(posx, posy);
}

void UiButton::setContent(sf::Texture& tex, float scale)
{
	consprite.setTexture(tex);
	consprite.setScale(scale, scale);
	imageloaded = true;
}

void UiButton::update(Game & game)
{
	resetColor();
	sf::Color nowcol = getDefaultColor();
	updateUiStats(game);
	if (imageloaded) {
		consprite.setPosition(getPosition().x + getWidth() / 2 - consprite.getGlobalBounds().width / 2 - getImage().getOutlineThickness(), getPosition().y + getHeight() / 2 - consprite.getGlobalBounds().height / 2 - getImage().getOutlineThickness());
	}
	if (isMouseOver()) {
		changeColor(nowcol, 30, 30, 30);
		/*nowcol.r -= 30;
		nowcol.g -= 30;
		nowcol.b -= 30;*/
	
		setColor(nowcol);
	}

	if (isKlicked()) {
		
		changeColor(nowcol, 60, 60, 60);
		/*nowcol.r -= 60;
		nowcol.g -= 60;
		nowcol.b -= 60;*/

		setColor(nowcol);
	}
	if (text.getString().isEmpty() == false) {
		text.setPosition(getPosition().x + getWidth() / 2.f - text.getGlobalBounds().width / 2.f,
						 getPosition().y + getHeight() / 2.f - text.getGlobalBounds().height / 1.7f);

	}

	if (subtext.getString().isEmpty() == false) {
		subtext.setPosition(getPosition().x + getWidth() / 2.f - subtext.getGlobalBounds().width / 2.f,
							getPosition().y + getHeight());
	}

	UiElement& own = *this;
	if (isReleased() && eventmethod != nullptr) {
		eventmethod(game, own);
	}
}

void UiButton::draw(sf::RenderTarget & window)
{
	
	window.draw(getImage());

	if(imageloaded)
	window.draw(consprite);

	if (text.getString().isEmpty() == false)
		window.draw(text);

	window.draw(subtext);
}
