#include <SDL.h>
#include <SDL_image.h>
#include "RTSGrid.h"

int main(int argc, char* argv[]) {
    // Initialisation de la bibliothèque SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("RTSGrid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de la texture du personnage
    SDL_Surface* surface = IMG_Load("character.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Création de la grille
    RTSGrid RTSGrid(10, 8, 50);

    // Position du personnage
    int x = 3;
    int y = 2;

    // Rectangle de sélection du personnage
    SDL_Rect selectionRect = { x * 50, y * 50, 50, 50 };
    bool selected = false;

    // Boucle de jeu
    bool quit = false;
    while (!quit) {
        // Gestion des événements
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int RTSGridX = mouseX / 50;
                int RTSGridY = mouseY / 50;

                // Si la souris est sur la case du personnage, on active la sélection
                if (RTSGridX == x && RTSGridY == y) {
                    selected = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                selected = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                if (selected) {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    int RTSGridX = mouseX / 50;
                    int RTSGridY = mouseY / 50;

                    // Déplacement du personnage sur la case sélectionnée
                    x = RTSGridX;
                    y = RTSGridY;

                    // Mise à jour de la position de la sélection
                    selectionRect.x = x * 50;
                    selectionRect.y = y * 50;
                }
            }
        }

        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessin de la grille
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        RTSGrid.draw(renderer);

        // Affichage du personnage
        SDL_Rect destRect = { x * 50, y * 50, 50, 50 };
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        // Affichage de la sélection
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &selectionRect);

        // Mise à jour de l'écran
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // Fermeture de la bibliothèque SDL
    SDL_Quit();

    return 0;
}

