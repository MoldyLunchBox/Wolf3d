#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
#include "wolf3d.h"
#include <string.h>

#define PI 3.1415926535
#define mapX 24	//map width
#define mapY 24
#define wallPadding 10
#define cellS 20 //map cube size
#define mapS mapX * cellS
#define WALL_H 50

int sound_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50)
         return (1);
   }
   return (0);
}

int play_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3 && b.y <= W_H/3 + 155)
         return (1);
   }
   return (0);
}

int quit_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3+200 && b.y <= W_H/3+200+155)
         return (1);
   }
   return (0);
}

int menu_icon_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= 10 && b.x <= 60 && b.y >= 10 && b.y <= 60)
         return (1);
   }
   return (0);
}

int menu_buttons_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-100 && b.x <= W_W/2+100)
      {
         if (b.y >= (W_H/6*0)+(12*1) && b.y <= (W_H/6*0)+(12*1) + W_H/6)
            return (1);
         if (b.y >= (W_H/6*1)+(12*2) && b.y <= (W_H/6*1)+(12*2) + W_H/6)
            return (2);
         if (b.y >= (W_H/6*2)+(12*3) && b.y <= (W_H/6*2)+(12*3) + W_H/6)
            return (3);
         if (b.y >= (W_H/6*3)+(12*4) && b.y <= (W_H/6*3)+(12*4) + W_H/6)
            return (4);
         if (b.y >= (W_H/6*4)+(12*5) && b.y <= (W_H/6*4)+(12*5) + W_H/6)
            return (5);
      }
   }
   return (0);
}

int close_btn_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W - 55 && b.x <= W_W - 15 && b.y >= 15 && b.y <= 55)
         return (1);
   }
   return (0);
}

int img_player_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.y >= W_H/2+W_H/6 && b.y <= W_H/2+W_H/6+W_H/2-W_H/4)
      {
         if (b.x >= W_W/5 && b.x <= W_W/5 + W_W/9)
            return (1);
         if (b.x >= W_W-W_W/5-W_W/10 && b.x <= W_W-W_W/5-W_W/10 + W_W/9)
            return (2);
      }
   }
   return (0);
}

int back_btn_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50)
         return (1);
   }
   return (0);
}

// int open_view(int tex)
// {
	
// 	if (tex == 2 && )
// 		return (1);
// }

float dtor(float d)
{
    return (d * PI / 180.0f);
}

float distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax)*(bx - ax) + (by - ay)*(by - ay)));
}

int text[] =		
	{
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,1,1,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,1,1,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,1,1,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0
};
int map12[] =		//the map array. Edit to change level but keep the outer walls
{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		
};

int map[] =		//the map array. Edit to change level but keep the outer walls
{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		
};

void    create_obj(t_obj *obj)
{
    obj = (t_obj*)malloc(sizeof(t_obj));
}

void    init_obj(t_obj *obj, float x, float y, float z, float frameWidth, float frameHigth, int state, int size_x, float size_y, float frameCount, float row, float surface_w, int fps, SDL_Texture *texture)
{
    obj->x = x;
    obj->y = y;
	obj->z = z;
    obj->frameWidth = frameWidth;
    obj->frameHigth = frameHigth;
    obj->state = state;
    obj->size_x = size_x;
    obj->size_y = size_y;
    obj->frameCount = frameCount;
    obj->row = row;
	obj->surface_w = surface_w;
	obj->fps = fps;
	obj->texture = texture;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	    case 1:
	        return *p;
	        break;

	    case 2:
	        return *(Uint16 *)p;
	        break;

	    case 3:
	        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	            return p[0] << 16 | p[1] << 8 | p[2];
	        else
	            return p[0] | p[1] << 8 | p[2] << 16;
	            break;

	        case 4:
	            return *(Uint32 *)p;
	            break;

	        default:
	            return 0;       /* shouldn't happen, but avoids warnings */
	      }
}

float range_conversion_val(float old_max, float old_min, float new_max, float new_min, float old_value)
{
	float old_range = (old_max - old_min);
	float new_range = (new_max - new_min);  
	float new_value = (((old_value - old_min) * new_range) / old_range) + new_min;
	return (new_value);
}
float safe_angle(float a)
{
	if (a > 2*PI)
			a -= 2*PI;
	if (a < 0)
			a += 2*PI;
	return (a);
}
float safe_angle_180(float a)
{
	if (a > PI)
			a -= PI;
	if (a < -PI)
			a += PI;
	return (a);
}
void safe_map(t_player *player, float pdx, float pdy)
{	
	int x0=0;
	int y0=0;
	if (pdx<0)
		x0=-wallPadding;
	else
		x0=wallPadding;
	if (pdy<0)
		y0=-wallPadding;
	else
		y0=wallPadding;
	int ipx=player->x/cellS;
	int ipx_add_x0=(player->x+x0)/cellS;
	int ipx_sub_x0=(player->x-x0)/cellS;
	int ipy=player->y/cellS;
	int ipy_add_y0=(player->y+y0)/cellS;
	int ipy_sub_y0=(player->y-y0)/cellS;

	if (ipy*mapX + ipx_add_x0 != 0 && map[ipy*mapX + ipx_add_x0] == 0)
		player->x+=pdx*player->speed;
	if (ipy_add_y0*mapX + ipx != 0 && map[ipy_add_y0*mapX + ipx] == 0)
		player->y+=pdy*player->speed;
}

void show_door_code(t_player *player, float pdx, float pdy, t_envirenment *env)
{
	int x0=0;
	int y0=0;
	if (pdx<0)
		x0=-cellS;
	else
		x0=cellS;
	int ipx=player->x/cellS;
	int ipx_add_x0=(player->x+x0)/cellS;
	int ipy=player->y/cellS;
	int ipy_add_y0=(player->y+y0)/cellS;
	if (map[ipy_add_y0*mapX + ipx_add_x0] == 2 && env->code_valid == SDL_FALSE)
		env->screen = 4;
}

void open_door(t_player *player, float pdx, float pdy, t_envirenment *env)
{
   	int x0=0;
	int y0=0;
	if (pdx<0)
		x0=-cellS;
	else
		x0=cellS;
	int ipx=player->x/cellS;
	int ipx_add_x0=(player->x+x0)/cellS;
	int ipy=player->y/cellS;
	int ipy_add_y0=(player->y+y0)/cellS;
	if (map[ipy_add_y0*mapX + ipx_add_x0] == 2)
	{
		env->fps--;
		if(env->fps == 0)
		{
			env->frame_door++;
			env->fps = 2;
		}
		if (env->frame_door == 6)
		{
			env->frame_door = 7;
			map[ipy_add_y0*mapX + ipx_add_x0] = 0;
		}
	}
}

