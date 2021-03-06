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

//#include "../include/tour.h"
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


    //quelques variables 
    int mousex=500;
    int mousey=500;

    int temp_tour_select = -1;
    int indice = 0;
    int nbLoop=0;
    int endGame = 0;
    int arrive =0;
    int frameIndex = 0;
    int start = 0;
    int end = 13;




    //initialisation de la carte
    Carte carte;
    
    carte.verifITD(argv[1]);

    GLuint textCarte = carte.setCarte();
    carte.argent = 100;


    // Création des tours
    TourBleue tourbleue;
    TourBleue select_blue;
    vector<TourBleue> tabTourBleue;
    
    TourRouge tourrouge;
    TourRouge select_rouge;
    vector<TourRouge> tabTourRouge;
    
    TourJaune tourjaune;
    TourJaune select_jaune;
    vector<TourJaune> tabTourJaune;

    TourVerte tourverte;
    TourVerte select_verte;
    vector<TourVerte> tabTourVerte;

    Radar radar;
    Radar select_radar;
    vector<Radar> tabRadar;

    UsineArmement uarmement;
    UsineArmement select_uarmement;
    vector<UsineArmement> tabUsineArmement;

    StockMunition stomuni;
    StockMunition select_stomuni;
    vector<StockMunition> tabStockMunition;



    //Création des monstres

    vector<PetitMonstre> tabPetitMonstre;
    vector<MoyenMonstre> tabMoyenMonstre;
    vector<GrosMonstre> tabGrosMonstre;



    //Initialisations tableaux

    vector<Noeud> noeuds = carte.noeuds;
    vector<vector<int>> grapheNoeuds;
    vector<vector<int>> tabPoids;
    vector<vector<int>> posNoeuds;
    constructGraphes (noeuds, grapheNoeuds, tabPoids, posNoeuds);
    vector<vector<int>> tabVagues = creerTabVague();
    vector<vector<int>> creerTabVague() ;



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


        // TEST FIN DU JEU
        if (arrive) {
            endGame = 2;
        }
        if (indice == tabVagues.size()-1) {
            if ((tabPetitMonstre.size() == 0) && (tabMoyenMonstre.size() == 0) && (tabGrosMonstre.size() == 0)) {
                endGame = 1;
            }
        }
        if  (endGame == 1) {
            printf("VOUS AVEZ GAGNEEEEEEEEEEEEEEEEEEEE\n");
            loop = 0;
            break;
            }
        else if (endGame == 2) {
            printf("vous avez perduuuuuuuuuuuuu\n");
            loop = 0;
            break;
        }



        if(play){
        startTime = SDL_GetTicks();
        time = SDL_GetTicks()/1000;
        frameIndex=SDL_GetTicks()/300;
        augmenteAllTours(tabRadar, tabUsineArmement, tabStockMunition, tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
        attaqueAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        tuerAllMonstre(carte, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        creerVague(indice, tabVagues, time, nbLoop, start, end, posNoeuds, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre, grapheNoeuds, tabPoids);
        updateAllMonstre(tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre, posNoeuds, arrive);
        }
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        // Affichage des éléments
        carte.afficherCarte(textCarte, 15., 8.4);


        drawAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, WINDOW_WIDTH, WINDOW_HEIGHT, frameIndex);
        drawAllBatiments(tabRadar, tabUsineArmement, tabStockMunition, frameIndex);
        attaqueAllTower(tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        drawTourShape(mousex, mousey, carte);        
        drawAllMonstres(frameIndex, tabPetitMonstre, tabMoyenMonstre, tabGrosMonstre);
        interface.drawInterface(carte, tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabRadar, tabUsineArmement, tabStockMunition);


        
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
                    clicOnInterface = interface.clicOnInterface(mousex, mousey, carte, tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte, tabPoids, grapheNoeuds, posNoeuds, tabRadar, tabUsineArmement, tabStockMunition);
                    if(!clicOnInterface){
                        if(play){
                            if(interface.select==1){
                                tourbleue.poser(mousex, mousey, carte, tabTourBleue, tabPoids, grapheNoeuds, posNoeuds);
                                interface.select = 0;
                            }
                            if(interface.select==2){
                                tourverte.poser(mousex, mousey, carte, tabTourVerte, tabPoids, grapheNoeuds, posNoeuds);
                                interface.select = 0;
                            }
                            if(interface.select==3){
                                tourjaune.poser(mousex, mousey, carte, tabTourJaune, tabPoids, grapheNoeuds, posNoeuds);
                                interface.select = 0;
                            }
                            if(interface.select==4){
                                tourrouge.poser(mousex, mousey, carte, tabTourRouge, tabPoids, grapheNoeuds, posNoeuds);
                                interface.select = 0;
                            }
                            if(interface.select==5){
                                radar.poser(mousex, mousey, carte, tabRadar);
                                interface.select = 0;
                            }
                            if(interface.select==6){
                                uarmement.poser(mousex, mousey, carte, tabUsineArmement);
                                interface.select = 0;
                            }
                            if(interface.select==7){
                                stomuni.poser(mousex, mousey, carte, tabStockMunition);
                                interface.select = 0;
                            }
                            
                            temp_tour_select = clickOnTowers(mousex, mousey, carte);
                            printf("%d\n", interface.tour_select);
                            if(temp_tour_select > -1){
                                interface.tour_select = temp_tour_select;
                                if(interface.tour_select == 1){
                                    interface.indice_tour = getTourBleue(mousex, mousey, tabTourBleue);
                                }
                                 if(interface.tour_select == 2){
                                    interface.indice_tour = getTourVerte(mousex, mousey, tabTourVerte);
                                }
                                 if(interface.tour_select == 3){
                                    interface.indice_tour = getTourJaune(mousex, mousey, tabTourJaune);
                                }
                                 if(interface.tour_select == 4){
                                    interface.indice_tour = getTourRouge(mousex, mousey, tabTourRouge);
                                }
                                if(interface.tour_select == 5){
                                    interface.indice_tour = getRadar(mousex, mousey, tabRadar);
                                }
                                if(interface.tour_select == 6){
                                    interface.indice_tour = getUsineArmement(mousex, mousey, tabUsineArmement);
                                }
                                if(interface.tour_select == 7){
                                    interface.indice_tour = getStockMunition(mousex, mousey, tabStockMunition);
                                }
                            }
                            

                            //afficherTourSelect(mousex, mousey, tour_select, tabTourBleue, tabTourJaune, tabTourRouge, tabTourVerte);
                        }
                    }
                    // else{
                    //     clicOnInterface = false;

                    // }
                    
                    carte.isConstructible(mousex, mousey, WINDOW_WIDTH, WINDOW_HEIGHT);
                    
                    
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    //bleu1.afficherEtat();
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
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