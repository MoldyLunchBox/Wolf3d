#ifndef WOLF3D_H
#define WOLF3D_H
#define W_W 600
#define W_H 600
#define mapWidth  24
#define mapHeight  24
void min_map(SDL_Renderer *rend, int worldMap[mapWidth][mapHeight], int px, int py);

void put_player(int pixel_skip, int pos_x, int pos_y, SDL_Renderer *rend);
#endif