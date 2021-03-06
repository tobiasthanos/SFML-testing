#include "application.h"
#include "luacircle.h"
Application::Application()
{


	winwidth = 1920;
	winheight = 1080;
	ttimes  = 0;
	curcount=0;
	
	luafile = "test.lua";
	
	luastate = lua_open();
	
	luaL_openlibs(luastate);
	
	Luna<Foo>::Register(luastate);
	

	circ = Luna<LuaCircle>::RegisterTable(luastate);
	circ->setPosition(luastate);
    //lua_close(luastate);

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

	editor.initialize(luafile);
	bgout.initialize();
	setuplualinks();
	
	fact.addCircle();
	fact.setRadius(50);
	fact.setColor(sf::Color::Red);
	fact.setPosition(500, 500);

}

void Application::setuplualinks()
{
	lua_register(luastate,"bgp",printback);
	lua_register(luastate,"clr",clearback);
}

void Application::loadfile()
{
	editor.initialize(luafile);
}

void Application::runscript()
{
	luaL_dofile(luastate, luafile.c_str());
}

void Application::printtoback(string pr)
{
	bgout.print(pr);
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

		window.draw(bg);
		
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
		
		if(bgout.visible)
		{
			for( int i = 0; i < BGLINES; i++ )
			{
				window.draw(bgout.displayedlines[i]);
			}
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
		
		circ->display();
		fact.display();
		
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
		if ((event.key.code == sf::Keyboard::F3))
		{
			runscript();
		}
		if ((event.key.code == sf::Keyboard::F4))
		{
			bgout.clear();
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
			}
			if ((event.key.code == sf::Keyboard::Delete))
			{
				editor.passdelete();
			}
			if ((event.key.control) && ( event.key.code == sf::Keyboard::D ) )
			{
				editor.passdeleteline();
			}
			if ((event.key.control) && ( event.key.code == sf::Keyboard::W ) )
			{
				editor.setColor(sf::Color(255,255,255));
			}
			if ((event.key.control) && ( event.key.code == sf::Keyboard::B ) )
			{
				editor.setColor(sf::Color(0,0,0));
			}
			if ((event.key.control) && ( event.key.code == sf::Keyboard::R ) )
			{
				editor.setColor(sf::Color(255,0,0));
			}
			editor.savefile(luafile);
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
				editor.savefile(luafile);
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
