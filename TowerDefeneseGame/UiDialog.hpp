#pragma once
#include "UiElement.hpp"
#include "EntityData.hpp"

class UiDialog : public UiElement
{
	bool visible = false;
public:
	UiDialog(int posx, int posy, int sizex, int sizey);
	~UiDialog();

	void makeTooltip(Entity::types);
	void setVisible(bool visible) { this->visible = visible; }
	bool isVisible() { return visible; }
	virtual void setPosition(float posx, float posy) override;
	virtual void draw(sf::RenderTarget& window) override;
	virtual void update(Game& game) override;
};

