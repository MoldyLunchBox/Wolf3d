#include"SDL.h"
#include "wolf3d.h"



void min_map(SDL_Renderer *rend, int worldMap[mapWidth][mapHeight], int px, int py){
		int i = 0;
        int j;
		int j2;
		int i2;
		SDL_RenderClear(rend);
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		while (i < mapWidth)
		{
			j = 0;
			while (j < mapHeight)
			{
				i2 = (i * 15);
				while (i2 < i * 15 + 15)
				{
					j2 = (j * 15);
					while (j2 < j * 15 + 15)
					{
						if (worldMap[i][j] != 0)
							SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
						else
							SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
						SDL_RenderDrawPoint(rend, j2, i2);
						j2++;
					}
					i2++;
				}
				// break;
				j++;
			}
			i++;
			// break;
		}
put_player(5, px, py, rend);
}