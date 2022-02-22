#ifndef WOLF3D_H
#define WOLF3D_H
#define W_W 600
#define W_H 600
#define mapWidth  24
#define mapHeight  24
#define numRays 600

#include <math.h>
#include <unistd.h>

typedef struct	s_player
{
	float x;
	float y;
	float a;
	float rotatSpeed;
	float size;
	float dist[numRays];
	float speed;
	float fov;
	double frame_player_x;
   	double frame_player_y;
	int player_num;

}				t_player;

typedef struct	s_ray
{
	int num;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float ca;
	float dist;
	float dist_h;
	float hx;
	float hy;
	float dist_v;
	float vx;
	float vy;
	float shade;
}				t_ray;

typedef struct	s_texture
{
	int num;
	int vmt;
	int hmt;
	SDL_Surface *img;
	float ty_step;
	float ty_offset;
	float ty;
	float tx;
	float scaling;
}				t_texture;

typedef struct	s_environment
{

}				t_envirenment;

typedef struct  s_obj
{
    float               x;
    float               y;
	float               z;
    float               frameWidth;
    float               frameHigth;
    char                *textureId;
    SDL_RendererFlip    flip;
    float               speed;
    float               frameCount;
    float               row;
	float				h;
	float				w;
	float				surface_w;
}   			t_obj;
#endif