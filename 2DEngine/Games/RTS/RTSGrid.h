#pragma once
#include <SDL.h>

class RTSGrid 
{

public:

    RTSGrid(int width, int height, int cellSize);
    ~RTSGrid();
    void draw(SDL_Renderer* renderer);

private:

    int m_width; // Largeur de la grille en nombre de cases
    int m_height; // Hauteur de la grille en nombre de cases
    int m_cellSize; // Taille en pixels d'une case
};
