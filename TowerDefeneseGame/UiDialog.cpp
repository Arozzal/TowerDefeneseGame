#include "UiDialog.hpp"



UiDialog::UiDialog(int posx, int posy, int sizex, int sizey)
{
	setSize(sizex, sizey);
	setPosition(posx, posy);
}


UiDialog::~UiDialog()
{
}

void UiDialog::makeTooltip(Entity::types type)
{
	std::string ttipp;
	auto udata = EntityData::getUnitData(type);
	auto bdata = EntityData::getBulletData(type);
	ttipp += " Name: ";
	ttipp += udata->texname;
	ttipp += '\n';
	ttipp += " Radius: ";
	ttipp += std::to_string(udata->radius);
	ttipp += '\n';
	ttipp += '\n';
	if (bdata != nullptr) {
		ttipp += " Bullet";
		ttipp += '\n';
		ttipp += " Dmg: ";
		ttipp += std::to_string(bdata->dmg);
		ttipp += '\n';
		ttipp += " Speed: ";
		ttipp += std::to_string(bdata->speed);
		ttipp += '\n';
		ttipp += '\n';
		ttipp += bdata->spezialattributs;
		ttipp += '\n';
	}
	UiElement::setText(ttipp);
}

void UiDialog::setPosition(float posx, float posy)
{
	UiElement::setPosition(posx, posy);
	text.setPosition(posx, posy);
}

void UiDialog::draw(sf::RenderTarget & window)
{
	if (isVisible()) {
		window.draw(getImage());
		window.draw(text);
	}
}

void UiDialog::update(Game & game)
{
}
