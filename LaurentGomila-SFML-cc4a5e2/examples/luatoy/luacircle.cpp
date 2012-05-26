#include "luacircle.h"

	LuaCircle::LuaCircle(lua_State *L) 
	{
		app.bgout.print("in circle constructor");
	}

	int LuaCircle::addCircle(lua_State *L) 
	{
		circle=sf::CircleShape();
		circle.setFillColor(sf::Color::Red);
		app.bgout.print("New Circle Created");
	}
	
	int LuaCircle::setRadius(lua_State *L)
	{
		circle.setRadius(lua_tonumber(L, 1));
	}
	/*void LuaCircle::setColor(sf::Color color)
	{
		circle.setFillColor(color);
	}*/
	int LuaCircle::setPosition(lua_State *L)
	{
		circle.setPosition(lua_tonumber(L, 1),lua_tonumber(L, 2));
	}
	
	int LuaCircle::display()
	{

		window.draw(circle);
	}

	LuaCircle::~LuaCircle() 
	{
		app.bgout.print("in circle destructor");
	}
