#include "layer.h"

	void Layer::draw()
	{
		for(vector<sf::Sprite>::iterator it = drawables.begin();it<drawables.end();it++)
		{
			window.draw(*it);
		}
	}
