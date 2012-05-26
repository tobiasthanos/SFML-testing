#ifndef EDITOR_H
#define EDITOR_H

class Editor
{
	public:

	int linenumber;
	int positioninline;
	int totallines;
	int sourceoffset;

	float spacing;
	bool visible;
	sf::RectangleShape cursor;
	bool cursorvis;
	sf::Font font;
	int fontstyle;
	vector<string> sourcefile;
	sf::Text displayedlines[41];
	
	string filename;

	Editor();
	void initialize(string name);
	void vis();
	void setColor(sf::Color col);
	void passkey(char key);
	void passback();
	void passenter();
	void passdelete();
	void passdeleteline();
	void passleft();
	void passright();
	void passup();
	void passdown();
	void update();
	void loadfile(string filetoopen);
	void savefile(string filetoopen);
	unsigned long getFileLength(ifstream& file);

	private:

	float a;                    ///< alpha value used to fade in/out smoothly following visible flag
};

#endif
