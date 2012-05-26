#ifndef GUI_H
#define GUI_H

class Gui
{
	public:
	Gui();

	bool visible;

	// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;
	
	sfg::Window::Ptr guiwindow;
	
	sfg::Entry::Ptr editfrag;
	sfg::Entry::Ptr editvert;
	sfg::Button::Ptr button1;
	void vis();
	void processevent(sf::Event event);
	void update(sf::Clock clock);
	void display();

};

#endif
