void updatefile()
{
	app.luafile=app.gui.luafile->GetText();
	app.loadfile();
}

int printback(lua_State * luas)
{
	string pr = lua_tostring(luas, 1);
	app.printtoback(pr);
	return 0;
}

int clearback(lua_State * luas)
{
	app.bgout.clear();
	return 0;
}
