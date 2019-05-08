#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tableauTour.h"
#include "sprites.h"
#include "image.h"


using namespace std;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1800;
static const unsigned int WINDOW_HEIGHT = 1012;
static const char WINDOW_TITLE[] = "ITD - Premier Test";

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -8.4, 8.4);
}

void drawCircle(int full, float size){
    if(full != 0 && full != 1) exit(EXIT_FAILURE);
    if (full == 1){
        glBegin(GL_POLYGON);
    }
    else {
        glBegin(GL_LINE_STRIP);
    }

    glColor3ub(0, 0, 0);

    for ( float i = 0 ; i < 10 ; i=i+0.1){
        glVertex2f(cos(i)*size, sin(i)*size);
    }

    glEnd();
}

void drawSquare(int mousex, int mousey, Carte carte){
    float x = (-1 + 2. * mousex / 1800.)*15.;
    float y = -(-1 + 2. * mousey / 1012.)*8.4;

    if(carte.isConstructible(mousex, mousey, WINDOW_WIDTH)){
        glColor3ub(0, 255, 0);
    }
    else{
        glColor3ub(255, 0, 0);
    }
    
    glPushMatrix();

        glTranslatef(x, y, 0);

        glBegin(GL_QUADS);
        
        
        glVertex2f(-0.9, -0.9);
        glVertex2f(-0.9, 0.9);
        glVertex2f(0.9, 0.9);
        glVertex2f(0.9, -0.9);

    glEnd();
    glPopMatrix();
}

int main()
{   
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
    int mousex=0;
    int mousey=0;

    Carte carte;
    carte.verifITD();
    carte.setDataCarte();
    GLuint textCarte = carte.setCarte();

    //test sprite
    //Sprites testSprite(400, 400, 50, 50);
    //GLuint textTestSprite = setTexture("./logo_imac.jpg");

    // Création des tours
    PetitMonstre monstre1;
    TourBleue tourbleue;
    vector<TourBleue> tabTourBleue;


    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
  
    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        carte.afficherCarte(textCarte, 15., 8.4);
        //testSprite.drawSprite(textTestSprite, 0, 0, 1);
        drawAllTower(tabTourBleue, WINDOW_WIDTH, WINDOW_HEIGHT);
        drawSquare(mousex, mousey, carte);
        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
        
            if( e.type == SDL_KEYDOWN 
                && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                loop = 0; 
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Redimensionnement fenetre */
                //case SDL_VIDEORESIZE:
                    //reshape(&surface, e.resize.w, e.resize.h);
                    //break;

                case SDL_MOUSEMOTION:
                    mousex = e.motion.x;
                    mousey = e.motion.y;
                    break;


                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    //printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    mousex = e.button.x;
                    mousey = e.button.y;
                    printf("clic en (%d, %d)\n", mousex, mousey);
                    //bleu1.attaquer(monstre1);
                    
                    //monstre1.afficherEtat();

                    tourbleue.poser(mousex, mousey, carte, tabTourBleue);
                   // printTab(tabTourBleue);
                    //cout<<"euh"<<endl;

                    //cout << tabTourBleue[0].getPositionX() << endl;


                    //carte.returnColor(mousex, mousey, WINDOW_WIDTH);
                    carte.isConstructible(mousex, mousey, WINDOW_WIDTH);
                    // carte.isChemin(mousex, mousey, WINDOW_WIDTH);
                    // carte.isIn(mousex, mousey, WINDOW_WIDTH);
                    printf("Il y a %d tours\n", tabTourBleue.size());
                    
                    
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    //bleu1.afficherEtat();
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    
                    

                break;
                    
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;


}
