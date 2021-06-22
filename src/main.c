#include "SDL.h"
#include "wolf3d.h"
#include <math.h>
#define PI 3.1415926535
#define mapX 8	//map width
#define mapY 8	//map height
#define mapS 64 //map cube size
int map[] =		//the map array. Edit to change level but keep the outer walls
	{
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
};
void put_player(int pixel_size, int pos_x, int pos_y, SDL_Renderer *rend)
{
	int i2;
	int j2;
	i2 = (pos_y);
	while (i2 < pos_y + pixel_size)
	{
		j2 = (pos_x);
		while (j2 < pos_x + pixel_size)
		{

			SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
			SDL_RenderDrawPoint(rend, j2, i2);
			j2++;
		}
		i2++;
	}
}
void drawMap2D(SDL_Renderer *rend)
{
	int x, y, xo, yo;
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			yo = y * mapS;
			while (yo < y * mapS+64)
			{
			xo = x * mapS;
				while (xo < x * mapS+64)
				{
					if (map[y * mapX + x] == 1)
						SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
					else
						SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
					if (x * mapS == xo ||y * mapS == yo)
					{
						SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
					}
				SDL_RenderDrawPoint(rend, xo, yo);
				xo++;	
				}
				yo++;
			}

		}
	}
}

void	cast_rays(float pa, float py, float px)
{
	int r,mx,my,mp,dof;
	float	rx,ry,ra,xo,yo;
	ra=pa;
	r = 0;
	while (r < 1)
	{
		float aTan = -1/tan(ra);
		if (ra>PI){ ry = (((int)py >> 6) << 6) - 0.0001;

		}
		r++;
	}
}
	int main(int argc, char *argv[])
	{

		/****************************** START-VARIABLES ****************************/
		float pdx = cos (0)*5;
		float pdy = sin(0)*5;  
		float pa = 0;
		double py = 4*64, px = 5*64;		//x and y start position
		double dirX = -1, dirY = 0; //initial direction vector

		double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

		double time = 0;	//time of current frame
		double oldTime = 0; //time of previous frame

		int w = mapWidth;
		int h = mapHeight;

		/****************************** END-VARIABLES ****************************/
		SDL_Init(SDL_INIT_VIDEO);

		int map[mapWidth][mapHeight] =
			{
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

		SDL_Window *window = SDL_CreateWindow(
			"SDL2Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			W_W,
			W_H,
			0);
		SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
		//SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_bool is_run = SDL_TRUE;
		while (is_run)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
					is_run = SDL_FALSE;
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a)
				{
					pa -= 0.5;
					if (pa < 0)
						pa += 2 * PI;
					pdx = cos(pa) * 5;
					pdy = sin(pa) * 5;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d)
				{
					pa += 0.5;
					if (pa > 2 * PI)
						pa -= 2 * PI;
					pdx = cos(pa) * 5;
					pdy = sin(pa) * 5;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
					{px+=pdx;py+=pdy;}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
					 {px-=pdx;py-=pdy;}
				// printf("\nx = %f | y = %f  map = %d ", px, py, map[(int)py][(int)px]);
			}
			SDL_RenderClear(rend);
		
		//    verLine(x, drawStart, drawEnd, color);
		// min_map(rend, map, px, py);
		drawMap2D(rend);
		put_player(10,px,py,rend);
		SDL_RenderDrawLine(rend, px+10/2,py+10/2,px+pdx*5+10/2, py+pdy*5+10/2);
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}