void sprites_reset(t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	//static
	init_obj(&ob_sprites[0], 4*20, 4*20, 20, 820, 1694, 1, 3, 1, 0, 0, 820, 2, tx_sprites[0]);
	init_obj(&ob_sprites[1], 5*20, 3*20, 20, 600, 600, 1, 4, 4, 0, 0, 600, 2, tx_sprites[1]);
	//enemy
	init_obj(&ob_sprites[2], 5*20, 5*20, 20, 910, 1493, 1, 3, 2, 0, 0, 910, 2, tx_sprites[2]);
	init_obj(&ob_sprites[3], 16*20, 3*20, 20, 910, 1493, 1, 3, 2, 0, 0, 910, 2, tx_sprites[2]);
	//coin
	init_obj(&ob_sprites[4], 5*20, 8*20, 20, 512, 512, 3, 5, 5, 0, 0, 512, 2, tx_sprites[3]);
	init_obj(&ob_sprites[5], 6*20, 9*20, 20, 512, 512, 3, 5, 5, 0, 0, 512, 2, tx_sprites[3]);
	init_obj(&ob_sprites[6], 7*20, 10*20, 20, 512, 512, 3, 5, 5, 0, 0, 512, 2, tx_sprites[3]);
	init_obj(&ob_sprites[7], 15*20, 3*20, 20, 512, 512, 3, 5, 5, 0, 0, 512, 2, tx_sprites[3]);
}

void player_reset(t_player *player)
{
	player->x = 2*cellS + 2.0f; //depent to map
    player->y = 2*cellS + 2.0f; //depent to map
    player->a = dtor(1.0f);
	player->rotatSpeed = dtor(6.0f); // 0.5 not map 2.0 with map
	player->size = cellS / 5;
	player->speed = 4;
	player->fov = 60.0;
	player->player_num = 1;
	player->frame_player_x = 1;
   	player->frame_player_y = 1;
	map[56]=2;

}

void env_reset(t_envirenment *env)
{
	env->code_valid = SDL_FALSE;
	env->len_code = 1;
	env->rust_code[0] = ' ';
	env->rust_code[1] = '\0';
	env->screen = 1;
	env->fps = 2;
	env->frame_door=0;
	env->fade = 220;
	env->num_sprites = 8;
	env->solde = 0;
	env->minimap = SDL_FALSE;
	env->texture = SDL_FALSE;
	env->skybox = SDL_FALSE;
	env->bg_music_active = SDL_TRUE;
}

void update(SDL_Renderer *rend, t_player *player, t_envirenment *env)
{
	const uint8_t* keys = SDL_GetKeyboardState(NULL);

	float dx = 0.0f, dy = 0.0f;

	if (keys[SDL_SCANCODE_S])
    {
		player->frame_player_x+=2;
        player->frame_player_y = 0;
       
		dx -= cos(player->a);
        dy += sin(player->a);
	}
	if (keys[SDL_SCANCODE_W])
    {
		player->frame_player_x+=2;
        player->frame_player_y = 1;
		dx += cos(player->a);
        dy -= sin(player->a);
	}
	player->a = -range_conversion_val(W_W, 0, 2*PI, -2*PI, env->mouse_x);
	if (keys[SDL_SCANCODE_LEFT])
	{
		player->a += player->rotatSpeed;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		player->a -= player->rotatSpeed;
		if (player->a < 0)
			player->a += 2 * PI;
	}
	if (player->a > 2 * PI)
			player->a -= 2 * PI;
	if (player->frame_player_x > 20)
       player->frame_player_x = 0;
    if (player->frame_player_x < 0)
       player->frame_player_x = 20;
	safe_map(player, dx, dy);
	show_door_code(player, dx, dy, env);
	if (env->code_valid)
		open_door(player, dx, dy, env);
}

void draw_player(t_player *player, SDL_Renderer *rend)
{
	int i;
	int j;
	i = (player->y);
	while (i < player->y + player->size)
	{
		j = (player->x);
		while (j < player->x + player->size)
		{
			SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
			SDL_RenderDrawPoint(rend, j, i);
			j++;
		}
		i++;
	}
	SDL_RenderDrawLine(rend, player->x+player->size/2, player->y+player->size/2, player->x + 20 * cos(player->a) + player->size/2, player->y - 20 * sin(player->a) + player->size/2);
}

void sort_sprites(t_obj *ob_sprites, int num_sp)
{
	int i, j;
    t_obj temp;
    
    for (i = 0; i < num_sp - 1; i++)
    {
        for (j = 0; j < (num_sp - 1 - i); j++)
        {
            if (ob_sprites[j].dist_to_player < ob_sprites[j + 1].dist_to_player)
            {
                temp = ob_sprites[j];
                ob_sprites[j] = ob_sprites[j + 1];
                ob_sprites[j + 1] = temp;
            } 
        }
    }
}

