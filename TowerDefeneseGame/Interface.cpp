#include "Interface.hpp"



Interface::Interface()
{
	uimap[ui];
	uimap[uie];
	uimap[mainmenu];
	uimap[messagebox];
	uimap[levelselectscreen];

	gamefont.loadFromFile("resources/Minecraft.ttf");
}

sf::Text * Interface::addLabelToScreen(std::string text, sf::Vector2f pos)
{
	sf::Text* textlab = new sf::Text;
	textlab->setFont(gamefont);
	textlab->setFillColor({ 255,255,255,255 });
	textlab->setPosition(pos);
	textlab->setString(text);
	textvec.push_back(textlab);
	return textlab;
}

UiElement * Interface::useDefaultDesing(UiElement * ele)
{
	ele->setDefaultColor(sf::Color(10, 95, 75, 255));
	ele->setBorder(2);
	ele->setBorderColor({ 180,180,180,255 });
	ele->setFont(&gamefont);
	ele->setTextSize(60);

	auto but = dynamic_cast<UiButton*>(ele);

	if (but != nullptr) {
		but->setSubTextFont(gamefont);
		but->setSubTextSize(20);
	}

	auto dia = dynamic_cast<UiDialog*>(ele);

	if (dia != nullptr) {
		dia->setTextSize(15);
		dia->setBorder(1);
		dia->setDefaultColor(sf::Color(0,0,0,0));
	}

	return ele;
}

void Interface::update(Game & game)
{
	auto scr = &uimap.at(currentscreen);


	for (auto it = scr->begin(); it != scr->end(); ++it) {
		(*it)->update(game);
	}

	if (currentscreen != ui)
		game.window->pollEvent(*game.event);
	
}

void Interface::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto scr = &uimap.at(currentscreen);
	
	for (auto it = scr->begin(); it != scr->end(); ++it) {
		(*it)->draw(target);
	}

	if(currentscreen == ui)
	for (auto it : textvec) {
		target.draw(*it);
	}
}


Interface::~Interface()
{
}
