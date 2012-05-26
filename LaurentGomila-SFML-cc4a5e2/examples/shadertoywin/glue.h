#ifndef GLUE
#define GLUE


/*
		char * wallfile="dig";
		FILE * pfile = fopen(wallfile,"w");
		fprintf(pfile,"%f %f %f %f ",neck.startx,neck.starty,neck.endx,neck.endy);
		fclose(pfile);*/

struct Point
{
	double x;
	double y;
};

void enterScreenSpace()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
   // glOrtho(0, winwidth, winheight, 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

/// Leave screen space

void leaveScreenSpace()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

string its(const int& number)
{
   ostringstream oss;
   oss << number;
   return oss.str();
}

void drawline(double x1, double y1, double x2, double y2,Color color)
{
	glColor3ub(color.red,color.green,color.blue);
	glBegin(GL_LINES); 
	glVertex3f((x1),(y1),0); 
	glVertex3f((x2),(y2),0); 
	glEnd();
}

void drawrect(double x1, double y1, double x2, double y2,Color color)
{
	//glColor3ub(color.red,color.green,color.blue);
	glBegin(GL_QUADS); 
	glTexCoord2f(0.0, 0.0);
	glVertex3f((x1),(y1),0);
	glTexCoord2f(1, 0.0); 
	glVertex3f((x2),(y1),0); 
	glTexCoord2f(1,1);
	glVertex3f((x2),(y2),0);
	glTexCoord2f(0.0, 1);
	glVertex3f((x1),(y2),0);
	glEnd();
}


void wpix(int x, int y)
{
glBegin(GL_QUADS); 
glColor3ub(255,255,255);
	glVertex2f(x,y+1);
    glVertex2f(x+1,y+1);
    glVertex2f(x+1,y);
    glVertex2f(x,y);
glEnd();
}

void bpix(int x, int y)
{
glBegin(GL_QUADS); 
			glColor3ub(0,0,0);
	glVertex2f(x,y+1);
    glVertex2f(x+1,y+1);
    glVertex2f(x+1,y);
    glVertex2f(x,y);
glEnd();
}

double Gsin (double angle)
{
	double angle2=angle*DEG2RAD;
	return sin(angle2);
}

double Gcos (double angle)
{
	double angle2=angle*DEG2RAD;
	return cos(angle2);
}

double Gtan (double angle)
{
	double angle2=angle*DEG2RAD;
	return tan(angle2);
}
 
void drawcircle(double x, double y,float radius,Color color)
{
	glColor3ub(color.red,color.green,color.blue);
	glBegin(GL_LINE_LOOP); 
	for (float i=0; i < 360; i++)
	{
		float deginrad = i*DEG2RAD;
		glVertex3f(x+radius*Gcos(i),y+radius*Gsin(i),0);

	}
 	glEnd();
}

void drawdiggalimb(double x, double y,float radius,double angle,int segments,Color color)
{
	glColor3ub(color.red,color.green,color.blue);
	glBegin(GL_LINE_LOOP); 

	for (float i=angle; i < angle+360; i=i+360/segments)
	{
		float x1=x+radius*Gcos(i);
		float y1=y+radius*Gsin(i);
		glVertex3f(x1,y1,0);
	}
	glEnd();
}

int isin(int value, int min, int max)
{
	if (value > min && value < max)
	{
		return 1;
	}
	return 0;	
}

double modulo(double value, int moduler)
{
	while(value >= moduler)
	{
		value -= moduler;
	}

	while(value < 0)
	{
		value += moduler;
	}
	return value;
}

/*
int sizeofarray (double array[])
{
	return sizeof(array)/sizeof(*array);
}

double sum(int inputs, ...)
{
	va_list in;
	va_start(in,inputs);
	double sum = 0;
	
	for ( int x = 0; x < inputs; x++ )        // Loop until all numbers are added
	{ 
		sum+=va_arg (in,double);
	}
 	va_end (in);   
		       
	return sum;
}



double sumarray(double array[])
{
	double sum=0;
		
	for (int i=0; i < sizeofarray(array); i++)
	{
		sum+=array[i];
	}
	return sum;
}

double average(int inputs, ...)
{
	va_list in;
	va_start(in,inputs);
	double sum = 0;
		for ( int x = 0; x < inputs; x++ )        // Loop until all numbers are added
		{ 
			sum+=va_arg (in,double);
		}
	 	va_end (in);   
		       
	return sum/inputs;
}

double averagearray(double array[])
{
	double sum=0;
		
	for (int i=0; i < sizeofarray(array); i++)
	{
		sum+=array[i];
	}
	return sum/sizeofarray(array);
}


*/

#endif
