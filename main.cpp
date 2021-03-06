#include <SDL2/SDL.h>
#include <sys/time.h>
#include "vehicule.hpp"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 800


int main(int ac, char ** av)
{
    //ouverture du fichier
    FILE* fichier = fopen(av[1],"r");

    //creation de la map
    int map[DISPLAY_WIDTH/10][DISPLAY_HEIGHT/10] = {'r'};

    // detection d'erreur de lecture
    if(fichier == NULL){
        printf("Erreur dans la lecture de fichier");
    }


    int xFile = 0;
    int yFile = 0;
    int tempC;

    //generation de la map depuis un fichier
    for(int y = 0; y < DISPLAY_HEIGHT/10; y++){
        for(int x = 0; x < DISPLAY_WIDTH/10; x++){
            map[x][y] = fgetc(fichier);
            if(map[x][y] == '\n'){
                map[x][y] = fgetc(fichier);
            }
        }
    }

    //fermeture du fichier a la fin du chargement de la map 
    fclose(fichier);

    //debug pour afficher la map entiere dans le terminal
    // for(int y = 0; y < DISPLAY_HEIGHT/10; y++){
    //     for(int x = 0; x < DISPLAY_WIDTH/10; x++){
    //         printf("%c",map[x][y]);
    //     }
    //     printf("\n");
    // }

    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Renderer* renderer; // Déclaration du rendu
    SDL_Event event; // Événements
    SDL_Surface* s;
    SDL_Texture* t;
    SDL_Texture* tGrass;

    int gaming = 1;
    double previousX = 0;
    double previousY = 0;

    // Initialisation de SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Erreur d’initialisation de la SDL: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Creation de la fenêtre et du rendu
    if (SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)){
        printf("Erreur de la creation d’une window: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //chargement de la texture du vehicule
    s = SDL_LoadBMP("V.bmp");
    if(s==NULL){
        printf("Erreur dans SDL_LoadBMP: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    t = SDL_CreateTextureFromSurface(renderer,s);
    if(t==NULL){
        printf("Erreur dans SDL_CreateTextureFromSurface: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // chargement d'une texture d'herbe
    s = SDL_LoadBMP("grass.bmp");
    if(s==NULL){
        printf("Erreur dans SDL_LoadBMP(grass.bmp): %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    tGrass = SDL_CreateTextureFromSurface(renderer,s);
    if(t==NULL){
        printf("Erreur dans SDL_CreateTextureFromSurface(grass.bmp): %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Vehicule v = Vehicule();

    int loopcount = 0;
    int fpscount = 0;
    int updatespeed = 0;
    struct timeval ti;
    struct timeval tbuffer;
    struct timeval tlimiter;
    struct timeval tdatalimiter;
    gettimeofday(&ti,NULL);
    gettimeofday(&tbuffer,NULL);
    gettimeofday(&tlimiter,NULL);
    gettimeofday(&tdatalimiter,NULL);


    // Fond de la fenetre en noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Boucle principale
    while( gaming ){
        //events
        while( SDL_PollEvent( &event ) ){
            switch(event.type){
                case SDL_QUIT:
                    gaming = 0; break;
                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_w:
                        v.setForward(VEHICULE_SPEED);
                        break;
                    case SDLK_s:
                        v.setForward(-VEHICULE_SPEED);
                        break;
                    case SDLK_a:
                        v.setLeftTurn(1);
                        break;
                    case SDLK_d:
                        v.setRightTurn(1);
                        break;
                    case SDLK_ESCAPE:
                        gaming = 0; break;
                    default:
                        break;
                }
                break;
                case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_a:
                        v.setLeftTurn(0);

                        break;
                    case SDLK_d:
                        v.setRightTurn(0);
                        break;
                    case SDLK_w:
                    case SDLK_s:
                        v.setForward(0);
                        break;
                }
                break;

            }
        }

        //update data
        if( (double)ti.tv_sec*1000 + (double)ti.tv_usec/1000 > ( (double)tdatalimiter.tv_sec*1000 + (double)tdatalimiter.tv_usec/1000 ) + 10. ){
            // garder en memoire la derniere position
            previousX = v.getX();
            previousY = v.getY();

            v.deplacer();
            if(map[(int)v.getX()/10][(int)v.getY()/10]=='g'){
                // appliquer la derniere position si le vehicule est dans de l'herbe
                v.setX(previousX);
                v.setY(previousY);
            }
            //offset de 3 et 4 pour la largeur/longueure de la voiture (a modifier avec des getWidth etc)
            if(map[((int)v.getX()/10)+3][((int)v.getY()/10)+4]=='g'){
                v.setX(previousX);
                v.setY(previousY); 
            }

            updatespeed++;
            gettimeofday(&tdatalimiter,NULL);

        }
        gettimeofday(&ti,NULL);


        //limitation a 60 fps
        if( (double)ti.tv_sec*1000. + (double)ti.tv_usec/1000. > ( (double)tlimiter.tv_sec*1000. + (double)tlimiter.tv_usec/1000. ) + 1000./60. ){

        // actualisation de l'affichage
            SDL_RenderClear(renderer);

            //rendu du sol
            for(int y = 0; y < DISPLAY_HEIGHT/10; y++){
                for(int x = 0; x < DISPLAY_WIDTH/10; x++){
                    if(map[x][y] == 'g'){
                        SDL_Rect rectGrass = {x*10,y*10,10,10};
                        SDL_RenderCopy(renderer,tGrass,NULL,&rectGrass);
                    }
                }
            }

            //rendu du vehicule
            SDL_Rect rectv = {(int)v.getX(),(int)v.getY(),25,40};
            SDL_RenderCopyEx(renderer,t, NULL, &rectv,v.getAngle(), NULL, SDL_FLIP_NONE);
            

            //rendu a l'ecran
            SDL_RenderPresent(renderer);

            //timer d'fps
            gettimeofday(&tlimiter,NULL);
            fpscount++;
        }
        
        if( ((double)ti.tv_sec) > ((double)tbuffer.tv_sec) ){
            printf("FPS: %d\n",fpscount);
            printf("loops/s: %d\n",loopcount);
            printf("updates/s: %d\n",updatespeed);
            gettimeofday(&tbuffer,NULL);
            fpscount = 0;
            loopcount = 0;
            updatespeed = 0;
        }
        loopcount ++;
    }

    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
} 
