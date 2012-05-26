/// Text element.
/// Manages rendering text on the screen with alpha blend in/out

struct Text
{
    string text;
    float x,y;
    float r,g,b;
    bool visible;

    /// default constructor

    Text()
    {
        x = 0.0f;
        y = 0.0f;

        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
        
        visible = true;
    }
    

    /// update text

    void update()
    {
	
    }

    /// render text

    void render()
    {

        if (visible == true)
        {
			// render text normally
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_COLOR,GL_ONE);
			glColor3f(r,g,b);
			glPrint(x, y,text);
			glDisable(GL_BLEND);
        }
    }



};
