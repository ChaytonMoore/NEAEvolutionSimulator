#include "Button.h"

#pragma once
class SettingWidget
{
	int accuracy;
	

public:
	float Value;
	float Change;
	Button* Decrement;
	Button* Increment;
	sf::Text VisualValue;
	float Lower;
	float Upper;

	SettingWidget(float Start, sf::Vector2i Location, float Interval, float UBound, float LBound, DataCarrier* FontData, int places, std::string Name);

	void Render(sf::RenderWindow* window);

	sf::Text WidgetName;
};

