/*******************************************************************************/
/*********************************21/09/200*************************************/
/**********************Programmer: Dimitrios Christopoulos**********************/
/**********************for the oglchallenge contest*****************************/
/**********************COLLISION CRAZY******************************************/
/*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
/*
 * getint and getshort arehelp functions to load the bitmap byte by byte on 
 * SPARC platform.
 * I've got them from xv bitmap load routinebecause the original bmp loader didn't work
 * I've tried to change as less code as possible.
 */

GLuint texture[2];
Image *TextureImage[2]; 

static unsigned int getint(FILE *fp)
{
  int c, c1, c2, c3;

  /* get 4 bytes*/
  c = getc(fp);  
  c1 = getc(fp);  
  c2 = getc(fp);  
  c3 = getc(fp);
  
  return ((unsigned int) c) +   
    (((unsigned int) c1) << 8) + 
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

static unsigned int getshort(FILE *fp)
{
  int c, c1;
  
  /*get 2 bytes*/
  c = getc(fp);  
  c1 = getc(fp);
 
  return ((unsigned int) c) + (((unsigned int) c1) << 8);
 
}
    

void randomizer(int iwidth, int iheight, Image *image)
{
	image->sizeX=iwidth;
	image->sizeY=iheight;
	int size = iwidth*iheight*4;
	image->data = (char *) malloc(size);
	Randerson ran;

	for(int i = 0; i < size; i++)
	{
		image->data[i] = ran.between(0,255);
	}
	
}

/* quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */
/* See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.*/

	int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 /* size of the image in bytes.*/
    unsigned long i;                    /* standard counter.*/
    unsigned short int planes;          /* number of planes in image (must be 1) */
    unsigned short int bpp;             /* number of bits per pixel (must be 24)*/
    char temp;                          /* temporary color storage for bgr-rgb conversion.*/

    /* make sure the file is there.*/
    if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return 0;
    }
    
    /* seek through the bmp header, up to the width/height:*/
    fseek(file, 18, SEEK_CUR);

    /* read the width*/
    image->sizeX = getint (file);
    
    /* read the height */
    image->sizeY = getint (file);
    
    /* calculate the size (assuming 24 bits or 3 bytes per pixel).*/
    size = image->sizeX * image->sizeY * 3;

    /* read the planes*/
    planes = getshort(file);
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    /* read the bpp*/
    bpp = getshort(file);
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    /* seek past the rest of the bitmap header.*/
    fseek(file, 24, SEEK_CUR);

    /* read the data. */
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { /* reverse all of the colors. (bgr -> rgb)*/
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    /* we're done.*/
    return 1;
}

	// Load Bitmaps And Convert To Textures
	int LoadGLTextures() {	
    int Status=false;                               				// Status Indicator
                     						// Create Storage Space For The Textures
        TextureImage[0] = (Image *) malloc(sizeof(Image));			// Set The Pointer To NULL
        TextureImage[1] = (Image *) malloc(sizeof(Image));			// Set The Pointer To NULL

        if (ImageLoad("Font.bmp",TextureImage[0]))
        {
			Status=true;                           		// Set The Status To TRUE
			glGenTextures(1, &texture[0]);         		// Create Two Texture

			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        }

		randomizer(1920,1080,TextureImage[1]);
		glGenTextures(1, &texture[1]);         		// Create Two Texture
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
	

        if (TextureImage[0])							// If Texture Exists
	    {
			if (TextureImage[0]->data)				// If Texture Image Exists
			{
				free(TextureImage[0]->data);	// Free The Texture Image Memory
			}
			free(TextureImage[0]);					// Free The Image Structure
		}
        return Status;                                 		// Return The Status
};



