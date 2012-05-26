#include "circlefactory.h"

	void Circle::addCircle()
	{
		circle = sf::CircleShape();
	}
	void Circle::setRadius(int radius)
	{
		circle.setRadius(radius);
	}
	void Circle::setColor(sf::Color color)
	{
		circle.setFillColor(color);
	}
	void Circle::setPosition(float x, float y)
	{
		circle.setPosition(x,y);
	}
	
	void Circle::display()
	{

		window.draw(circle);
	}
