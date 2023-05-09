/*#include "grid.h"

Grid::Grid(int width, int height, int cellSize) 
{
    m_width = width;
    m_height = height;
    m_cellSize = cellSize;
}

Grid::~Grid() 
{
}

void Grid::draw(SDL_Renderer* renderer) 
{
    // Dessiner les lignes verticales
    for (int i = 0; i <= m_width; i++) 
    {
        SDL_RenderDrawLine(renderer, i * m_cellSize, 0, i * m_cellSize, m_height * m_cellSize);
    }
    // Dessiner les lignes horizontales
    for (int i = 0; i <= m_height; i++) 
    {
        SDL_RenderDrawLine(renderer, 0, i * m_cellSize, m_width * m_cellSize, i * m_cellSize);
    }
}*/
