#include <SDL2/SDL.h>
#include <sys/time.h>
#include "vehicule.hpp"

int main()
{
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Renderer* renderer; // Déclaration du rendu
    SDL_Event event; // Événements
    SDL_Surface* s;
    SDL_Texture* t;

    int gaming = 1;

    // Initialisation de SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Erreur d’initialisation de la SDL: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Creation de la fenêtre et du rendu
    if (SDL_CreateWindowAndRenderer(1600, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)){
        printf("Erreur de la creation d’une window: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

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
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
                        v.forward();
                        break;
                    case SDLK_s:
                        //fonction stop temporaire
                        v.stop();
                        break;
                    case SDLK_a:
                        v.left();
                        break;
                    case SDLK_d:
                        v.right();
                        break;
                    case SDLK_ESCAPE:
                        gaming = 0; break;
                    default:
                        break;
                }
            }
        }
        // printf("%lf\n",(double)ti.tv_sec*1000 + (double)ti.tv_usec/1000);
        if( (double)ti.tv_sec*1000 + (double)ti.tv_usec/1000 > ( (double)tdatalimiter.tv_sec*1000 + (double)tdatalimiter.tv_usec/1000 ) + 1 ){

            v.deplacer();
            updatespeed++;
            gettimeofday(&tdatalimiter,NULL);

        }
        gettimeofday(&ti,NULL);

        //update data

        //limitation a 60 fps
        if( (double)ti.tv_sec*1000. + (double)ti.tv_usec/1000. > ( (double)tlimiter.tv_sec*1000. + (double)tlimiter.tv_usec/1000. ) + 1000./60. ){

        // actualisation de l'affichage
            SDL_RenderClear(renderer);

            SDL_Rect rectv = {(int)v.getX(),(int)v.getY(),25,40};
            SDL_RenderCopyEx(renderer,t, NULL, &rectv,v.getAngle(), NULL, SDL_FLIP_NONE);

            SDL_RenderPresent(renderer);

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
