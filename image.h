#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

GLuint setTexture(const char* imagePath);

void drawTexture(GLuint texture, int size);