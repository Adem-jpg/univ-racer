#include <SDL2/SDL.h>

int main()
{
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Renderer* renderer; // Déclaration du rendu
    SDL_Event event; // Événements

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

    // Fond de la fenetre en noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
                }
            }
        }
        // actualisation de l'affichage
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
} 
