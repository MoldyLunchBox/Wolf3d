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
	int frame_gun_x;
	int frame_gun_y;
	SDL_bool gun_animation;
	SDL_bool is_shoot;
	double blood;
	SDL_Rect life;

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
	Mix_Chunk *bg_music;
	Mix_Chunk *enemy_sound;
	Mix_Chunk *gun_fire_sound;
	int mouse_x;
	SDL_bool minimap;
	SDL_bool texture;
	SDL_bool skybox;
	SDL_bool bg_music_active;
	int		near_enemy;
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
	float				dist_to_player;
	SDL_Texture 		*texture;
	int 				fps;
	SDL_bool			alive;
}   			t_obj;

typedef struct  s_pnt
{
	int x;
	int y;
}				t_pnt;
#endif