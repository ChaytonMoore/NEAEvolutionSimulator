#include "SettingWidget.h"
 

int FunctionIncrement(SettingWidget* Widget)
{
	Widget->Value++;
	return 1;
}

int FunctionDecrement(SettingWidget* Widget)
{
	Widget->Value--;
	return 1;
}


SettingWidget::SettingWidget(float Start, sf::Vector2i Location, float Interval, float UBound, float LBound, DataCarrier* FontData,int places,std::string Name)
{
	Value = Start;
	Change = Interval;



	Decrement = new Button("",FontData,sf::Vector2f(Location) ,sf::Vector2f(25,15));
	

	Increment = new Button("", FontData, sf::Vector2f(Location)+ sf::Vector2f(40,0), sf::Vector2f(15, 15));

	FontData->StandardFont = GetDefaultFont(FontData);
	VisualValue.setFont(FontData->StandardFont); //Need to get the DataCarrier that contains the default font

	// set the string to display
	VisualValue.setString(std::to_string(Value).std::string::substr(0,places));
	accuracy = places;

	// set the character size
	VisualValue.setCharacterSize(12);

	VisualValue.setFillColor(sf::Color::Green);

	VisualValue.setPosition(sf::Vector2f(Location) + sf::Vector2f(10, 0) + sf::Vector2f((3-places)*5, 0));

	Upper = UBound;
	Lower = LBound;


	WidgetName.setString(Name);
	WidgetName.setFont(FontData->StandardFont);
	WidgetName.setCharacterSize(14);
	WidgetName.setFillColor(sf::Color::Red);
	WidgetName.setPosition(sf::Vector2f(Location) + sf::Vector2f(0, -20));



}

void SettingWidget::Render(sf::RenderWindow* window)
{
	window->draw(Decrement->shape);
	window->draw(Increment->shape);
	window->draw(VisualValue);
	window->draw(WidgetName);
	Decrement->ButtonTick(window);
	Increment->ButtonTick(window);
	VisualValue.setString(std::to_string(Value).std::string::substr(0, accuracy));

}
