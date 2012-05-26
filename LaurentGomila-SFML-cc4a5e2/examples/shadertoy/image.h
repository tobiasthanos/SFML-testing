#ifndef image_h
#define image_h

struct Color 
{
	int red;
	int green;
	int blue;
};

/* Image type - contains height, width, and data */
struct Image 
{
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

int ImageLoad(char *filename, Image *image);

#endif
