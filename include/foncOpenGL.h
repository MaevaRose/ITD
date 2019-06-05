#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>




void drawSquare(int pos_x, int pos_y, float large, float height, int full, int r, int g, int b);

void drawCircle(float sizeCircle, int full);

class Sprites {


public:
	Sprites();
    Sprites(int tW, int tH, int sW, int sH);

    GLuint initSprite(const char* imagePath);
    void drawSprite(GLuint texture, float size, float posX, float posY, int frameIndex);

private:
	int spriteWidth; 
	int spriteHeight;
    int texWidth;
    int texHeight;
};

GLuint setTexture(const char* imagePath);

GLuint setPNGTexture(const char* imagePath);

void drawTexture(GLuint texture, int pos_x, int pos_y, int width, int height);

void drawRedTower(float x, float y, int frameIndex);

void writeString(int x, int y,  char* s);