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
	//Camera cam;
	Layer layer;
	sf::Vector2i pos;
	sf::Vector2i newpos;
	sf::Vector2i dpos;
	bool moving;
	sf::Clock clock;
	sf::RectangleShape bg;
	sf::Sprite tiles[4];
	sf::Event event;
	sf::View view;
	sf::Texture tex[4];
	sf::Mouse mouse;
	Randerson r;
	float zoom;
	void processevent();
	void loadfiles();
	void run();
};

#endif
