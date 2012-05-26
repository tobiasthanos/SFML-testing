#include "gui.h"

Gui::Gui()
{
	visible = false;
	
	guiwindow = sfg::Window::Create();
	//guiwindow->SetTitle( "Title" );
	

	// Create a couple of buttons to populate the notebook.
	button1 = sfg::Button::Create("Set shader files");
	
	editfrag = sfg::Entry::Create( "frag.frag" );
	editvert = sfg::Entry::Create( "vert.vert" );
	sfg::Box::Ptr boxed( sfg::Box::Create( sfg::Box::VERTICAL ) );
	editfrag->SetRequisition( sf::Vector2f( 200.f, 0.f ) );
	editvert->SetRequisition( sf::Vector2f( 200.f, 0.f ) );
	boxed->Pack( editfrag );
	boxed->Pack( editvert );
	boxed->Pack( button1 );
	
	button1->OnLeftClick.Connect( &updatefiles );

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