void draw_sprite(SDL_Renderer *rend, t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	//enemy_movement
	// enemy_animation(env, &ob_sprites[2]);
	for (int i = 0; i < env->num_sprites; i++)
	{
		if (ob_sprites[i].state == 2)
		{
			ob_sprites[i].fps--;
			if (ob_sprites[i].fps == 0)
			{
				ob_sprites[i].frameCount++;
				ob_sprites[i].fps = 2;
			}
			if (ob_sprites[i].frameCount > 16)
				ob_sprites[i].frameCount = 0;

			int spx = (int)ob_sprites[i].x/cellS;
			int spy = (int)ob_sprites[i].y/cellS;
			int spx_add = ((int)ob_sprites[i].x + 15)/cellS;
			int spy_add = ((int)ob_sprites[i].y + 15)/cellS;
			int spx_sub = ((int)ob_sprites[i].x - 15)/cellS;
			int spy_sub = ((int)ob_sprites[i].y - 15)/cellS;
			if (ob_sprites[i].x > player->x && map[spy*mapX+spx_sub] == 0)
				ob_sprites[i].x-=0.5;
			if (ob_sprites[i].x < player->x && map[spy*mapX+spx_add] == 0)
				ob_sprites[i].x+=0.5;
			if (ob_sprites[i].y > player->y && map[spy_sub*mapX+spx] == 0)
				ob_sprites[i].y-=0.5;
			if (ob_sprites[i].y < player->y && map[spy_add*mapX+spx] == 0)
				ob_sprites[i].y+=0.5;
			//player lose
			if (player->x > ob_sprites[i].x - 10 && player->x < ob_sprites[i].x + 10 && player->y > ob_sprites[i].y - 10 && player->y < ob_sprites[i].y + 10)
				env->screen = 5;
		}
		if (ob_sprites[i].state == 3)
		{
			if (player->x > ob_sprites[i].x - 15 && player->x < ob_sprites[i].x + 15 && player->y > ob_sprites[i].y - 15 && player->y < ob_sprites[i].y + 15)
			{
				Mix_PlayChannel(1, env->coin_sound, 0);
				ob_sprites[i].state = 0;
				env->solde+=1;
			}
		}
	}
	//draw sprites
	for (int i=0; i<env->num_sprites; i++)
	{
		float dist = distance(player->x, player->y, ob_sprites[i].x, ob_sprites[i].y);
		ob_sprites[i].dist_to_player = dist;
	}
	sort_sprites(ob_sprites, env->num_sprites);
	for (int i=0; i<env->num_sprites; i++)
	{
		// printf("%f\n",ob_sprites[i].z);
		if (ob_sprites[i].state != 0)
		{
			float dx = ob_sprites[i].x - player->x;
			float dy = ob_sprites[i].y - player->y;


			float target_ang = fmodf((atan2(dx, dy)) + 2*PI, 2*PI) + PI/2;
			target_ang = safe_angle(target_ang);
			float tmp_player_angng = player->a + PI ;
			tmp_player_angng = safe_angle(tmp_player_angng);


			float diff_angles = fmodf((tmp_player_angng - target_ang) + PI + 2*PI,  2*PI) - PI;
			diff_angles = safe_angle_180(diff_angles);
			SDL_Rect rect0, rect1;

			if (diff_angles < PI/6 && diff_angles > -PI/6)
			{
				ob_sprites[i].h = ((WALL_H * 220) / ob_sprites[i].dist_to_player)/ob_sprites[i].size_y;
				ob_sprites[i].w = ((WALL_H * 220) / ob_sprites[i].dist_to_player)/ob_sprites[i].size_x;
				float sx = range_conversion_val(dtor(player->fov/2), -dtor(player->fov/2), W_W , 0-ob_sprites[i].w, diff_angles); //ob_sprites[i].size decalage pour sprite width
				for (int j = (int)sx; j < (int)sx + ob_sprites[i].w; j++)
				{
					if (ob_sprites[i].dist_to_player < player->dist[j])
					{
						float on_floor = ((WALL_H * 220) / ob_sprites[i].dist_to_player) / 2;

						rect0 = (SDL_Rect){ob_sprites[i].frameWidth * ob_sprites[i].frameCount + ((float)ob_sprites[i].surface_w/ob_sprites[i].w * (j-(int)sx)), ob_sprites[i].frameHigth * ob_sprites[i].row, (float)ob_sprites[i].surface_w/ob_sprites[i].w, ob_sprites[i].frameHigth};
						rect1 = (SDL_Rect){j, W_H/2 + on_floor - ob_sprites[i].h, 1, ob_sprites[i].h};
						if(SDL_RenderCopyEx(rend, ob_sprites[i].texture, &rect0, &rect1, 0, NULL, SDL_FLIP_NONE) != 0)
						{
							printf("create tx_sprite1 Error: %s\n", SDL_GetError());
    					    SDL_Quit();
						}
					}
				}
			}
		}
	}
}

