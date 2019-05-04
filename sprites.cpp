#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include "image.h"
#include "sprites.h"

Sprites::Sprites(int tW, int tH, int sW, int sH) : texWidth(tW), texHeight(tH), spriteWidth(sW), spriteHeight(sH) {};


GLuint Sprites::initSprite(const char* imagePath){
    GLuint texture = setTexture(imagePath);
    return texture;
}

void Sprites::drawSprite(GLuint texture, float posX, float posY, int frameIndex) {
        const float verts[] = {
            posX, posY,
            posX + spriteWidth, posY,
            posX + spriteWidth, posY + spriteHeight,
            posX, posY + spriteHeight
        };
        float tw = float(spriteWidth) / texWidth;
        float th = float(spriteHeight) / texHeight;
        int numPerRow = texWidth / spriteWidth;
        float tx = (frameIndex % numPerRow) * tw;
        float ty = (frameIndex / numPerRow + 1) * th;
        float texVerts[] = {
            tx, ty,
            tx + tw, ty,
            tx + tw, ty + th,
            tx, ty + th
        };

        // ... Bind the texture, enable the proper arrays

        glEnable(GL_TEXTURE_2D);
        glEnableClientState (GL_VERTEX_ARRAY);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glVertexPointer(2, GL_FLOAT, 0, verts);
        glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
        glDrawArrays( GL_LINE_LOOP, 0, 4);
        //glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);


};