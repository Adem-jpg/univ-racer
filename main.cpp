#include <SDL2/SDL.h>
#include <time.h>

int main()
{
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Renderer* renderer; // Déclaration du rendu
    SDL_Event event; // Événements
    SDL_Surface* s;
    SDL_Texture* t;


 

    double x = 800;
    double y = 350;
    double vitesse = 1;

    double vitesseX = 0;
    double vitesseY = 0;

    double angle = 7;

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

    // Fond de la fenetre en noir
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Boucle principale
    while( gaming ){
        while( SDL_PollEvent( &event ) ){
            switch(event.type){
                case SDL_QUIT:
                    gaming = 0; break;
                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        gaming = 0; break;
                    default:
                        break;
                }
            }
        }
        //debut 


        if(angle == 0){
            y -= 1;
        } else if(angle > 0 && angle < 90){
            // angle: 90 | 45 | 37
            // %:    100 |    |
            // vitesseY = vitesse * (angle / (int)90);
            // vitesseX = 1 - vitesse * ( angle / (int)90);
            y -= 1. - vitesse * (angle / 90.);
            x += vitesse * ( angle / 90.);
            // printf("vitesse en x:%i, vitesse en y:%i\n",vitesseX,vitesseY);
        } else if(angle == 90){
            x += 1;
        }

        
        


        // actualisation de l'affichage
        SDL_RenderClear(renderer);

        SDL_Rect rectv = {(int)x,(int)y,25,40};
        SDL_RenderCopyEx(renderer,t, NULL, &rectv,angle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
    }

    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
} 
