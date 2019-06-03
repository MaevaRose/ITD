#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

class Interface{
	public :
	Interface();

	int select;

	bool clicOnInterface(int x, int y);

	void clicOnMenuBas(int x);

	void setAllTexture();

	void drawInterface();

	void drawMenuHaut();

	void drawMenuBas();

	private :
	GLuint texMenuBas;

};





