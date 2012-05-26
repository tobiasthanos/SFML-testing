#ifndef FONT
#define FONT
//#include <string.h>

using namespace std;

GLuint	base;											// Base Display List For The Font

void BuildFont()										// Build Our Font Display List
{
	float cx;											// Holds Our X Character Coord
	float cy;											// Holds Our Y Character Coord

	base=glGenLists(256);								// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Font Texture
	for (int loop=0; loop<256; loop++)					// Loop Through All 256 Lists
	{
		cx=float(loop%16)/16.0f;						// X Position Of Current Character
		cy=float(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(base+loop,GL_COMPILE);				// Start Building A List
		glBegin(GL_QUADS);								// Use A Quad For Each Character
			glTexCoord2f(cx,1-cy-0.0625f);				// Texture Coord (Bottom Left)
			glVertex2i(0,0);							// Vertex Coord (Bottom Left)
			glTexCoord2f(cx+0.0625f,1-cy-0.0625f);		// Texture Coord (Bottom Right)
			glVertex2i(16,0);							// Vertex Coord (Bottom Right)
			glTexCoord2f(cx+0.0625f,1-cy);				// Texture Coord (Top Right)
			glVertex2i(16,16);							// Vertex Coord (Top Right)
			glTexCoord2f(cx,1-cy);						// Texture Coord (Top Left)
			glVertex2i(0,16);							// Vertex Coord (Top Left)
		glEnd();										// Done Building Our Quad (Character)
		glTranslated(10,0,0);							// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}													// Loop Until All 256 Are Built
}

void KillFont()											// Delete The Font From Memory
{
	glDeleteLists(base,256);							// Delete All 256 Display Lists
}

void glPrint(GLint x, GLint y, string sstring)			// Where The Printing Happens
{

	int	set=0;
	
	glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR);
	glBlendFunc(GL_DST_COLOR,GL_ZERO);
	//glColor4f(1,1,1,1);

	const char* text=sstring.c_str();					// Results Are Stored In Text
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winwidth,0,winheight,-1,1);						// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)
	glScalef(1.2,1.2,1.2);
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base-32+(128*set));						// Choose The Font Set (0 or 1)
	glCallLists(strlen(text),GL_BYTE,text);				// Write The Text To The Screen
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
#endif
