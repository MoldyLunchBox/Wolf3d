#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}


typedef struct s_2d{
	float x;
	float y;
}				t_2d;

t_2d	find_h_intersect(float py, float pa)
{
	t_2d	ray_pos;
		float yn, xn, ys, xs, ra, rx, ry;
		ra = pa;
	// Horizontal intersection
	if (pa >=0 && pa <= PI/2)
	{
		yn = -(py - (int)(py / 64) * 64);
		xn = -(yn / (tan(ra)+0.000001));
		
	}

	if (pa >PI/2 && pa <= PI)
	{
		yn = -(py - (int)(py / 64) * 64);
		xn = -(yn / (tan(ra)+0.000001));
	}

	if (pa > PI && pa <= 3*PI/2)
	{
		yn =64 - (py - (int)(py / 64) * 64);
		xn = -(yn / (tan(ra)+0.000001));
	}

	if (pa > 3*PI/2 && pa < 2*PI)
	{
		yn =64 - (py - (int)(py / 64) * 64);
		xn = -(yn / (tan(ra)+0.000001));
	}
	
	ys = 64;
	xs = ys / tan(ra);

	ray_pos.x = xn;
	ray_pos.y = yn;
	return ray_pos;

}
t_2d	find_v_intersect(float px, float pa)
{
	t_2d	ray_pos;
		float yn, xn, ys, xs, ra, rx, ry;
		ra = pa;
	// Horizontal intersection
	if (pa >=0 && pa <= PI/2)
	{
		xn = 64 -(px - (int)(px / 64) * 64);
		yn = -(xn * (tan(ra)+0.000001));
	}

	if (pa >PI/2 && pa <= PI)
	{
		xn = -(px - (int)(px / 64) * 64);
		yn = -(xn * (tan(ra)+0.000001));
	}

	if (pa > PI && pa <= 3*PI/2)
	{
		xn = -((px - (int)(px / 64) * 64));
		yn = -(xn * (tan(ra)+0.000001));
	}

	if (pa > 3*PI/2 && pa < 2*PI)
	{
		xn = 64 -(px - (int)(px / 64) * 64);
		yn = -(xn * (tan(ra)+0.000001));
	}

	//xn = 64 -(px - (int)(px / 64) * 64);
	//yn = xn * (tan(ra)+0.000001);

	xs = 64;
	ys = xs / tan(ra);


	ray_pos.x = xn;
	ray_pos.y = yn;
	return ray_pos;

}

void	draw_ray(float pa, float px, float py, SDL_Renderer *rend)
{
	float yn, xn, ys, xs, ra, rx, ry;
	t_2d	ray_hpos;
	t_2d	ray_vpos;
	//testint first intersection
	//SDL_RenderDrawLine(rend, px, py, rx, ry);
	//rx+=xs;
	//ry+=ys;
	//ray_hpos = find_h_intersect(py, pa);
	ray_vpos = find_v_intersect(px, pa);
	SDL_RenderDrawLine(rend, px, py, px+ray_vpos.x, py+ray_vpos.y);
	//SDL_RenderDrawLine(rend, px, py, px+ray_vpos.x, py+ray_vpos.y);
	//printf("%f %f %f %f", px, py, rx, ry);
	//exit(1);
	//testing rest intesection
}

void	cast_rays(float pa, float py, float px)
{
	int r,mx,my,mp,dof;
	float	rx,ry,ra,xo,yo;
	ra=pa;
	r = PI/2;
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
		float pa = 0;
		float pdx = cos (pa)*5;
		float pdy = sin(pa)*5;  
		double py = 4*64+20, px = 5*64+20;		//x and y start position
		double dirX = -1, dirY = 0; //initial direction vector

		double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

		double time = 0;	//time of current frame
		double oldTime = 0; //time of previous frame

		int w = mapWidth;
		int h = mapHeight;

		/****************************** END-VARIABLES ****************************/
		SDL_Init(SDL_INIT_VIDEO);



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
		SDL_RenderDrawLine(rend, px+10/2,py+10/2,px+pdx*5+10/2, py-pdy*5+10/2);
		draw_ray(pa,  px,  py, rend);
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}