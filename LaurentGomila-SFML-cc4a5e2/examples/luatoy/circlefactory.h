#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
	public:
	
	sf::CircleShape circle;
	
	
	void addCircle();
	void setRadius(int radius);
	void setColor(sf::Color color);
	void setPosition(float x, float y);
	void display();
	
};


#endif