void render_view(SDL_Renderer *rend, t_player *player, t_ray r, t_texture t, SDL_Surface **walls, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *ceil, t_envirenment *env)
{
	float line_h;
	SDL_Rect line;
	int y;

	line.w = W_W/numRays;
	line.x = r.num*line.w;
	line.h = 1;
	
	line_h = (WALL_H * 220) / r.dist; //220 how player far to screen

	if (t.num == 1)
		(t.img) = walls[0];
	if (t.num == 2)
		(t.img) = doors[env->frame_door];
	t.ty_step = (t.img)->w / (float)line_h;
	t.ty_offset = 0;
	if (line_h > W_H)
	{
		t.ty_offset = (line_h - W_H) / 2.0;
		line_h = W_H;
	}
	if (line_h <= 0)
		line_h = 1;
	// printf("%f\n", line_h);
	
	t.ty = t.ty_offset * t.ty_step;	
	t.scaling=(float)(t.img)->w/cellS;
	if (r.shade == 1)
	{
		t.tx = (int)(r.rx*t.scaling)%(t.img)->w; //scaling = scal (t.img)
		if (r.ra > PI)
			t.tx=((t.img)->w-1)-t.tx; // flip direction left/right
	}
	else
	{
		t.tx = (int)(r.ry*t.scaling)%(t.img)->w;
		if (r.ra > PI/2 && r.ra < (3*PI)/2)
			t.tx=((t.img)->w-1)-t.tx; // flip direction left/right
	}
	//wall
	for (y = 0; y < line_h; y++)
	{
		line.y = (W_H / 2) - (line_h / 2) + y; //offset to center
		// float c = text[(int)(ty)*32 + (int)(t.tx)] * r.shade;
		// SDL_SetRenderDrawColor(rend, 255 - (c * 100), 255 - (c * 100), 255 - (c * 100), 255);
		if (env->texture)
		{
			if (t.num == 2)
				r.shade = 1;
			SDL_Color rgb;
			Uint32 data = getpixel((t.img), (int)(t.tx), (int)(t.ty));
			SDL_GetRGB(data, (t.img)->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r*r.shade, rgb.g*r.shade, rgb.b*r.shade, 255);
		}
		SDL_RenderFillRect(rend, &line);
		t.ty+=t.ty_step;
	}
	for (y = (W_H / 2) + (line_h / 2); y < W_H; y++)
	{
		// draw floor
		line.y = y;
		float dy = y-(W_H/2.0);
		r.ra = safe_angle(r.ra);
		float raFix = cos(player->a - r.ra);
		t.tx = player->x*28 + cos(r.ra)*220*floor->w/dy/raFix;
		t.ty = player->y*28 - sin(r.ra)*220*floor->w/dy/raFix;
		SDL_SetRenderDrawColor(rend, 200, 100, 50, 255);
		// float c = text[((int)(t.ty)&31)*32 + ((int)(t.tx)&31)] * 0.7;
		// SDL_SetRenderDrawColor(rend, 255 - (c * 100), 255 - (c * 100), 255 - (c * 100), 255);
		
		SDL_Color rgb;
		Uint32 data;
		if (env->texture)
		{
			data = getpixel(floor, (int)(t.tx)&(floor->w-1), (int)(t.ty)&(floor->w-1));
			SDL_GetRGB(data, floor->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
		}
		SDL_RenderFillRect(rend, &line);
		// draw ceiling
		line.y = (W_H/2.0) - (y - (W_H/2.0)) - 1;
		SDL_SetRenderDrawColor(rend, 150, 150, 200, 255);
		if (env->texture && !env->skybox)
		{
			data = getpixel(ceil, (int)(t.tx)&(ceil->w-1), (int)(t.ty)&(ceil->w-1));
			SDL_GetRGB(data, ceil->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
			SDL_RenderFillRect(rend, &line);
		}
		
		if (!env->texture)
			SDL_RenderFillRect(rend, &line);
	}

}

void render_rays(SDL_Renderer *rend, t_player *player, SDL_Surface **walls, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *ceil, t_envirenment *env)
{
	int mx,my,mp,dof; //m=map, p=position, r=ray, dof=deept of field
	t_ray ray;
	t_texture tex;
	
	tex.vmt = 0;
	tex.hmt = 0;
	tex.img = walls[0];
	ray.ra = player->a + dtor(player->fov / 2);
	
	for (ray.num = 0; ray.num < numRays; ray.num++)
	{
		ray.ra = safe_angle(ray.ra);
		// check horizental line
		dof = 0;
		ray.dist_h = 100000;
		ray.hx = player->x;
		ray.hy = player->y;
		if (ray.ra != 0. && ray.ra != PI)
		{
			float aTan = 1/(tan(ray.ra));
			if (ray.ra < PI) //look up
			{
				ray.ry = (((int)(player->y) / cellS) * cellS - 0.0001);
				ray.rx = player->x - (ray.ry - player->y)*aTan;
				ray.yo = -(cellS);
				ray.xo = -ray.yo*aTan;
			}
			if (ray.ra > PI) //look down
			{
				ray.ry = (((int)(player->y) / cellS) * cellS) + cellS;
				ray.rx = player->x - (ray.ry - player->y)*aTan;
				ray.yo = cellS;
				ray.xo = -ray.yo*aTan;
			}
		}
		else //look rigth or left
		{
			ray.rx = player->x;
			ray.ry = player->y;
			dof = mapX;
		}
		
		while (dof < mapX)
		{
			mx = (int)(ray.rx)/cellS;
			my = (int)(ray.ry)/cellS;
			mp = my*mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] >= 1) //hit wall
			{
				ray.hx = ray.rx;
				ray.hy = ray.ry;
				ray.dist_h = distance(player->x, player->y, ray.hx, ray.hy);
				dof = mapX;
				tex.hmt=map[mp];
			}	
			else
			{
				// printf("tt\n");
				ray.rx+=ray.xo;
				ray.ry+=ray.yo;
				dof+=1;
			}
		}

		//check vertical line
		dof = 0;
		ray.dist_v = 100000;
		ray.vx = player->x;
		ray.vy = player->y;
	
		float aTan = (tan(ray.ra));
		if (ray.ra > PI/2 && ray.ra < (3*PI)/2) //look left
		{
			ray.rx = (((int)(player->x) / cellS) * cellS - 0.0001);
			ray.ry = player->y - (ray.rx - player->x)*aTan;
			ray.xo = -(cellS);
			ray.yo = -ray.xo*aTan;
		}
		if (ray.ra < PI/2 || ray.ra > (3*PI)/2) //look right
		{
			ray.rx = (((int)(player->x) / cellS) * cellS) + cellS;
			ray.ry = player->y - (ray.rx - player->x)*aTan;
			ray.xo = cellS;
			ray.yo = -ray.xo*aTan;
		}
		if (ray.ra == 0. || ray.ra == PI)//look stright rigth or left
		{
			ray.rx = player->x;
			ray.ry = player->y;
			dof = mapX;
		}
		// printf("%f %f %f\n", ray.ra, player->a, tan(ray.ra));
		
		while (dof < mapX)
		{
			mx = (int)(ray.rx)/cellS;
			my = (int)(ray.ry)/cellS;
			mp = my*mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] >= 1) //hit wall
			{
				ray.vx = ray.rx;
				ray.vy = ray.ry;
				ray.dist_v = distance(player->x, player->y, ray.vx, ray.vy);
				dof = mapY;
				tex.vmt=map[mp];
			}	
			else
			{
				ray.rx+=ray.xo;
				ray.ry+=ray.yo;
				dof+=1;
			}
		}
		ray.shade = 1;
		if (ray.dist_v < ray.dist_h)
		{
			tex.num = tex.vmt;
			ray.shade = 0.5;
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist = ray.dist_v;
			if((ray.ra >= PI/2 && ray.ra <= (3*PI)/2))
				SDL_SetRenderDrawColor(rend, 0, 0, 150, 255);
			else
				SDL_SetRenderDrawColor(rend, 0, 150, 0, 255);
		}
		if (ray.dist_h < ray.dist_v)
		{
			tex.num = tex.hmt;
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist = ray.dist_h;
			if (ray.ra <= PI)
				SDL_SetRenderDrawColor(rend, 200, 0, 200, 255);
			else
				SDL_SetRenderDrawColor(rend, 200, 200, 0, 255);
		}
		ray.ca = safe_angle(player->a - ray.ra);
		
		ray.dist *=cos(ray.ca); //fix fisheye 
		
		player->dist[ray.num] = ray.dist;
		render_view(rend, player, ray, tex, walls, doors, floor, ceil, env);

		ray.ra-=dtor(0.1);
	}
}


void render_map(t_player *player, SDL_Renderer *rend)
{
	int x, y, xo, yo;
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			yo = y * cellS;
			while (yo < y * cellS + cellS)
			{
				xo = x * cellS;
				while (xo < x * cellS + cellS)
				{
					if (map[y * mapX + x] >= 1)
						SDL_SetRenderDrawColor(rend, 150, 150, 150, 255);
					else
						SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
					if (x * cellS == xo || y * cellS == yo)
						SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
					SDL_RenderDrawPoint(rend, xo, yo);
					xo++;
				}
				yo++;
			}
		}
	}
	draw_player(player, rend);
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderDrawPoint(rend, 4*20, 4*20);
	SDL_RenderDrawPoint(rend, 4*20+1, 4*20);
	SDL_RenderDrawPoint(rend, 4*20-1, 4*20);
	SDL_RenderDrawPoint(rend, 4*20, 4*20+1);
	SDL_RenderDrawPoint(rend, 4*20, 4*20-1);

}

