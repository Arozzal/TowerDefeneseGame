#include "UiMessageBox.hpp"


UiMessageBox::UiMessageBox(float posx, float posy, float sizex, float sizey)
{
	messagesquare.setPosition({ posx, posy });
	messagesquare.setSize({ sizex,sizey });


	button1.setSize(sizex / 3.f, sizey / 3.f);
	button2.setSize(sizex / 3.f, sizey / 3.f);

	button1.setPosition(posx + 25, posy + sizey - 25 - button1.getHeight());
	button2.setPosition(posx + sizex - 25 - button2.getWidth(), posy + sizey - 25 - button2.getHeight());

	text.setPosition(posx + 25, posy - text.getGlobalBounds().height);
}

UiMessageBox::~UiMessageBox()
{
}

void UiMessageBox::setFont(sf::Font * font)
{
	button1.setFont(font);
	button2.setFont(font);
	text.setFont(*font);
}

void UiMessageBox::setTextSize(int size)
{
	button1.setTextSize(size);
	button2.setTextSize(size);
	text.setCharacterSize(size);
}

void UiMessageBox::setBorder(int bordersize)
{
	button1.setBorder(bordersize);
	button2.setBorder(bordersize);
	messagesquare.setOutlineThickness(bordersize);
}

void UiMessageBox::setBorderColor(sf::Color col)
{
	button1.setBorderColor(col);
	button2.setBorderColor(col);
	messagesquare.setOutlineColor(col);
}

void UiMessageBox::setDefaultColor(sf::Color color)
{
	button1.setDefaultColor(color);
	button2.setDefaultColor(color);
	messagesquare.setFillColor(color);
}

void UiMessageBox::update(Game & game)
{
	button1.update(game);
	button2.update(game);
}

void UiMessageBox::draw(sf::RenderTarget & window)
{
	drawShadow(messagesquare, window);
	window.draw(messagesquare);
	button1.draw(window);
	button2.draw(window);
	window.draw(text);
}
