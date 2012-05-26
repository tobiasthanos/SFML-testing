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
#include "luna.h"
using namespace std;
#include "MersenneTwister.h"
#include "randerson.cpp"
#include "image.cpp"
#include "glue.h"
#include "quad.h"
#include "editor.cpp"
#include "bgout.cpp"

void updatefile();
int printback(lua_State *luas);
int clearback(lua_State * luas);
sf::RenderWindow window;

#include "foo.h"
#include "gui.cpp"
#include "circlefactory.cpp"
#include "application.cpp"

Application app;

#include "luacircle.cpp"


#include "globalluabindings.h"


int main()
{
	
	window.create(sf::VideoMode(1920, 1080), "Luatoytest", sf::Style::Fullscreen, sf::ContextSettings(32));
	app.run();
	

	return EXIT_SUCCESS;
}