void	draw_sky(SDL_Renderer *rend, SDL_Surface *sky, t_player *player)
{
	int x, y, x0;

	for(x=0; x<600; x++)
	{

		for(y=0; y<300; y++)
		{			
			x0 = (int)(player->a*5 / PI * 180.0f) - x;
			if (x0 < 0)
				x0+=800;
			x0=x0%800;
			SDL_Color rgb;
			Uint32 data = getpixel(sky, x0, y);
			SDL_GetRGB(data, sky->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
			SDL_RenderDrawPoint(rend, x, y);
		}
	}
}

void render(SDL_Renderer *rend, t_player *player, SDL_Surface **walls, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *sky, SDL_Surface *ceil, t_obj *ob_sprites, t_envirenment *env)
{
	if (env->skybox)
		draw_sky(rend, sky, player);
    render_rays(rend, player, walls, doors, floor, ceil, env);
	draw_sprite(rend, player, ob_sprites, env);
    if (env->minimap)
        render_map(player, rend);
}

void            write_text(SDL_Renderer *rend, TTF_Font  *font, char *str, int x, int y)
{
	SDL_Color white = {0, 0, 0, 255};
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, str, white); 
	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x; //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect

	SDL_RenderCopy(rend, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

int main(int argc, char *argv[])
{
	/****************************** START-VARIABLES ****************************/
	t_envirenment env;
	t_player player;
	player_reset(&player);
	env_reset(&env);
	if( TTF_Init() != 0)
	{
        printf("Font init: %s", SDL_GetError());
		SDL_Quit();
        return (1);
    }

	TTF_Font  *font1= TTF_OpenFont("/Library/Fonts/Arial.ttf", 42);
	TTF_Font  *font2= TTF_OpenFont("/Library/Fonts/Arial.ttf", 26);

    if (font1 == NULL)
    {
        printf("Font1 error: %s", SDL_GetError());
		SDL_Quit();
        return (1);
    }
	if (font2 == NULL)
    {
        printf("Font2 error: %s", SDL_GetError());
		SDL_Quit();
        return (1);
    }

	SDL_Surface *wall = IMG_Load("resources/wall.png");
	SDL_Surface *door = IMG_Load("resources/door1.png");
	SDL_Surface *floor = IMG_Load("resources/floor.png");
	SDL_Surface *ceil = IMG_Load("resources/ceiling.png");
	SDL_Surface *sky = IMG_Load("resources/menu_sc.png");
	SDL_Surface *sprite1 = IMG_Load("resources/pillar.png");
	SDL_Surface *sprite2 = IMG_Load("resources/ball.png");
	SDL_Surface *sprite3 = IMG_Load("resources/enemy.png");
	SDL_Surface *sprite4 = IMG_Load("resources/coin.png");

	SDL_Surface *door1 = IMG_Load("resources/door1.png");
	SDL_Surface *door2 = IMG_Load("resources/door2.png");
	SDL_Surface *door3 = IMG_Load("resources/door3.png");
	SDL_Surface *door4 = IMG_Load("resources/door4.png");
	SDL_Surface *door5 = IMG_Load("resources/door5.png");
	SDL_Surface *door6 = IMG_Load("resources/door6.png");
	SDL_Surface *door7 = IMG_Load("resources/door7.png");
	SDL_Surface *door8 = IMG_Load("resources/door8.png");
	SDL_Surface *door9 = IMG_Load("resources/door9.png");
	
	
	// SDL_Surface *enemy1 = IMG_Load("resources/e1.png");
	// SDL_Surface *enemy2 = IMG_Load("resources/e2.png");
	// SDL_Surface *enemy3 = IMG_Load("resources/e3.png");
	// SDL_Surface *enemy4 = IMG_Load("resources/e4.png");
	// SDL_Surface *enemy5 = IMG_Load("resources/e5.png");
	// SDL_Surface *enemy6 = IMG_Load("resources/e6.png");
	// SDL_Surface *enemy7 = IMG_Load("resources/e7.png");
	// SDL_Surface *enemy8 = IMG_Load("resources/e8.png");
	// SDL_Surface *enemy9 = IMG_Load("resources/e9.png");
	// SDL_Surface *enemy10 = IMG_Load("resources/e10.png");
	// SDL_Surface *enemy11 = IMG_Load("resources/e11.png");
	// SDL_Surface *enemy12 = IMG_Load("resources/e12.png");
	// SDL_Surface *enemy13 = IMG_Load("resources/e13.png");
	// SDL_Surface *enemy14 = IMG_Load("resources/e14.png");
	// SDL_Surface *enemy15 = IMG_Load("resources/e15.png");
	// SDL_Surface *enemy16 = IMG_Load("resources/e16.png");
	// SDL_Surface *enemy17 = IMG_Load("resources/e17.png");
	
   	SDL_Surface *welcom_sc;
   	SDL_Surface *wolf3d;
   	SDL_Surface *play;
	SDL_Surface *quit;
   	SDL_Surface *menu_icon;
   	SDL_Surface *icon;
   	SDL_Surface *player1;
   	SDL_Surface *player2;
   	SDL_Surface *menu_sc;
   	SDL_Surface *menu_btns;
   	int menu_btn_clicked = 0;
   	int previous_screen = 1;
   	SDL_Surface *options_pupop;
   	int options_pupop_showed = 0;
   	SDL_Surface *close_btn;
   	int img_player_selected = 1;
   	SDL_Surface *img_player1;
   	SDL_Surface *img_player2;
   	SDL_Surface *selection_img_player;
	SDL_Surface *rust_code_sc;
	SDL_Surface *back_btn;
	SDL_Surface *calculator;
	SDL_Surface *lose_sc;

	double frame_sound = 0;

	SDL_Surface *walls[1];
	walls[0] = wall;
	SDL_Surface *doors[9];
	doors[0] = door1;
	doors[1] = door2;
	doors[2] = door3;
	doors[3] = door4;
	doors[4] = door5;
	doors[5] = door6;
	doors[6] = door7;
	doors[7] = door8;
	doors[8] = door9;

	// SDL_Surface *enemys[18];
	// enemys[0] = enemy1;
	// enemys[1] = enemy2;
	// enemys[2] = enemy3;
	// enemys[3] = enemy4;
	// enemys[4] = enemy5;
	// enemys[5] = enemy6;
	// enemys[6] = enemy7;
	// enemys[7] = enemy8;
	// enemys[8] = enemy9;
	// enemys[9] = enemy10;
	// enemys[10] = enemy11;
	// enemys[11] = enemy12;
	// enemys[12] = enemy13;
	// enemys[13] = enemy14;
	// enemys[14] = enemy15;
	// enemys[15] = enemy16;
	// enemys[16] = enemy17;
	/****************************** END-VARIABLES ****************************/
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return (1);
    }
	SDL_Window *window = SDL_CreateWindow(
		"Wolf3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		W_W,
		W_H,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (rend == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) //Initialisation de l'API Mixer
   	{
   	   printf("3%s", Mix_GetError());
   	   return (1);
   	}

   	Mix_VolumeMusic(MIX_MAX_VOLUME/4);

	/************************ load textures **********************************/ 

	if (wall == NULL)
	{
    	printf("Failed to load image at 'resource/wall.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (door == NULL)
	{
    	printf("Failed to load image at 'resource/door.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}


	if (floor == NULL)
	{
    	printf("Failed to load image at 'resource/floor.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (ceil == NULL)
	{
    	printf("Failed to load image at 'resource/ceil.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (sky == NULL)
	{
    	printf("Failed to load image at 'resource/sky.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (sprite1 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite1.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}
	if (sprite2 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite2.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}
	if (sprite3 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite3.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}
	if (sprite4 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite4.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	SDL_Texture *tx_sprite1;
	tx_sprite1 = SDL_CreateTextureFromSurface(rend, sprite1);
	if(tx_sprite1 == NULL)
	{
		SDL_FreeSurface(sprite1);
		printf("create tx_sprite1 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Texture *tx_sprite2;
	tx_sprite2 = SDL_CreateTextureFromSurface(rend, sprite2);
	if(tx_sprite2 == NULL)
	{
		SDL_FreeSurface(sprite2);
		printf("create tx_sprite2 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Texture *tx_sprite3;
	tx_sprite3 = SDL_CreateTextureFromSurface(rend, sprite3);
	if(tx_sprite3 == NULL)
	{
		SDL_FreeSurface(sprite3);
		printf("create tx_sprite3 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Texture *tx_sprite4;
	tx_sprite4 = SDL_CreateTextureFromSurface(rend, sprite4);
	if(tx_sprite4 == NULL)
	{
		SDL_FreeSurface(sprite4);
		printf("create tx_sprite4 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}
	SDL_Rect rect_icon_coin_s = (SDL_Rect){0,0,512,512};
	SDL_Rect rect_icon_coin_d = (SDL_Rect){W_W/2-35,10,30,30};

	SDL_Texture *tx_sprites[4];
	tx_sprites[0] = tx_sprite1;
	tx_sprites[1] = tx_sprite2;
	tx_sprites[2] = tx_sprite3;
	tx_sprites[3] = tx_sprite4;
   	
   	icon = IMG_Load("resources/sound.png");
   	if (!icon)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_sound_s;
   	SDL_Rect rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	SDL_Texture *tx_icon = SDL_CreateTextureFromSurface(rend, icon);
   	SDL_FreeSurface(icon);

   	player1 = IMG_Load("resources/player1.png");
   	if (!player1)
   	{
   	   printf("5%s", SDL_GetError());
   	   return (1);
   	}
   	player2 = IMG_Load("resources/player2.png");
   	if (!player2)
   	{
   	   printf("5%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_player1_s;
	SDL_Rect rect_player2_s;
   	SDL_Rect rect_player_d = (SDL_Rect){W_W/2 - 150, W_H - 300, 300, 650};
   	SDL_Texture *tx_player1 = SDL_CreateTextureFromSurface(rend, player1);
   	SDL_Texture *tx_player2 = SDL_CreateTextureFromSurface(rend, player2);
   	SDL_FreeSurface(player1);
   	SDL_FreeSurface(player2);

   	welcom_sc = IMG_Load("resources/welcom_sc.png");
   	if (!welcom_sc)
   	{
   	   printf("6%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_welcom_sc_s;
   	SDL_Rect rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_welcom_sc = SDL_CreateTextureFromSurface(rend, welcom_sc);
   	SDL_FreeSurface(welcom_sc);


   	wolf3d = IMG_Load("resources/wolf3d.png");
   	if (!wolf3d)
   	{
   	   printf("7%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_wolf3d_s;
   	SDL_Rect rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   	SDL_Texture *tx_wolf3d = SDL_CreateTextureFromSurface(rend, wolf3d);
   	SDL_FreeSurface(wolf3d);
	

	// door_auto = IMG_Load("resources/door_auto.png");
	// if (!door_auto)
   	// {
   	//    printf("7%s", SDL_GetError());
   	//    return (1);
   	// }
   	// SDL_Rect rect_door_auto_s;
   	// SDL_Rect rect_door_auto_d = (SDL_Rect){0, 0, 250, 250};
   	// SDL_Texture *tx_door_auto = SDL_CreateTextureFromSurface(rend, door_auto);
   	// SDL_FreeSurface(door_auto);

   	play = IMG_Load("resources/play.png");
   	if (!play)
   	{
   	   printf("8%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_play_s;
   	SDL_Rect rect_play_d = (SDL_Rect){W_W/2-125, W_H/3, 250, 155};
   	SDL_Texture *tx_play = SDL_CreateTextureFromSurface(rend, play);
   	SDL_FreeSurface(play);

	quit = IMG_Load("resources/quit.png");
   	if (!quit)
   	{
   	   printf("8%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_quit_s;
   	SDL_Rect rect_quit_d = (SDL_Rect){W_W/2-125, W_H/3 + 200, 250, 155};
   	SDL_Texture *tx_quit = SDL_CreateTextureFromSurface(rend, quit);
   	SDL_FreeSurface(quit);

   	menu_icon = IMG_Load("resources/menu_icon.png");
   	if (!menu_icon)
   	{
   	   printf("9%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_icon_s;
   	SDL_Rect rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
   	SDL_Texture *tx_menu_icon = SDL_CreateTextureFromSurface(rend, menu_icon);
   	SDL_FreeSurface(menu_icon);

   	menu_sc = IMG_Load("resources/menu_sc.png");
   	if (!menu_sc)
   	{
   	   printf("10%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_sc_s;
   	SDL_Rect rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_menu_sc = SDL_CreateTextureFromSurface(rend, menu_sc);
   	SDL_FreeSurface(menu_sc);

   	menu_btns = IMG_Load("resources/menu_buttons.png");
   	if (!menu_btns)
   	{
   	   printf("11%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_btns_home_s;
   	SDL_Rect rect_menu_btns_home_d = (SDL_Rect){W_W/2 - 100, (W_H/6*0)+(12*1), 200, W_H/6};
   	SDL_Rect rect_menu_btns_resume_s;
   	SDL_Rect rect_menu_btns_resume_d = (SDL_Rect){W_W/2 - 100, (W_H/6*1)+(12*2), 200, W_H/6};
   	SDL_Rect rect_menu_btns_restart_s;
   	SDL_Rect rect_menu_btns_restart_d = (SDL_Rect){W_W/2 - 100, (W_H/6*2)+(12*3), 200, W_H/6};
   	SDL_Rect rect_menu_btns_options_s;
   	SDL_Rect rect_menu_btns_options_d = (SDL_Rect){W_W/2 - 100, (W_H/6*3)+(12*4), 200, W_H/6};
   	SDL_Rect rect_menu_btns_exit_s;
   	SDL_Rect rect_menu_btns_exit_d = (SDL_Rect){W_W/2 - 100, (W_H/6*4)+(12*5), 200, W_H/6};
   	SDL_Texture *tx_menu_btns = SDL_CreateTextureFromSurface(rend, menu_btns);
   	SDL_FreeSurface(menu_btns);

   	options_pupop = IMG_Load("resources/options_pupop.png");
   	if (!options_pupop)
   	{
   	   printf("12%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_options_pupop_s;
   	SDL_Rect rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   	SDL_Texture *tx_options_pupop = SDL_CreateTextureFromSurface(rend, options_pupop);
   	SDL_FreeSurface(options_pupop);

   	close_btn = IMG_Load("resources/close_btn.png");
   	if (!close_btn)
   	{
   	   printf("13%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_close_btn_s;
   	SDL_Rect rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   	SDL_Texture *tx_close_btn = SDL_CreateTextureFromSurface(rend, close_btn);
   	SDL_FreeSurface(close_btn);

   	img_player1 = IMG_Load("resources/img_player1.png");
   	if (!img_player1)
   	{
   	   printf("14%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_img_player1_s;
   	SDL_Rect rect_img_player1_d = (SDL_Rect){W_W/5, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   	SDL_Texture *tx_img_player1 = SDL_CreateTextureFromSurface(rend, img_player1);
   	SDL_FreeSurface(img_player1);

   	img_player2 = IMG_Load("resources/img_player2.png");
   	if (!img_player2)
   	{
   	   printf("15%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_img_player2_s;
   	SDL_Rect rect_img_player2_d = (SDL_Rect){W_W-W_W/5-W_W/10, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   	SDL_Texture *tx_img_player2 = SDL_CreateTextureFromSurface(rend, img_player2);
   	SDL_FreeSurface(img_player2);

   	selection_img_player = IMG_Load("resources/selection_img_player.png");
   	if (!selection_img_player)
   	{
   	   printf("16%s", SDL_GetError());
   	   return (1);
   	}
   	SDL_Rect rect_selection_img_player_s;
   	SDL_Rect rect_selection_img_player_d;
   	SDL_Texture *tx_selection_img_player = SDL_CreateTextureFromSurface(rend, selection_img_player);
   	SDL_FreeSurface(selection_img_player);

	rust_code_sc = IMG_Load("resources/rust_code_sc.png");
   	if (!rust_code_sc)
   	{
   	   printf("16%s", SDL_GetError());
   	   return (1);
   	}
   	SDL_Rect rect_rust_code_sc_s = (SDL_Rect){0, 0, 250, 250};
   	SDL_Rect rect_rust_code_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_rust_code_sc = SDL_CreateTextureFromSurface(rend, rust_code_sc);
   	SDL_FreeSurface(rust_code_sc);

	back_btn = IMG_Load("resources/back_btn.png");
   	if (!back_btn)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_back_btn_s;
   	SDL_Rect rect_back_btn_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	SDL_Texture *tx_back_btn = SDL_CreateTextureFromSurface(rend, back_btn);
   	SDL_FreeSurface(back_btn);

	calculator = IMG_Load("resources/calculator.png");
   	if (!calculator)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_calculator_s;
   	SDL_Rect rect_calculator_d = (SDL_Rect){W_W/2-90, 60, 200, 70};
   	SDL_Texture *tx_calculator = SDL_CreateTextureFromSurface(rend, calculator);
   	SDL_FreeSurface(calculator);

	lose_sc = IMG_Load("resources/lose_sc.png");
   	if (!lose_sc)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_lose_sc_s;
   	SDL_Rect rect_lose_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_lose_sc = SDL_CreateTextureFromSurface(rend, lose_sc);
   	SDL_FreeSurface(lose_sc);



   	Mix_Music *music;
   	music = Mix_LoadMUS("resources/music.wav");
   	Mix_PlayMusic(music, -1);

   	Mix_AllocateChannels(3);
   	// Mix_Chunk *son1;
   	// Mix_Chunk *son2;
   	env.foots_sound = Mix_LoadWAV("resources/running.wav");
   	env.coin_sound = Mix_LoadWAV("resources/coin_sound.wav");
	env.bg_music = Mix_LoadWAV("resources/bg_music.wav");
   	Mix_VolumeChunk(env.foots_sound, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
   	Mix_VolumeChunk(env.coin_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env.bg_music, MIX_MAX_VOLUME/4);

   	Mix_PlayChannel(0, env.foots_sound, -1);//Joue le son1 1 sur le canal 1 ; le joue une fois (0 + 1)
	Mix_PlayChannel(2, env.bg_music, -1);
   	Mix_Pause(0);
	Mix_Pause(2);
	t_obj ob_sprites[env.num_sprites];
	sprites_reset(ob_sprites, tx_sprites);
	// printf("%f\n",ob_sprites[1].z);
	//SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_bool is_run = SDL_TRUE;
	
	SDL_Event e;

	int x;
	while (is_run)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				is_run = SDL_FALSE;
			if (e.type == SDL_TEXTINPUT && env.screen == 4)
			{
				if (env.len_code < 5)
				{
					strcat(env.rust_code, e.text.text);
					env.len_code++;
				}
			}
			if (e.type ==SDL_MOUSEMOTION)
				env.mouse_x = e.motion.x;
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
            	if (sound_press(e.button) && env.screen == 2 && options_pupop_showed == 0)
            	{
            	   if(Mix_PausedMusic() == 1) //Si la music est en pause
            	   {
            	      frame_sound = 0;
            	      Mix_ResumeMusic(); //Reprendre la music
            	   }
            	   else
            	   {
            	      frame_sound = 1;
            	      Mix_PauseMusic(); //Mettre en pause la music
            	   }
            	}
				if (play_press(e.button) && env.screen == 1)
				{
					SDL_Rect r = (SDL_Rect){0,0,W_W,W_H};
               		env.screen = 2;
					for (int i=255;i>0;i--)
					{
						SDL_SetRenderDrawColor(rend, 0, 0, 0, i);
						SDL_RenderFillRect(rend, &r);
					}
				}
				if (quit_press(e.button) && env.screen == 1)
               		is_run = SDL_FALSE;
            	if (menu_icon_press(e.button) && env.screen == 2 && env.screen != 3 && options_pupop_showed == 0)
            	{
            	   previous_screen = env.screen;
            	   env.screen = 3;
            	}
            	else if (menu_icon_press(e.button) && env.screen == 3 && options_pupop_showed == 0)
            	   env.screen = previous_screen;
            	if (close_btn_press(e.button) && options_pupop_showed == 1)
            	   options_pupop_showed = 0;
            	img_player_selected = img_player_press(e.button);
            	if (img_player_selected && options_pupop_showed == 1)
            	   player.player_num = img_player_selected;
            	menu_btn_clicked = menu_buttons_press(e.button);
            	if (menu_btn_clicked && env.screen == 3 && options_pupop_showed == 0)
            	{
            	   	if (menu_btn_clicked == 1)
            	   		env.screen = 1;
            	   	if (menu_btn_clicked == 2)
						env.screen = 2;
            	   	if (menu_btn_clicked == 3)
            	   	{
					   player_reset(&player);
					   env_reset(&env);
					   env.screen = 2;
            	   	}
            	   	if (menu_btn_clicked == 4)
            	   		options_pupop_showed = 1;
            	   	if (menu_btn_clicked == 5)
            			is_run   = SDL_FALSE;
            	}
				if (back_btn_press(e.button) && env.screen == 4)
				{
					player_reset(&player);
               		env.screen = 2;
				}
				if (env.screen == 5)
				{
					env.screen = 1;
					player_reset(&player);
					sprites_reset(ob_sprites, tx_sprites);
				}
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					is_run = SDL_FALSE;
				if (e.key.keysym.sym == SDLK_m)
					env.minimap = !env.minimap;
				if (e.key.keysym.sym == SDLK_t)
					env.texture = !env.texture;
				if (e.key.keysym.sym == SDLK_k)
					env.skybox = !env.skybox;
				if (e.key.keysym.sym == SDLK_BACKSPACE && env.screen == 4)
				{
					if (env.len_code > 1)
					{
						env.rust_code[env.len_code - 1] = '\0';
						env.len_code--;
					}
				}
			}
			if (e.type == SDL_KEYDOWN)
			{		
				if (e.key.keysym.sym == SDLK_w)
				{
                  	Mix_Resume(0);
				}
				if (e.key.keysym.sym == SDLK_s)
				{
                  	Mix_Resume(0);
				}
			}
			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_w)
				{
					player.frame_player_x = 1;
   					player.frame_player_y = 1;
					Mix_Pause(0);
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					player.frame_player_x = 1;
   					player.frame_player_y = 0;
					Mix_Pause(0);
				}
			}
		}
		SDL_RenderClear(rend);
		if (env.screen == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
		if (env.screen == 2)
			Mix_Resume(2);
		else
			Mix_Pause(2);
		if (env.screen == 1)
      	{
      	   	SDL_RenderClear(rend);
      	   	rect_welcom_sc_s = (SDL_Rect){0, 0, 612, 344};
      	   	rect_wolf3d_s = (SDL_Rect){0, 0, 867, 364};
      	   	rect_play_s = (SDL_Rect){0, 0, 250, 155};
			rect_quit_s = (SDL_Rect){0, 0, 250, 155};
      	   	SDL_RenderCopyEx(rend, tx_welcom_sc, &rect_welcom_sc_s, &rect_welcom_sc_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_wolf3d, &rect_wolf3d_s, &rect_wolf3d_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_play, &rect_play_s, &rect_play_d, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(rend, tx_quit, &rect_quit_s, &rect_quit_d, 0, NULL, SDL_FLIP_NONE);
      	}
		if (env.screen == 2)
      	{
      	   	SDL_RenderClear(rend);
			update(rend, &player, &env);
			render(rend, &player, walls, doors, floor, sky, ceil, ob_sprites, &env);
      	   	rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   	rect_sound_s = (SDL_Rect){752 * frame_sound, 0, 752, 774};
      	   	rect_player1_s = (SDL_Rect){363 * player.frame_player_x, 1105 * player.frame_player_y, 363, 1105};
			rect_player2_s = (SDL_Rect){449 * player.frame_player_x, 1105 * player.frame_player_y, 449, 1105};
      	   	SDL_RenderCopyEx(rend, tx_icon, &rect_sound_s, &rect_sound_d, 0, NULL, SDL_FLIP_NONE);
      	   	if (player.player_num == 1)
      	   	   SDL_RenderCopyEx(rend, tx_player1, &rect_player1_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
      	   	else
      	   	   SDL_RenderCopyEx(rend, tx_player2, &rect_player2_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(rend, tx_sprite4, &rect_icon_coin_s, &rect_icon_coin_d, 0, NULL, SDL_FLIP_NONE);
			write_text(rend, font2, ft_strjoin("x ", ft_itoa(env.solde)), W_W/2, 10);
			if (env.fade > 0)
			{
				SDL_Rect r;
				SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(rend, 0,0,0,env.fade);
				r=(SDL_Rect){0,0,W_W,W_H};
				SDL_RenderFillRect(rend, &r);
				env.fade-=10;
			}
		  }
		if (env.screen == 3)
      	{
      	   SDL_RenderClear(rend);
      	   rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   rect_menu_sc_s = (SDL_Rect){0, 0, 800, 600};
      	   rect_menu_btns_home_s = (SDL_Rect){0, 0, 281, 137};
      	   rect_menu_btns_resume_s = (SDL_Rect){0, 1*137, 281, 137};
      	   rect_menu_btns_restart_s = (SDL_Rect){0, 2*137, 281, 137};
      	   rect_menu_btns_options_s = (SDL_Rect){0, 3*137, 281, 137};
      	   rect_menu_btns_exit_s = (SDL_Rect){0, 4*137, 281, 137};
      	   SDL_RenderCopyEx(rend, tx_menu_sc, &rect_menu_sc_s, &rect_menu_sc_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_home_s, &rect_menu_btns_home_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_resume_s, &rect_menu_btns_resume_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_restart_s, &rect_menu_btns_restart_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_options_s, &rect_menu_btns_options_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_exit_s, &rect_menu_btns_exit_d, 0, NULL, SDL_FLIP_NONE);
      	}
		if (env.screen == 4)
      	{
      	   	SDL_RenderClear(rend);
			rect_back_btn_s = (SDL_Rect){0, 0, 120, 120};
			rect_calculator_s = (SDL_Rect){0, 0, 150, 46};
      	   	SDL_RenderCopyEx(rend, tx_rust_code_sc, &rect_rust_code_sc_s, &rect_rust_code_sc_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_back_btn, &rect_back_btn_s, &rect_back_btn_d, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(rend, tx_calculator, &rect_calculator_s, &rect_calculator_d, 0, NULL, SDL_FLIP_NONE);
			write_text(rend, font1, env.rust_code, W_W/2-90, 75);
			
      	}
		if (env.screen == 5)
      	{
      	   	SDL_RenderClear(rend);
			rect_lose_sc_s = (SDL_Rect){0, 0, 1624, 892};
			SDL_RenderCopyEx(rend, tx_lose_sc, &rect_lose_sc_s, &rect_lose_sc_d, 0, NULL, SDL_FLIP_NONE);
			
      	}
		if (strcmp(env.rust_code, " 1337") == 0 && env.screen == 4)
		{
			env.code_valid = SDL_TRUE;
			env.screen = 2;
		}
		if (options_pupop_showed == 1)
      	{
      	   	rect_options_pupop_s = (SDL_Rect){0, 0, 771, 638};
      	   	rect_close_btn_s = (SDL_Rect){0, 0, 300, 300};
      	   	rect_img_player1_s = (SDL_Rect){0, 0, 363, 1105};
			rect_img_player2_s = (SDL_Rect){0, 0, 449, 1105};
      	   	SDL_RenderCopyEx(rend, tx_options_pupop, &rect_options_pupop_s, &rect_options_pupop_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_close_btn, &rect_close_btn_s, &rect_close_btn_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_img_player1, &rect_img_player1_s, &rect_img_player1_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_img_player2, &rect_img_player2_s, &rect_img_player2_d, 0, NULL, SDL_FLIP_NONE);
      	   	if (player.player_num == 1)
      	   	   rect_selection_img_player_d = rect_img_player1_d;
      	   	else
      	   	   rect_selection_img_player_d = rect_img_player2_d;
      	   	SDL_RenderCopyEx(rend, tx_selection_img_player, &rect_img_player1_s, &rect_selection_img_player_d, 0, NULL, SDL_FLIP_NONE);
      	}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	Mix_FreeChunk(env.foots_sound);//Libération du son 1
   	Mix_FreeChunk(env.coin_sound);
	Mix_FreeMusic(music); //Libération de la music
	SDL_DestroyTexture(tx_icon);
   	SDL_DestroyTexture(tx_player1);
   	SDL_DestroyTexture(tx_player2);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}