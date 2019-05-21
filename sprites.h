#include <iostream>
#include <string>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

class Sprites {


public:
    Sprites(int tW, int tH, int sW, int sH);

    GLuint initSprite(const char* imagePath);
    void drawSprite(GLuint texture, float size, float posX, float posY, int frameIndex);

private:
	int spriteWidth; 
	int spriteHeight;
    int texWidth;
    int texHeight;
};