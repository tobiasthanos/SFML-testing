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
	
	sfg::Entry::Ptr luafile;
	sfg::Button::Ptr reload;
	void vis();
	void processevent(sf::Event event);
	void update(sf::Clock clock);
	void display();

};

#endif
