#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include "../include/foncOpenGL.h"


using namespace std;

void drawSquare(int pos_x, int pos_y, float width, float height, int full, int r, int g, int b) {
    float x = (-1 + 2. * pos_x / 1800.)*15.;
    float y = -(-1 + 2. * pos_y / 1012.)*8.4;

    float width2 = (-1 + 2. * width / 1800.)*15.;
    float height2 = -(-1 + 2. * height / 1012.)*8.4;

    glPushMatrix();
    glTranslatef(x, y, 0);
    if (full) {
        glBegin(GL_QUADS);
    }
    else {
        glBegin(GL_LINE_LOOP);
    }

    glColor3ub(r, g, b);

        //Points du carré
        glVertex2f(-width/2.,height/2.);
        glVertex2f(width/2.,height/2.);
        glVertex2f(width/2.,-height/2.);
        glVertex2f(-width/2.,-height/2.);

    glEnd();
    glPopMatrix();
}


void drawCircle(float sizeCircle, int full) {
    if (full) {
        glBegin(GL_POLYGON);
    }
    else {
        glBegin(GL_LINE_STRIP);
    }

        for (float i=0; i<50; i+=0.1) {
            glVertex2f(sizeCircle*cos(i), sizeCircle*sin(i));
        }
    glEnd();

}


Sprites::Sprites(int tW, int tH, int sW, int sH) : texWidth(tW), texHeight(tH), spriteWidth(sW), spriteHeight(sH) {};


GLuint Sprites::initSprite(const char* imagePath){
    GLuint texture = setTexture(imagePath);
    return texture;
}


void Sprites::drawSprite(GLuint texture, float size, float posX, float posY, int frameIndex) {
        //printf("Je suis dans drawSprite\n");
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


GLuint setTexture(const char* imagePath) {

    SDL_Surface *image = NULL;
    image = IMG_Load(imagePath);
    if(!image){
        printf("Image non chargée");
        exit(EXIT_FAILURE);
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(image);
    return texture;
}


GLuint setPNGTexture(const char* imagePath) {
    SDL_Surface *image = NULL;
    image = IMG_Load(imagePath);
    if(!image){
        printf("Image non chargée");
        exit(EXIT_FAILURE);
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(image);

    return texture;
}


void drawTexture(GLuint texture, int pos_x, int pos_y, int width_px, int height_px){
    
    float x = (-1 + 2. * pos_x / 1800.)*15.;
    float y = -(-1 + 2. * pos_y / 1012.)*8.4;

    float width = (-1 + 2. * width_px / 1800.)*15.;
    float height = (-1 + 2. * height_px / 1800.)*15.;

    glPushMatrix();

        glTranslatef(x, y, 0);

        glColor3ub(255, 255, 255);
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex2f(height/2, width/2);

        glTexCoord2f(1,1);
        glVertex2f(-height/2, width/2);

        glTexCoord2f(1,0);
        glVertex2f(-height/2, -width/2);

        glTexCoord2f(0,0);
        glVertex2f(height/2, -width/2);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}


void writeString(int x, int y,  char* s) {

        char* c;
        
        // Positionne le premier caractère de la chaîne
        glRasterPos2f(x, y);
        for (c = s; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Affiche chaque caractère de la chaîne

        // Réinitialise la position du premier caractère de la chaîne
        glRasterPos2f(0, 0);
}