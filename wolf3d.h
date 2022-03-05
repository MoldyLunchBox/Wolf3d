#ifndef WOLF3D_H
#define WOLF3D_H
#define W_W 600
#define W_H 600
#define mapWidth  24
#define mapHeight  24
#define numRays 600

#include <math.h>
#include "./libft/libft.h"

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
	int len_code;
	char rust_code[6];
	int screen;
	int fps;
	int frame_door;
	SDL_bool code_valid;
	int fade;
	int num_sprites;
	int solde;
	Mix_Chunk *foots_sound;
   	Mix_Chunk *coin_sound;
	int mouse_x;
	SDL_bool minimap;
	SDL_bool texture;
	SDL_bool skybox;
}				t_envirenment;

typedef struct  s_obj
{
    float               x;
    float               y;
	float               z;
    float               frameWidth;
    float               frameHigth;
    int                	state;
    int    				size_x;
	int    				size_y;
    float               frameCount;
    float               row;
	float				h;
	float				w;
	float				surface_w;
	SDL_Texture 		*texture;
	float				dist_to_player;
	int 				fps;
}   			t_obj;
#endif