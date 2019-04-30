#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "image.h"

using namespace std;

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(image);
    return texture;

}

void drawTexture(GLuint texture, int size){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex2f(-size, -size);

        glTexCoord2f(1,1);
        glVertex2f(size, -size);

        glTexCoord2f(1,0);
        glVertex2f(size, size);

        glTexCoord2f(0,0);
        glVertex2f(-size, size);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

}

