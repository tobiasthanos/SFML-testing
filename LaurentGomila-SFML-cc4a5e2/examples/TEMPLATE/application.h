#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
	public:
	Application();
//pointers here are because of the way I have shader code setup, it takes pointers to the data that you want it to send to the shader every frame.
	float winwidth;
	float winheight;
	Gui gui;
	sf::Clock clock;
	sf::RectangleShape bg;
	sf::Event event;
	void processevent();
	void loadfiles();
	void run();
};

#endif
