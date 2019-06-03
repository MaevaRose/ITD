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

#include "../include/tour.h"
#include "../include/interface.hpp"
//#include "../include/grapheNoeuds.h"


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
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER );
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

void drawCircle(float size, float x, float y){
    
    glBegin(GL_LINE_STRIP);

    glColor3ub(0, 0, 0);

    for ( float i = 0 ; i < 10 ; i=i+0.1){
        glVertex2f(cos(i)*size, sin(i)*size);
    }

    glEnd();
}

void drawTourShape(int mousex, int mousey, Carte &carte){
    float x = (-1 + 2. * mousex / 1800.)*15.;
    float y = -(-1 + 2. * mousey / 1012.)*8.4;

    bool isConstructible = carte.isConstructible(mousex, mousey, WINDOW_WIDTH, WINDOW_HEIGHT);
    if(isConstructible){
        glColor3ub(0, 255, 0);
    }
    else{
        glColor3ub(255, 0, 0);
    }

    //glColor3ub(0, 0, 0);
    
    glPushMatrix();

        glTranslatef(x, y, 0);

        glBegin(GL_LINE_LOOP);
        
        
        glVertex2f(-0.9, -0.9);
        glVertex2f(-0.9, 0.9);
        glVertex2f(0.9, 0.9);
        glVertex2f(0.9, -0.9);

    glEnd();
    glPopMatrix();
}


int main(int argc, char* argv[])
{   

    glutInit (&argc, argv);
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

    Interface interface;
    interface.setAllTexture();
    interface.select=0;
    bool clicOnInterface=false;

    //temps
    bool play = true;
    //cout<<"horloge"<<CLOCKS_PER_SEC<<endl;
    //double frame=1;

    int mousex=500;
    int mousey=500;
    int tourColor = 0;

    Carte carte;
    carte.setDataCarte();
    carte.verifITD();
    GLuint textCarte = carte.setCarte();

    //test sprite
    Sprites testSprite(300, 300, 100, 100);
    GLuint textTestSprite = setPNGTexture("./images/tourRouge.png");

    // Création des tours
    int finPartie = 0;

    TourBleue tourbleue;
    vector<TourBleue> tabTourBleue;
    
    TourRouge tourrouge;
    vector<TourRouge> tabTourRouge;
    
    TourJaune tourjaune;
    vector<TourJaune> tabTourJaune;

    TourVerte tourverte;
    vector<TourVerte> tabTourVerte;

    //Création des monstres
    PetitMonstre monstre1;
    MoyenMonstre monstre2;
    GrosMonstre monstre3;

    vector<PetitMonstre> tabPetitMonstre;
    vector<MoyenMonstre> tabMoyenMonstre;
    vector<GrosMonstre> tabGrosMonstre;

    monstre1.apparaitre(1625,725, tabPetitMonstre);
    monstre2.apparaitre(1625,725, tabMoyenMonstre);
    monstre3.apparaitre(1625, 725, tabGrosMonstre);


    int frameIndex = 0;

    //TEST DIJKSTRA

    vector<Noeud> noeuds = carte.noeuds;
    vector<vector<int>> grapheNoeuds;
    vector<vector<int>> tabPoids;
    vector<vector<int>> posNoeuds;
    constructGraphes (noeuds, grapheNoeuds, tabPoids, posNoeuds);

    //printf("JE SUIS LA\n");
    //vector<vector<int>> grapheNoeuds = creerGrapheTest2();
    printf("il y a %d noeuds et le premier noeud est %d\n", grapheNoeuds.size(), grapheNoeuds[0][0]);
    //vector<vector<int>> tabPoids = creerTabTest2();
    printf("il y a %d poids et le deuxieme poids est %d\n", tabPoids.size(), tabPoids[0][0]);
    int start = 0;
    int end = 13;
    vector<int> chemin = calculCheminMonstre(grapheNoeuds, tabPoids, start, end);
    afficheChemin(chemin);
    //vector<vector<int>> posNoeuds = creerPosNoeud();


    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);
  
    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        //Uint32 startTime = SDL_GetTicks();

        
        Uint32 startTime;
        Uint32 time;

        if(play){
            startTime = SDL_GetTicks();
            time = SDL_GetTicks()/1000;
            frameIndex=SDL_GetTicks()/300;
            attaqueAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        //printf("j'ai attaqué sans pb\n");
            tuerAllMonstre(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        //printf("apres premier if play\n");
        }

        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        

        carte.afficherCarte(textCarte, 15., 8.4);
        testSprite.drawSprite(textTestSprite, 0.9, -5, 5, frameIndex);

        drawAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex);
        attaqueAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        drawTourShape(mousex, mousey, carte);
        glColor3ub(0,0,0);
        writeString(0, 0,  "Je test loul");
        glColor3ub(255,255,255);
        interface.drawInterface();

        if(play){
            updateAllMonstre(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre, chemin, posNoeuds, finPartie);
        
        }
        drawAllMonstres(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);

        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        glDisable(GL_BLEND);
        
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
                    clicOnInterface = interface.clicOnInterface(mousex, mousey);
                    if(!clicOnInterface){
                        if(play){
                            if(interface.select==1){
                                tourbleue.poser(mousex, mousey, carte, tabTourBleue);
                                interface.select = 0;
                            }
                            if(interface.select==2){
                                tourverte.poser(mousex, mousey, carte, tabTourVerte);
                                interface.select = 0;
                            }
                            if(interface.select==3){
                                tourjaune.poser(mousex, mousey, carte, tabTourJaune);
                                interface.select = 0;
                            }
                            if(interface.select==4){
                                tourrouge.poser(mousex, mousey, carte, tabTourRouge);
                                interface.select = 0;
                            }
                        }
                    }
                    else{
                        clicOnInterface = false;
                    }
                    
                    carte.isConstructible(mousex, mousey, WINDOW_WIDTH, WINDOW_HEIGHT);
                    
                    
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    //bleu1.afficherEtat();
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if(e.key.keysym.sym == SDLK_b){
                        tourColor = 1;
                    }
                    if(e.key.keysym.sym == SDLK_v){
                        tourColor = 2;
                    }
                    if(e.key.keysym.sym == SDLK_j){
                        tourColor = 3;
                    }
                    if(e.key.keysym.sym == SDLK_r){
                        tourColor = 4;
                    }
                    if(e.key.keysym.sym == SDLK_p){
                        if(play){
                            play = false;
                        }
                        else{
                            play = true;
                        }
                    }
                    
                    

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