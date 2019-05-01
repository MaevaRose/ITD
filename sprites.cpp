#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include "image.h"

GLuint setTexture("./mars.jpg");

void SpriteSheet::drawSprite(float posX, float posY, int frameIndex) {
        const float verts[] = {
            posX, posY,
            posX + spriteWidth, posY,
            posX + spriteWidth, posY + spriteHeight,
            posX, posY + spriteHeight
        };
        const float tw = float(spriteWidth) / texWidth;
        const float th = float(spriteHeight) / texHeight;
        const int numPerRow = texWidth / spriteWidth;
        const float tx = (frameIndex % numPerRow) * tw;
        const float ty = (frameIndex / numPerRow + 1) * th;
        const float texVerts[] = {
            tx, ty,
            tx + tw, ty,
            tx + tw, ty + th,
            tx, ty + th
        };

        // ... Bind the texture, enable the proper arrays

        glVertexPointer(2, GL_FLOAT, verts);
        glTexCoordPointer(2, GL_FLOAT, texVerts);
        glDrawArrays(GL_TRI_STRIP, 0, 4);

};