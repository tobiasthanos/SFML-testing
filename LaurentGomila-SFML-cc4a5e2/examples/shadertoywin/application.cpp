#include "application.h"

Application::Application()
{


	winwidth = 1920;
	winheight = 1080;
	ttimes  = 0;
	
	curcount=0;

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


}

void Application::loadfiles()
{
	shad.load(vertname,fragname);
	editor.initialize(fragname);
}

void Application::run()
{
	// Start game loop
	while (window.isOpen())
	{
		// Process events
		
		while (window.pollEvent(event))
		{
			// Handle events
			gui.processevent(event);
			processevent();
		}

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
		glLoadIdentity();				// Reset The View

		// Activate the window before using OpenGL commands.
		// This is useless here because we have only one window which is
		// always the active one, but don't forget it if you use multiple windows
		window.setActive();

		// Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);

		//shad.setparams("resolution", wwidth, wheight);    //these are initialized in the constructor
		//shad.setparams("times", times);
		shad.updateparams();

		//cant figure out why, sfml shader class won't reload the shader, which defeats the purpose of putting a text editor into the shader program. My shader class still works so I think I'll fill out it's features and use it instead.
		
		shad.enable();
		
		window.draw(bg);
		
		shad.disable();
		// Update the GUI every 5ms
		if( clock.getElapsedTime().asMicroseconds() >= 5000 ) 
		{
			gui.update(clock);
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
		gui.display();
		
		// Finally, display the rendered frame on screen
		window.display();
		
	}

}

void Application::processevent()
{
	// Close window : exit
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
	if ( (event.type == sf::Event::KeyPressed) )
	{
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
			gui.vis();
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
