#include "application.h"

Application::Application()
{


	winwidth = 1920;
	winheight = 1080;
	
	
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
		
		window.draw(bg);
		
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
	}
	else
	{
		if( event.type == sf::Event::TextEntered )
		{
			
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
