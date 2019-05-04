#include <iostream>
#include <string>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

class Sprites {


public:
    Sprites(int tW, int tH, int sW, int sH);

    GLuint initSprite(const char* imagePath);
    void drawSprite(GLuint texture, float posX, float posY, int frameIndex);

private:
	int spriteWidth, spriteHeight;
    int texWidth, texHeight;
};