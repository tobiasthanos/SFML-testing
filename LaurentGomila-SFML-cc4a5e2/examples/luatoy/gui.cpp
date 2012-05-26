#include "gui.h"

Gui::Gui()
{
	visible = false;
	
	guiwindow = sfg::Window::Create();
	guiwindow->SetTitle( "Select Lua File to Edit" );

	// Create a couple of buttons to populate the notebook.
	reload = sfg::Button::Create("Set Lua file");
	
	luafile = sfg::Entry::Create( "test.lua" );
	sfg::Box::Ptr boxed( sfg::Box::Create( sfg::Box::VERTICAL ) );
	luafile->SetRequisition( sf::Vector2f( 200.f, 0.f ) );
	boxed->Pack( luafile );
	boxed->Pack( reload );
	
	reload->OnLeftClick.Connect( &updatefile );

	// Add the notebook to the window.
	guiwindow->Add( boxed );
	guiwindow->Show(visible);
}

void Gui::vis()
{
	visible = !visible;
	guiwindow->Show(visible);
}
void Gui::processevent(sf::Event event)
{
	guiwindow->HandleEvent( event );
}

void Gui::update(sf::Clock clock)
{
	guiwindow->Update( static_cast<float>( clock.getElapsedTime().asMicroseconds() ) / 1000000.f );
}

void Gui::display()
{
	sfgui.Display( window );
}
