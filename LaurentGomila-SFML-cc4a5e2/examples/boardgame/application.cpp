#include "application.h"

Application::Application()
{


	winwidth = 1280;
	winheight = 1040;
	
	bg.setSize(sf::Vector2f(winwidth, winheight));
	bg.setPosition(0, 0);
	
	tex[0].loadFromFile("resources/4way.png");
	tex[1].loadFromFile("resources/corner.png");
	tex[2].loadFromFile("resources/straight.png");
	tex[3].loadFromFile("resources/3way.png");
	tiles[0].setTexture(tex[0]);
	tiles[0].setOrigin(150,150);
	tiles[1].setTexture(tex[1]);
	tiles[1].setOrigin(150,150);
	tiles[2].setTexture(tex[2]);
	tiles[2].setOrigin(150,150);
	tiles[3].setTexture(tex[3]);
	tiles[3].setOrigin(150,150);
	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			int which = r.between(0,3); 
			int rott = r.between(0,3);
			tiles[which].setPosition(300*i,300*j);
			tiles[which].setRotation(90*rott);
			layer.drawables.push_back(tiles[which]);
		}
	}
	dpos.x=0;
	dpos.y=0;
	
	zoom=1.0;

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

		if(moving)
		{
			
			view.move(dpos.x*zoom,dpos.y*zoom);
			dpos.x=0;
			dpos.y=0;
		}
		window.setView(window.getDefaultView());
		window.draw(bg);
		window.setView(view);
		//window.draw(sp);
		layer.draw();
		
		//window.draw(cam);
		
		// Update the GUI every 5ms
		if( clock.getElapsedTime().asMicroseconds() >= 5000 ) 
		{
			gui.update(clock);
			// Update() takes the elapsed time in seconds.
			clock.restart();
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
		
		}
		if ((event.key.code == sf::Keyboard::F2))
		{
			gui.vis();
		}
		if ((event.key.code == sf::Keyboard::Up))
		{
		}
		if ((event.key.code == sf::Keyboard::Down))
		{
		}
		if ((event.key.code == sf::Keyboard::Left))
		{
		}
		if ((event.key.code == sf::Keyboard::Right))
		{
		}
	}
	if( event.type == sf::Event::TextEntered )
	{
		
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		if(moving)
		{
			newpos.x = event.mouseMove.x;
			newpos.y = event.mouseMove.y;
			dpos=pos-newpos;
			pos=newpos;
		}
		
	}
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			if(!moving)
			{
				pos.x = event.mouseButton.x;
				pos.y = event.mouseButton.y;
			}
			moving = true;
		}
	}
	
	if( event.type == sf::Event::MouseButtonReleased )
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			dpos.x=0;
			dpos.y=0;
			moving = false;
		}
	}
	
	if( event.type == sf::Event::MouseWheelMoved)
	{
		if( event.mouseWheel.delta > 0 )
		{
				zoom=zoom/2;
			view.zoom(.5);
		}
		else
		{
			zoom=zoom*2;
			view.zoom(2);
		}
	
		//view.zoom(event.mouseWheel.delta);
		
	}
	
	// Adjust the viewport when the window is resized
	if (event.type == sf::Event::Resized)
	{
		winwidth = event.size.width;
		winheight = event.size.height;
		glViewport(0, 0, winwidth, winheight);
	}
}
