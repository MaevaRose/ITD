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

void Sprites::drawSprite(GLuint texture, float size, float posX, float posY, int frameIndex) {
        float tw = float(spriteWidth) / texWidth;
        float th = float(spriteHeight) / texHeight;
        int numPerRow = texWidth / spriteWidth;
        float tx = (frameIndex % numPerRow) * tw;
        float ty = (frameIndex / numPerRow + 1) * th;

        float sW = (-1 + 2. * float(spriteWidth) / 1800.);
        float sH = -(-1 + 2. * float(spriteHeight) / 1012.);
        //cout<<sW<<sH<<endl;
        float x1, x2, y1, y2, xm1, xm2, ym1, ym2;

        // x1 = 0.5 ;
        // x2 = 0 ;
        // y1 = 0.5 ;
        // y2 = 1 ;
        x1 = tx + tw;
        x2 = tx;
        y1 = ty;
        y2 = ty + th;
        xm1 = posX - size;
        xm2 = posX + size;
        ym1 = posY - size;
        ym2 = posY + size;

        // ... Bind the texture, enable the proper arrays

        glEnable(GL_TEXTURE_2D);
        glEnableClientState (GL_VERTEX_ARRAY);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // glVertexPointer(2, GL_FLOAT, 0, verts);
        // glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
        // glDrawArrays( GL_QUADS, 0, 4);

        glBegin(GL_QUADS);

        glTexCoord2f(x2,y2);
        glVertex2f(xm1, ym1);

        glTexCoord2f(x2,y1);
        glVertex2f(xm1, ym2);

        glTexCoord2f(x1,y1);
        glVertex2f(xm2, ym2);

        glTexCoord2f(x1,y2);
        glVertex2f(xm2, ym1);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);


};