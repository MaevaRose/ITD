#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include "../include/interface.hpp"
#include "../include/foncOpenGL.h"


void drawInterface() {
	drawMenuHaut();
	drawMenuTour();
}


void drawMenuHaut() {
	drawSquare(1700, 150, 3., 5., 1, 0, 0, 255);
	//printf("echo loul\n");
}


void drawMenuTour() {
	drawSquare(900, 950, 10., 2., 1, 0, 0, 255);
}

