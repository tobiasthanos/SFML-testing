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

using namespace std;
#include "MersenneTwister.h"
#include "randerson.cpp"
#include "image.cpp"
#include "glue.h"
#include "shader.h"
#include "quad.h"
#include "editor.cpp"
sf::RenderWindow window;
#include "gui.cpp"
#include "application.cpp"


Application app;


int main()
{
	window.create(sf::VideoMode(1920, 1080), "gameboard test", sf::Style::Fullscreen, sf::ContextSettings(32));
	app.run();
	
	

	return EXIT_SUCCESS;
}
