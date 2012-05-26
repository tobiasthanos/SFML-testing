#ifndef BGOUT_H
#define BGOUT_H

#define BGLINES 59
class Bgout
{
	public:
	
	float spacing;
	bool visible;
	sf::Font font;
	sf::Text displayedlines[BGLINES];
	
	Bgout();
	void initialize();
	void vis();
	void setColor(sf::Color col);
	void print( string temp );
	void clear();
	//void update();
	void savefile(string filetoopen);
	unsigned long getFileLength(ifstream& file);

	private:
	//not used anymore?
	float a;                    ///< alpha value used to fade in/out smoothly following visible flag
};

#endif
