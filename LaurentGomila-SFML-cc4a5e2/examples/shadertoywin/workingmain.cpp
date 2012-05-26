#define PI 3.1415926535898
#define GL_GLEXT_PROTOTYPES

const double DEG2RAD = PI/180;

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdarg>
#include <vector>

#include <lua5.1/lua.hpp>

float winwidth = 1920;
float winheight = 1080;
float ttimes = 0;
float * wwidth = new float;
float * wheight = new float;

float *times=new float;

using namespace std;
#include "MersenneTwister.h"
#include "randerson.cpp"
#include "image.cpp"
#include "glue.h"
#include "shader.h"

sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Shadertoytest", sf::Style::Fullscreen, sf::ContextSettings(32));

#include "quad.h"
#include "editor.cpp"



Editor editor;
Shader shad;

sf::RectangleShape bg;

bool guivis;

// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;
	
	sfg::Window::Ptr guiwindow;
	
string vertname;
string fragname;

sfg::Entry::Ptr editfrag;
sfg::Entry::Ptr editvert;

void setfragfile(string name)
{
	fragname=name;
}

void setvertfile(string name)
{
	vertname=name;
}

void loadfiles()
{
	setfragfile(editfrag->GetText());
	setvertfile(editvert->GetText());
	shad.load(vertname,fragname);
	editor.initialize(fragname);
}

void init()
{

	guivis = false;

	vertname = "vert.vert";
	fragname = "frag.frag";

	wwidth = &winwidth;
	wheight = &winheight;
	times = &ttimes;
	
	bg.setSize(sf::Vector2f(winwidth, winheight));
	bg.setPosition(0, 0);

	window.setVerticalSyncEnabled(true);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);	// Clear The Background Color To Grey 
	gluPerspective(90.f, 1.f, 1.f, 500.f);

	editor.initialize(fragname);

	shad.load(vertname,fragname);
	shad.setparams("times", times);
	shad.setparams("resolution", wwidth, wheight);

	
	guiwindow = sfg::Window::Create();
	//guiwindow->SetTitle( "Title" );
	

	// Create a couple of buttons to populate the notebook.
	sfg::Button::Ptr button1( sfg::Button::Create("Set shader files") );
	
	editfrag = sfg::Entry::Create( "frag.frag" );
	editvert = sfg::Entry::Create( "vert.vert" );
	sfg::Box::Ptr boxed( sfg::Box::Create( sfg::Box::VERTICAL ) );
	editfrag->SetRequisition( sf::Vector2f( 200.f, 0.f ) );
	editvert->SetRequisition( sf::Vector2f( 200.f, 0.f ) );
	boxed->Pack( editfrag );
	boxed->Pack( editvert );
	boxed->Pack( button1 );
	
	button1->OnLeftClick.Connect( &loadfiles );

	// Add the notebook to the window.
	guiwindow->Add( boxed );
	guiwindow->Show(guivis);

}

void processevent(sf::Event event)
{


	// Close window : exit
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}

	if ( (event.type == sf::Event::KeyPressed) )
		{

		// Escape key : exit
		if ((event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}

		if ((event.key.code == sf::Keyboard::F1))
		{
			editor.vis();
		}
		
		if ((event.key.code == sf::Keyboard::F2))
		{
			guivis = !guivis;
			guiwindow->Show(guivis);
		}
		
		if(editor.visible)
		{
	
			if ((event.key.code == sf::Keyboard::Up))
			{
				editor.passup();
			}
	
			if ((event.key.code == sf::Keyboard::Down))
			{
				editor.passdown();
			}
	
			if ((event.key.code == sf::Keyboard::Left))
			{
				editor.passleft();
			}
	
			if ((event.key.code == sf::Keyboard::Right))
			{
				editor.passright();
			}
	
			if ((event.key.code == sf::Keyboard::Return))
			{
				editor.passenter();
			}
	
			if ((event.key.code == sf::Keyboard::Back))
			{
				editor.passback();
				shad.update();
			}
	
			if ((event.key.code == sf::Keyboard::Delete))
			{
				editor.passdelete();
				shad.update();
			}
		
			if ((event.key.control) && ( event.key.code == sf::Keyboard::D ) )
			{
				editor.passdeleteline();
				shad.update();
			}
		
			if ((event.key.control) && ( event.key.code == sf::Keyboard::W ) )
			{
				editor.setColor(sf::Color(255,255,255));
				shad.update();
			}
		
			if ((event.key.control) && ( event.key.code == sf::Keyboard::B ) )
			{
				editor.setColor(sf::Color(0,0,0));
				shad.update();
			}
		
			if ((event.key.control) && ( event.key.code == sf::Keyboard::R ) )
			{
				editor.setColor(sf::Color(255,0,0));
				shad.update();
			}
			editor.savefile(fragname);
		}
		
		
	}
	else
	{
		if( event.type == sf::Event::TextEntered )
		{
			if(editor.visible)
			{
				if ( event.text.unicode < 126 && event.text.unicode > 31 )
				{
					editor.passkey((char)event.text.unicode);
				}
				editor.savefile(fragname);
				shad.update();	
			}
				
		}
		
	}
	
	// Adjust the viewport when the window is resized
	if (event.type == sf::Event::Resized)
	{
		winwidth = event.size.width;
		winheight = event.size.height;
		glViewport(0, 0, winwidth, winheight);
	}

	

}


int curcount=0;

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{

	init();


	// Create a clock for measuring the time elapsed
	sf::Clock clock;

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle events
			guiwindow->HandleEvent( event );
			processevent(event);
		}

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
		glLoadIdentity();				// Reset The View

		// Activate the window before using OpenGL commands.
		// This is useless here because we have only one window which is
		// always the active one, but don't forget it if you use multiple windows
		window.setActive();

		// Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);

		// We get the position of the mouse cursor, so that we can move the box accordingly
		float x =  sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
		float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;
/*
			shad.setparams("resolution", 1280, 1024);
		shad.setparams("times", times);
*/

		shad.updateparams();
		
		//render the console

		//cant figure out why, sfml shader class won't reload the shader, which defeats the purpose of putting a text editor into the shader program. My shader class still works so I think I'll fill out it's features and use it instead.
		
		shad.enable();
		
		window.draw(bg);
		
		shad.disable();
		// Update the GUI every 5ms
		if( clock.getElapsedTime().asMicroseconds() >= 5000 ) 
		{
			guiwindow->Update( static_cast<float>( clock.getElapsedTime().asMicroseconds() ) / 1000000.f );
			// Update() takes the elapsed time in seconds.
			if(curcount<10)
			{
				curcount++;
			}
			else
			{
				curcount=0;
				editor.cursorvis = !editor.cursorvis;
			}
			editor.update();
			*times+=.01;
			clock.restart();
		}

		
		if(editor.visible)
		{
			for( int i = 0; i < 41; i++)		
			{
				window.draw(editor.displayedlines[i]);
			}
			if(editor.cursorvis)
			{
				window.draw(editor.cursor);
			}
		}
		
		// Draw the GUI
		sfgui.Display( window );
		
		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}
