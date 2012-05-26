#ifndef GUI_H
#define GUI_H

class Gui
{
	public:
	Gui();

	bool visible;

	// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;
	
	sfg::Image::Ptr images;
	
	sfg::Window::Ptr guiwindow;
	
	sfg::Button::Ptr button1;
	void vis();
	void processevent(sf::Event event);
	void update(sf::Clock clock);
	void init();
	void display();

};

#endif
