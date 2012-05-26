INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib -L/usr/local/lib/SFML -L/usr/lib



COMPILERFLAGS = -Wall -g -DGL_GLEXT_PROTOTYPES
CC = i586-mingw32msvc-g++
LD = i586-mingw32msvc-ld
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LFLAGS = $(COMPILERFLAGS) 
LIBRARIES = -lopenal -lsndfile -lXrandr -lpthread -lrt -lfreetype -lGLEW -ljpeg -lGL -lGLU -lSM -lICE -lX11 -lXext -lsfgui -lsfml-graphics -lsfml-window -lsfml-system

all: $(basename main.cpp)

main : main.o 
	$(CC) $(CFLAGS) -c -o $@ $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm main
	rm main.o

