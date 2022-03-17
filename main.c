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

void cursor_mouse(t_envirenment *env)
{
	if (env->screen == 2 && env->mouse_y > 50)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
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

int back_btn_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50)
         return (1);
   }
   return (0);
}

float dtor(float d)
{
    return (d * PI / 180.0f);
}

float distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax)*(bx - ax) + (by - ay)*(by - ay)));
}

void draw_square(SDL_Renderer *rend, int size, int x, int y)
{
	int ix = x-size/2;
	int iy = y-size/2;
	for (int i = 0; i<size; i++)
	{
		SDL_RenderDrawLine(rend, ix, iy, ix+size, iy);
		iy++;
	}
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
		1, 4, 3, 1, 7, 12, 1, 5, 1, 4, 1, 1, 14, 1, 1, 3, 1, 12, 1, 1, 11, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		14, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,
		1, 0, 0, 0, 0, 0, 0, 8, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		5, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 1, 0, 0, 11,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 12,
		8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 1, 0, 0, 1,
		15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		1, 1, 1, 6, 1, 0, 0, 0, 0, 1, 1, 1, 15, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 14,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 7,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		6, 0, 0, 0, 0, 0, 1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 14, 11, 1, 0, 0, 14, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1,
		15, 1, 7, 1, 0, 0, 1, 1, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 14,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 10, 1, 7, 4, 3, 1, 1, 10, 1, 1, 11, 1, 14, 1, 12, 1, 1, 1, 1, 15, 1, 3, 1,
};

void    create_obj(t_obj *obj)
{
    obj = (t_obj*)malloc(sizeof(t_obj));
}

void    init_obj(t_obj *obj, t_vars_obj vars_obj, SDL_Texture *texture)
{
    obj->x = vars_obj.x;
    obj->y = vars_obj.y;
    obj->frame_width = vars_obj.frame_width;
    obj->frame_higth = vars_obj.frame_higth;
    obj->state = vars_obj.state;
    obj->size_x = vars_obj.size_x;
    obj->size_y = vars_obj.size_y;
    obj->frame_num = vars_obj.frame_num;
	obj->surface_w = vars_obj.surface_w;
	obj->texture = texture;
	obj->alive = SDL_TRUE;
	obj->fps = 2;
	obj->row = 0;
	obj->damage = 3;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp;
    Uint8 *p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
	    return (*p);
	else if (bpp == 2)
	    return (*(Uint16 *)p);
	else if (bpp == 3)
	{
	    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	        return (p[0] << 16 | p[1] << 8 | p[2]);
	    else
	        return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (bpp == 4)
	    return (*(Uint32 *)p);
	else
	    return (0);
}

float range_conversion_val(t_pnt old, t_pnt new, float old_value)
{
	float old_range;
	float new_range;
	float new_value;

	old_range = (old.ma - old.mi);
	new_range = (new.ma - new.mi);
	new_value = (((old_value - old.mi) * new_range) / old_range) + new.mi;
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

SDL_bool hit_sprites(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	int s;

	s = 0;
	while (s < env->num_sprites)
	{
		if ((ob_sprites[s].state == 1 || ob_sprites[s].state == 2))
		{
			if (ob_sprites[s].dist_to_player + distance(player->x + 15 * cos(player->a), player->y - 15 * sin(player->a), ob_sprites[s].x, ob_sprites[s].y) > 14.5 && 
			ob_sprites[s].dist_to_player + distance(player->x + 15 * cos(player->a), player->y - 15 * sin(player->a), ob_sprites[s].x, ob_sprites[s].y) < 15.5)
				return (SDL_FALSE);
		}
		s++;
	}
	return (SDL_TRUE);
}

void safe_map(t_player *player, float pdx, float pdy, t_envirenment *env)
{	
	t_var_int vars;

	vars.x0 = 0;
	vars.y0 = 0;
	if (pdx < 0)
		vars.x0 =- wallPadding;
	else
		vars.x0 = wallPadding;
	if (pdy < 0)
		vars.y0 =- wallPadding;
	else
		vars.y0 = wallPadding;
	vars.ipx = player->x / cellS;
	vars.ipx_add_x0 = (player->x + vars.x0) / cellS;
	vars.ipx_sub_x0 = (player->x - vars.x0) / cellS;
	vars.ipy = player->y / cellS;
	vars.ipy_add_y0 = (player->y + vars.y0) / cellS;
	vars.ipy_sub_y0 = (player->y - vars.y0) / cellS;
	if ((vars.ipy * mapX + vars.ipx_add_x0 != 0 && map[vars.ipy * mapX + vars.ipx_add_x0] == 0))
		player->x += pdx * player->speed;
	if ((vars.ipy_add_y0 * mapX + vars.ipx != 0 && map[vars.ipy_add_y0 * mapX + vars.ipx] == 0))
		player->y += pdy * player->speed;
}


void show_door_code(t_player *player, t_envirenment *env)
{
	t_var_int vars;

	vars.x0 = cellS;
	vars.ipx = player->x / cellS;
	vars.ipx_add_x0 = (player->x + vars.x0) / cellS;
	vars.ipy = player->y / cellS;
	vars.ipy_add_y0 = player->y / cellS;
	if (map[vars.ipy_add_y0 * mapX + vars.ipx_add_x0] == 2 && env->code_valid == SDL_FALSE)
		env->screen = 4;
}

void open_door(t_player *player, t_envirenment *env)
{
	env->fps--;
	if(env->fps == 0)
	{
		env->frame_door++;
		env->fps = 2;
	}
	if (env->frame_door == 4)
	{
		env->frame_door = 5;
		map[56] = 0;
	}
}

void sprites_reset(t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	//static
	init_obj(&ob_sprites[0], (t_vars_obj){4*20, 4*20, 820, 1694, 1, 3, 1, 0, 820}, tx_sprites[0]);
	init_obj(&ob_sprites[1], (t_vars_obj){5*20, 3*20, 280, 270, 1, 3, 3, 0, 280}, tx_sprites[1]);
	//enemy
	init_obj(&ob_sprites[2], (t_vars_obj){5*20, 5*20, 910, 1493, 2, 3, 2, 0, 910}, tx_sprites[2]);
	init_obj(&ob_sprites[3], (t_vars_obj){16*20, 3*20, 910, 1493, 2, 3, 2, 3, 910}, tx_sprites[2]);
	init_obj(&ob_sprites[4], (t_vars_obj){2*20, 15*20, 910, 1493, 2, 3, 2, 6, 910}, tx_sprites[2]);
	init_obj(&ob_sprites[5], (t_vars_obj){3*20, 13*20, 910, 1493, 2, 3, 2, 8, 910}, tx_sprites[2]);
	//coin
	init_obj(&ob_sprites[6], (t_vars_obj){5*20, 8*20, 512, 512, 3, 5, 5, 0, 512}, tx_sprites[3]);
	init_obj(&ob_sprites[7], (t_vars_obj){6*20, 9*20, 512, 512, 3, 5, 5, 0, 512}, tx_sprites[3]);
	init_obj(&ob_sprites[8], (t_vars_obj){7*20, 10*20, 512, 512, 3, 5, 5, 0, 512}, tx_sprites[3]);
	init_obj(&ob_sprites[9], (t_vars_obj){15*20, 3*20, 512, 512, 3, 5, 5, 0, 512}, tx_sprites[3]);
	//static
	init_obj(&ob_sprites[10], (t_vars_obj){9*20+10, 1*20+10, 295, 400, 1, 3, 3, 0, 295}, tx_sprites[4]);
	init_obj(&ob_sprites[11], (t_vars_obj){10*20+8, 8*20+8, 260, 310, 1, 3, 3, 0, 260}, tx_sprites[6]);
	//aid_kit
	init_obj(&ob_sprites[12], (t_vars_obj){2*20+10, 22*20+10, 223, 200, 4, 4, 4, 0, 223}, tx_sprites[5]);
}

void player_reset(t_player *player)
{
	player->x = 2 * cellS + 2.0f;
    player->y = 2 * cellS + 2.0f;
    player->a = dtor(1.0f);
	player->rotatSpeed = dtor(6.0f);
	player->size = cellS / 5;
	player->speed = 4;
	player->fov = 60.0;
	player->frame_gun_x = 0;
	player->frame_gun_y = 0;
	player->gun_animation = SDL_FALSE;
	player->is_shoot = SDL_FALSE;
	map[56] = 2;
	player->blood = W_W/4;
	player->life = (SDL_Rect){40, W_H - 32, player->blood, 5};
	player->damaged = SDL_FALSE;
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
	env->num_sprites = 13;
	env->solde = 0;
	env->minimap = SDL_FALSE;
	env->texture = SDL_TRUE;
	env->skybox = SDL_FALSE;
	env->bg_music_active = SDL_TRUE;
	env->enemy_num = 4;
}

void gun_animation(SDL_Renderer *rend, SDL_Texture *tx_gun, t_player *player, SDL_Surface **shoots)
{
	SDL_Rect rect_gun_s;
	SDL_Rect rect_gun_d;

	rect_gun_s = (SDL_Rect){0, 0, 1920, 1080};
   	rect_gun_d = (SDL_Rect){W_W/2-250, W_H-280, 500, 280};
	if (player->gun_animation)
	{
		player->frame_gun_x++;
		if (player->frame_gun_x == 1)
			player->is_shoot = SDL_FALSE;
		if (player->frame_gun_x > 8)
		{
			player->frame_gun_x = 0;
			player->gun_animation = SDL_FALSE;
		}	
	}
	tx_gun = SDL_CreateTextureFromSurface(rend, shoots[player->frame_gun_x]);
	SDL_RenderCopyEx(rend, tx_gun, &rect_gun_s, &rect_gun_d, 0, NULL, SDL_FLIP_NONE);
}
void init_pnt(t_pnt *p, float ma, float mi)
{
	p->ma = ma;
	p->mi = mi;
}

t_pnt movement(t_player *player)
{
	const uint8_t* keys;
	t_pnt p;

	keys = SDL_GetKeyboardState(NULL);
	init_pnt(&p, 0, 0);
	if (keys[SDL_SCANCODE_S])
    {
		p.ma -= cos(player->a);
        p.mi += sin(player->a);
	}
	if (keys[SDL_SCANCODE_W])
    {
		p.ma += cos(player->a);
        p.mi -= sin(player->a);
	}
	if (keys[SDL_SCANCODE_A])
    {
		p.ma += cos(player->a + PI/2.0f);
        p.mi -= sin(player->a + PI/2.0f);
	}
	if (keys[SDL_SCANCODE_D])
    {
		p.ma += cos(player->a - PI/2.0f);
        p.mi -= sin(player->a - PI/2.0f);
	}
	return (p);
}

void update(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	float dx;
	float dy;
	t_pnt p;
	
	p = movement(player);
	dx = p.ma;
	dy = p.mi;
	player->a = -range_conversion_val((t_pnt){W_W, 0}, (t_pnt){3*PI, -3*PI}, env->mouse_x);
	safe_angle(player->a);
	if (hit_sprites(player, ob_sprites, env) == SDL_TRUE)
		safe_map(player, dx, dy, env);
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

void enemy_movement(t_player *player, t_obj *ob_sprites)
{
	t_var_int vars;

	vars.ipx = (int)ob_sprites->x/cellS;
	vars.ipy = (int)ob_sprites->y/cellS;
	vars.ipx_add_x0 = ((int)ob_sprites->x + 15)/cellS;
	vars.ipy_add_y0 = ((int)ob_sprites->y + 15)/cellS;
	vars.ipx_sub_x0 = ((int)ob_sprites->x - 15)/cellS;
	vars.ipy_sub_y0 = ((int)ob_sprites->y - 15)/cellS;
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) > 10 
	&& distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 100 && ob_sprites->alive)
	{
		if (ob_sprites->x > player->x && map[vars.ipy*mapX+vars.ipx_sub_x0] == 0)
			ob_sprites->x-=0.7;
		if (ob_sprites->x < player->x && map[vars.ipy*mapX+vars.ipx_add_x0] == 0)
			ob_sprites->x+=0.7;
		if (ob_sprites->y > player->y && map[vars.ipy_sub_y0*mapX+vars.ipx] == 0)
			ob_sprites->y-=0.7;
		if (ob_sprites->y < player->y && map[vars.ipy_add_y0*mapX+vars.ipx] == 0)
			ob_sprites->y+=0.7;
	}
}

void enemy_animation(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	ob_sprites->fps--;
	if (ob_sprites->fps == 0)
	{
		ob_sprites->frame_num++;
		ob_sprites->fps = 2;
	}
	if (ob_sprites->frame_num > 16)
		ob_sprites->frame_num = 0;
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 50)
		Mix_Resume(3);
	else
		Mix_Pause(3);
	if (env->enemy_num == 0)
		Mix_Pause(3);
	if (!ob_sprites->alive)
	{
		if (ob_sprites->frame_num == 16)
			ob_sprites->state = 1;
	}
}

void player_damage_lose(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 11 && ob_sprites->alive)
	{
		player->damaged = SDL_TRUE;
		player->blood--;
		player->life = (SDL_Rect){40, W_H - 32, player->blood, 5};
		Mix_Resume(6);
	}
	else
	{
		Mix_Pause(6);
		player->damaged = SDL_FALSE;
	}
	//player lose
	if (player->blood < 0)
		env->screen = 5;
}

void coin_collect(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 15)
	{
		Mix_PlayChannel(1, env->coin_sound, 0);
		ob_sprites->state = 0;
		env->solde+=10;
	}
}

void aid_kit_collect(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 15)
	{
		Mix_PlayChannel(1, env->aid_kit_sound, 0);
		ob_sprites->state = 0;
		player->blood+=50;
		if (player->blood > W_W/4)
			player->blood = W_W/4;
		player->life = (SDL_Rect){40, W_H - 32, player->blood, 5};
	}
}

void update_sprites(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	int i;

	i = 0;
	while (i < env->num_sprites)
	{
		if (ob_sprites[i].state == 2)
		{
			enemy_movement(player, &ob_sprites[i]);
			enemy_animation(player, &ob_sprites[i], env);
			player_damage_lose(player, &ob_sprites[i], env);	
		}
		if (ob_sprites[i].state == 3)
			coin_collect(player,  &ob_sprites[i], env);
		if (ob_sprites[i].state == 4)
			aid_kit_collect(player, &ob_sprites[i], env);
		i++;
	}
	i = 0;
	while (i < env->num_sprites)
	{
		float dist = distance(player->x, player->y, ob_sprites[i].x, ob_sprites[i].y);
		ob_sprites[i].dist_to_player = dist;
		i++;
	}
	sort_sprites(ob_sprites, env->num_sprites);
}

void enemy_damage_die(t_player *player, t_obj *ob_sprites, t_envirenment *env, t_pnt p)
{
	if (player->is_shoot)
	{
		if (p.ma+(ob_sprites->w/10) <= W_W/2 && p.ma+ob_sprites->w-(ob_sprites->w/10) >= W_W/2
		&& W_H/2 + p.mi - ob_sprites->h <= env->mouse_y && W_H/2 + p.mi >= env->mouse_y
		&& ob_sprites->alive)
		{
			ob_sprites->frame_num = 3;
			if (ob_sprites->damage > 0)
				ob_sprites->damage--;
			if (ob_sprites->damage == 0)
			{
				env->enemy_num--;
				ob_sprites->size_x = 2;
				ob_sprites->alive = SDL_FALSE;
				ob_sprites->row = 1;
				ob_sprites->frame_num = 0;
			}
		}
	}
}
void sprite_in_vision(SDL_Renderer *rend, t_player *player, t_obj *ob_sprites, t_envirenment *env, float diff_angles)
{
	SDL_Rect rect0;
	SDL_Rect rect1;
	float sx;
	float on_floor;
	int j;

	ob_sprites->h = ((WALL_H * 220) / ob_sprites->dist_to_player)/ob_sprites->size_y;
	ob_sprites->w = ((WALL_H * 220) / ob_sprites->dist_to_player)/ob_sprites->size_x;
	sx = range_conversion_val((t_pnt){dtor(player->fov/2), -dtor(player->fov/2)}, (t_pnt){W_W , 0-ob_sprites->w}, diff_angles); //ob_sprites->size decalage pour sprite width
	on_floor = ((WALL_H * 220) / ob_sprites->dist_to_player) / 2;
	if (ob_sprites->state == 2)
		enemy_damage_die(player, ob_sprites, env, (t_pnt){sx, on_floor});
	j = (int)sx;
	while (j < (int)sx + ob_sprites->w)
	{
		if (ob_sprites->dist_to_player < player->dist[j])
		{
			rect0 = (SDL_Rect){ob_sprites->frame_width * ob_sprites->frame_num + ((float)ob_sprites->surface_w/ob_sprites->w * (j - (int)sx)), ob_sprites->frame_higth * ob_sprites->row, (float)ob_sprites->surface_w / ob_sprites->w, ob_sprites->frame_higth};
			rect1 = (SDL_Rect){j, W_H/2 + on_floor - ob_sprites->h, 1, ob_sprites->h};
			SDL_RenderCopyEx(rend, ob_sprites->texture, &rect0, &rect1, 0, NULL, SDL_FLIP_NONE);
		}
		j++;
	}
}

void draw_sprite(SDL_Renderer *rend, t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	int i;
	t_pnt p;
	float target_ang;
	float tmp_player_ang;
	float diff_angles;

	update_sprites(player, ob_sprites, env);
	i = 0;
	while (i < env->num_sprites)
	{
		if (ob_sprites[i].state != 0)
		{
			p.ma = ob_sprites[i].x - player->x;
			p.mi = ob_sprites[i].y - player->y;
			target_ang = fmodf((atan2(p.ma, p.mi)) + 2 * PI, 2 * PI) + PI / 2;
			target_ang = safe_angle(target_ang);
			tmp_player_ang = player->a + PI ;
			tmp_player_ang = safe_angle(tmp_player_ang);
			diff_angles = fmodf((tmp_player_ang - target_ang) + PI + 2 * PI,  2 * PI) - PI;
			diff_angles = safe_angle_180(diff_angles);
			if (diff_angles < PI / 6 && diff_angles > -PI / 6)
				sprite_in_vision(rend, player, &ob_sprites[i], env, diff_angles);
		}
		i++;
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
	if (t.num == 3)
		(t.img) = walls[1];
	if (t.num == 4)
		(t.img) = walls[2];
	if (t.num == 5)
		(t.img) = walls[3];
	if (t.num == 6)
		(t.img) = walls[4];
	if (t.num == 7)
		(t.img) = walls[5];
	if (t.num == 8)
		(t.img) = walls[6];
	if (t.num == 9)
		(t.img) = walls[7];
	if (t.num == 10)
		(t.img) = walls[8];
	if (t.num == 11)
		(t.img) = walls[9];
	if (t.num == 12)
		(t.img) = walls[10];
	if (t.num == 13)
		(t.img) = walls[11];
	if (t.num == 14)
		(t.img) = walls[12];
	if (t.num == 15)
		(t.img) = walls[13];
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
	float darkness = range_conversion_val((t_pnt){cellS*24, 0}, (t_pnt){0,1}, r.dist);
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
			int red;
			int green;
			int blue;
			red = rgb.r*r.shade*darkness;
			if (red > 255)
				red = 255;
			if (red < 0)
				red = 0;
			green = rgb.g*r.shade*darkness;
			if (green > 255)
				green = 255;
			if (green < 0)
				green = 0;
			blue = rgb.b*r.shade*darkness;
			if (blue > 255)
				blue = 255;
			if (blue < 0)
				blue = 0;
			SDL_SetRenderDrawColor(rend, red, green, blue, 255);
		}
		SDL_RenderFillRect(rend, &line);
		t.ty+=t.ty_step;
	}
	for (y = (W_H / 2) + (line_h / 2); y < W_H; y++)
	{
		darkness = range_conversion_val((t_pnt){W_H, (W_H / 2)}, (t_pnt){1,0}, y);
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
			SDL_SetRenderDrawColor(rend, rgb.r*darkness, rgb.g*darkness, rgb.b*darkness, 255);
		}
		SDL_RenderFillRect(rend, &line);
		// draw ceiling
		line.y = (W_H/2.0) - (y - (W_H/2.0)) - 1;
		SDL_SetRenderDrawColor(rend, 150, 150, 200, 255);
		if (env->texture && !env->skybox)
		{
			data = getpixel(ceil, (int)(t.tx)&(ceil->w-1), (int)(t.ty)&(ceil->w-1));
			SDL_GetRGB(data, ceil->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r*darkness, rgb.g*darkness, rgb.b*darkness, 255);
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


void render_map(SDL_Renderer *rend, t_player *player, t_obj *ob_sprites, t_envirenment *env)
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
	for (int s=0; s < env->num_sprites; s++)
	{
		if (ob_sprites[s].state == 2)
			draw_square(rend, 4, ob_sprites[s].x, ob_sprites[s].y);
	}

}

void	draw_sky(SDL_Renderer *rend, SDL_Surface *sky, t_player *player)
{
	int x, y, x0;

	for(x=0; x<1124; x++)
	{

		for(y=0; y<300; y++)
		{			
			x0 = (int)(player->a*3 / PI * 180.0f) - x;
			if (x0 < 0)
				x0+=1124;
			x0=x0%1124;
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
        render_map(rend, player, ob_sprites, env);
}

void            write_text(SDL_Renderer *rend, TTF_Font  *font, char *str, int x, int y)
{
	SDL_Color color = {200, 100, 0, 255};
	
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, str, color); 
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

	SDL_Surface *wall = IMG_Load("resources/images/walls/wall.png");
	SDL_Surface *wall_code = IMG_Load("resources/images/walls/wall_code.png");
	SDL_Surface *wall_key = IMG_Load("resources/images/walls/wall_key.png");
	SDL_Surface *wall_1 = IMG_Load("resources/images/walls/wall_1.png");
	SDL_Surface *wall_2 = IMG_Load("resources/images/walls/wall_2.png");
	SDL_Surface *wall_3 = IMG_Load("resources/images/walls/wall_3.png");
	SDL_Surface *wall_4 = IMG_Load("resources/images/walls/wall_4.png");
	SDL_Surface *wall_5 = IMG_Load("resources/images/walls/wall_5.png");
	SDL_Surface *wall_6 = IMG_Load("resources/images/walls/wall_6.png");
	SDL_Surface *wall_7 = IMG_Load("resources/images/walls/wall_7.png");
	SDL_Surface *wall_8 = IMG_Load("resources/images/walls/wall_8.png");
	SDL_Surface *wall_9 = IMG_Load("resources/images/walls/wall_9.png");
	SDL_Surface *wall_10 = IMG_Load("resources/images/walls/wall_10.png");
	SDL_Surface *wall_11 = IMG_Load("resources/images/walls/wall_11.png");

	SDL_Surface *door = IMG_Load("resources/images/doors/door1.png");
	SDL_Surface *door1 = IMG_Load("resources/images/doors/door1.png");
	SDL_Surface *door2 = IMG_Load("resources/images/doors/door2.png");
	SDL_Surface *door3 = IMG_Load("resources/images/doors/door3.png");
	SDL_Surface *door4 = IMG_Load("resources/images/doors/door4.png");
	SDL_Surface *door5 = IMG_Load("resources/images/doors/door5.png");
	SDL_Surface *door6 = IMG_Load("resources/images/doors/door6.png");

	SDL_Surface *floor = IMG_Load("resources/floor.png");
	SDL_Surface *ceil = IMG_Load("resources/ceil.png");
	SDL_Surface *sky = IMG_Load("resources/night_sky.png");

	SDL_Surface *sprite1 = IMG_Load("resources/images/sprites/pillar.png");
	SDL_Surface *sprite2 = IMG_Load("resources/images/sprites/trash.png");
	SDL_Surface *sprite3 = IMG_Load("resources/images/sprites/enemy.png");
	SDL_Surface *sprite4 = IMG_Load("resources/images/sprites/coin.png");
	SDL_Surface *sprite5 = IMG_Load("resources/images/sprites/table.png");
	SDL_Surface *sprite6 = IMG_Load("resources/images/sprites/aid_kit.png");
	SDL_Surface *sprite7 = IMG_Load("resources/images/sprites/barrel.png");

	
	
	SDL_Surface *shoot1 = IMG_Load("resources/images/shoot/shoot1.png");
	SDL_Surface *shoot2 = IMG_Load("resources/images/shoot/shoot2.png");
	SDL_Surface *shoot3 = IMG_Load("resources/images/shoot/shoot3.png");
	SDL_Surface *shoot4 = IMG_Load("resources/images/shoot/shoot4.png");
	SDL_Surface *shoot5 = IMG_Load("resources/images/shoot/shoot5.png");
	SDL_Surface *shoot6 = IMG_Load("resources/images/shoot/shoot6.png");
	SDL_Surface *shoot7 = IMG_Load("resources/images/shoot/shoot7.png");
	SDL_Surface *shoot8 = IMG_Load("resources/images/shoot/shoot8.png");
	SDL_Surface *shoot9 = IMG_Load("resources/images/shoot/shoot9.png");

	
   	SDL_Surface *welcom_sc;
   	SDL_Surface *wolf3d;
   	SDL_Surface *play;
	SDL_Surface *quit;
   	SDL_Surface *menu_icon;
   	SDL_Surface *icon;
   	SDL_Surface *menu_sc;
   	SDL_Surface *menu_btns;
   	int menu_btn_clicked = 0;
   	int previous_screen = 1;
   	SDL_Surface *options_pupop;
   	int options_pupop_showed = 0;
   	SDL_Surface *close_btn;
	SDL_Surface *rust_code_sc;
	SDL_Surface *back_btn;
	SDL_Surface *calculator;
	SDL_Surface *lose_sc;
	SDL_Surface *gun;
	SDL_Surface *aim;
	SDL_Surface *heart;
	SDL_Surface *damage_sc;


	double frame_sound = 0;
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

	SDL_Surface *walls[14];
	walls[0] = wall;
	walls[1] = wall_code;
	walls[2] = wall_1;
	walls[3] = wall_2;
	walls[4] = wall_3;
	walls[5] = wall_4;
	walls[6] = wall_5;
	walls[7] = wall_6;
	walls[8] = wall_7;
	walls[9] = wall_8;
	walls[10] = wall_9;
	walls[11] = wall_key;
	walls[12] = wall_10;
	walls[13] = wall_11;

	SDL_Surface *doors[6];
	doors[0] = door1;
	doors[1] = door2;
	doors[2] = door3;
	doors[3] = door4;
	doors[4] = door5;
	doors[5] = door6;

	SDL_Surface *shoots[9];
	shoots[0] = shoot1;
	shoots[1] = shoot2;
	shoots[2] = shoot3;
	shoots[3] = shoot4;
	shoots[4] = shoot5;
	shoots[5] = shoot6;
	shoots[6] = shoot7;
	shoots[7] = shoot8;
	shoots[8] = shoot9;
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
	if (sprite5 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite5.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}
	if (sprite6 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite6.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}
	if (sprite7 == NULL)
	{
    	printf("Failed to load image at 'resource/sprite7.png': %s\n", SDL_GetError());
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

	SDL_Texture *tx_sprite5;
	tx_sprite5 = SDL_CreateTextureFromSurface(rend, sprite5);
	if(tx_sprite5 == NULL)
	{
		SDL_FreeSurface(sprite5);
		printf("create tx_sprite5 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Texture *tx_sprite6;
	tx_sprite6 = SDL_CreateTextureFromSurface(rend, sprite6);
	if(tx_sprite6 == NULL)
	{
		SDL_FreeSurface(sprite6);
		printf("create tx_sprite6 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Texture *tx_sprite7;
	tx_sprite7 = SDL_CreateTextureFromSurface(rend, sprite7);
	if(tx_sprite7 == NULL)
	{
		SDL_FreeSurface(sprite7);
		printf("create tx_sprite7 Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

	SDL_Rect rect_icon_coin_s = (SDL_Rect){0,0,512,512};
	SDL_Rect rect_icon_coin_d;

	SDL_Texture *tx_sprites[7];
	tx_sprites[0] = tx_sprite1;
	tx_sprites[1] = tx_sprite2;
	tx_sprites[2] = tx_sprite3;
	tx_sprites[3] = tx_sprite4;
	tx_sprites[4] = tx_sprite5;
	tx_sprites[5] = tx_sprite6;
	tx_sprites[6] = tx_sprite7;
   	
   	icon = IMG_Load("resources/images/decoration/sound.png");
   	welcom_sc = IMG_Load("resources/images/decoration/welcom_sc.png");
   	wolf3d = IMG_Load("resources/images/decoration/wolf3d.png");
   	play = IMG_Load("resources/images/decoration/play.png");
	quit = IMG_Load("resources/images/decoration/quit.png");
   	menu_icon = IMG_Load("resources/images/decoration/menu_icon.png");
   	menu_sc = IMG_Load("resources/images/decoration/menu_sc.png");
   	menu_btns = IMG_Load("resources/images/decoration/menu_buttons.png");
   	options_pupop = IMG_Load("resources/images/decoration/options_pupop.png");
   	close_btn = IMG_Load("resources/images/decoration/close_btn.png");
	rust_code_sc = IMG_Load("resources/images/decoration/rust_code_sc.png");
	back_btn = IMG_Load("resources/images/decoration/back_btn.png");
	calculator = IMG_Load("resources/images/decoration/calculator.png");
	lose_sc = IMG_Load("resources/images/decoration/lose_sc.png");
	aim = IMG_Load("resources/images/decoration/aim.png");
	heart = IMG_Load("resources/images/decoration/heart.png");
	damage_sc = IMG_Load("resources/images/decoration/damage_sc.png");

   	if (!icon)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_sound_s;
   	SDL_Rect rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	SDL_Texture *tx_icon = SDL_CreateTextureFromSurface(rend, icon);
   	SDL_FreeSurface(icon);


   	if (!welcom_sc)
   	{
   	   printf("6%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_welcom_sc_s;
   	SDL_Rect rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_welcom_sc = SDL_CreateTextureFromSurface(rend, welcom_sc);
   	SDL_FreeSurface(welcom_sc);


   	if (!wolf3d)
   	{
   	   printf("7%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_wolf3d_s;
   	SDL_Rect rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   	SDL_Texture *tx_wolf3d = SDL_CreateTextureFromSurface(rend, wolf3d);
   	SDL_FreeSurface(wolf3d);


   	if (!play)
   	{
   	   printf("8%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_play_s;
   	SDL_Rect rect_play_d = (SDL_Rect){W_W/2-125, W_H/3, 250, 155};
   	SDL_Texture *tx_play = SDL_CreateTextureFromSurface(rend, play);
   	SDL_FreeSurface(play);

   	if (!quit)
   	{
   	   printf("8%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_quit_s;
   	SDL_Rect rect_quit_d = (SDL_Rect){W_W/2-125, W_H/3 + 200, 250, 155};
   	SDL_Texture *tx_quit = SDL_CreateTextureFromSurface(rend, quit);
   	SDL_FreeSurface(quit);

   	if (!menu_icon)
   	{
   	   printf("9%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_icon_s;
   	SDL_Rect rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
   	SDL_Texture *tx_menu_icon = SDL_CreateTextureFromSurface(rend, menu_icon);
   	SDL_FreeSurface(menu_icon);

   	if (!menu_sc)
   	{
   	   printf("10%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_sc_s;
   	SDL_Rect rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_menu_sc = SDL_CreateTextureFromSurface(rend, menu_sc);
   	SDL_FreeSurface(menu_sc);

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

   	if (!options_pupop)
   	{
   	   printf("12%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_options_pupop_s;
   	SDL_Rect rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   	SDL_Texture *tx_options_pupop = SDL_CreateTextureFromSurface(rend, options_pupop);
   	SDL_FreeSurface(options_pupop);

   	if (!close_btn)
   	{
   	   printf("13%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_close_btn_s;
   	SDL_Rect rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   	SDL_Texture *tx_close_btn = SDL_CreateTextureFromSurface(rend, close_btn);
   	SDL_FreeSurface(close_btn);


   	if (!rust_code_sc)
   	{
   	   printf("16%s", SDL_GetError());
   	   return (1);
   	}
   	SDL_Rect rect_rust_code_sc_s = (SDL_Rect){0, 0, 250, 250};
   	SDL_Rect rect_rust_code_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_rust_code_sc = SDL_CreateTextureFromSurface(rend, rust_code_sc);
   	SDL_FreeSurface(rust_code_sc);

   	if (!back_btn)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_back_btn_s;
   	SDL_Rect rect_back_btn_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	SDL_Texture *tx_back_btn = SDL_CreateTextureFromSurface(rend, back_btn);
   	SDL_FreeSurface(back_btn);

   	if (!calculator)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_calculator_s;
   	SDL_Rect rect_calculator_d = (SDL_Rect){W_W/2-90, 60, 200, 70};
   	SDL_Texture *tx_calculator = SDL_CreateTextureFromSurface(rend, calculator);
   	SDL_FreeSurface(calculator);

   	if (!lose_sc)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_lose_sc_s;
   	SDL_Rect rect_lose_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_lose_sc = SDL_CreateTextureFromSurface(rend, lose_sc);
   	SDL_FreeSurface(lose_sc);


   	SDL_Rect rect_gun_s;
   	SDL_Rect rect_gun_d = (SDL_Rect){W_W/2-250, W_H-280, 500, 280};
   	SDL_Texture *tx_gun;
   	SDL_FreeSurface(gun);

   	if (!aim)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}
	SDL_Rect rect_aim_s;
   	SDL_Rect rect_aim_d = (SDL_Rect){W_W/2-20, W_H/2+5, 40, 40};
   	SDL_Texture *tx_aim = SDL_CreateTextureFromSurface(rend, aim);
   	SDL_FreeSurface(aim);

   	if (!heart)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}
	SDL_Rect rect_heart_s;
   	SDL_Rect rect_heart_d = (SDL_Rect){10, W_H-50, 40, 40};
   	SDL_Texture *tx_heart = SDL_CreateTextureFromSurface(rend, heart);
   	SDL_FreeSurface(heart);
	
   	if (!damage_sc)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}
	SDL_Rect rect_damage_sc_s = (SDL_Rect){0, 0, 800, 600};
   	SDL_Rect rect_damage_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_damage_sc = SDL_CreateTextureFromSurface(rend, damage_sc);
   	SDL_FreeSurface(damage_sc);

   	Mix_Music *music;
   	music = Mix_LoadMUS("resources/sounds/music.wav");
   	Mix_PlayMusic(music, -1);

   	Mix_AllocateChannels(7);
 
   	env.foots_sound = Mix_LoadWAV("resources/sounds/footsteps.wav");
   	env.coin_sound = Mix_LoadWAV("resources/sounds/coin_sound.wav");
	env.bg_music = Mix_LoadWAV("resources/sounds/bg_music.wav");
	env.enemy_sound = Mix_LoadWAV("resources/sounds/enemy_sound.wav");
	env.gun_fire_sound = Mix_LoadWAV("resources/sounds/gun_fire_sound.wav");
	env.aid_kit_sound = Mix_LoadWAV("resources/sounds/aid_kit_sound.wav");
	env.pain_sound = Mix_LoadWAV("resources/sounds/pain_sound.wav");
   	Mix_VolumeChunk(env.foots_sound, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
   	Mix_VolumeChunk(env.coin_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env.bg_music, MIX_MAX_VOLUME/10);
	Mix_VolumeChunk(env.enemy_sound, MIX_MAX_VOLUME/4);
	Mix_VolumeChunk(env.gun_fire_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env.aid_kit_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env.pain_sound, MIX_MAX_VOLUME);

	
   	Mix_PlayChannel(0, env.foots_sound, -1);//Joue le son1 1 sur le canal 1 ; le joue une fois (0 + 1)
	Mix_PlayChannel(2, env.bg_music, -1);
	Mix_PlayChannel(3, env.enemy_sound, -1);
	Mix_PlayChannel(6, env.pain_sound, -1);
   	Mix_Pause(0);
	Mix_Pause(2);
	Mix_Pause(3);
	Mix_Pause(6);

	t_obj ob_sprites[env.num_sprites];
	sprites_reset(ob_sprites, tx_sprites);
	
	SDL_bool is_run = SDL_TRUE;
	
	SDL_Event e;
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
			{
				env.mouse_x = e.motion.x;
				env.mouse_y = e.motion.y;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (env.screen == 2)
				{
					//fire shoot
					player.gun_animation = SDL_TRUE;
					player.frame_gun_x = 0;
					player.is_shoot = SDL_TRUE;
					Mix_PlayChannel(1, env.gun_fire_sound, 0);
				}
            	if (sound_press(e.button) && env.screen == 2 && options_pupop_showed == 0)
            	{
            	   if(Mix_Paused(2) == 1) //Si la music est en pause
            	   {
            	      frame_sound = 0;
            	      Mix_Resume(2); //Reprendre la music
            	   }
            	   else
            	   {
            	      frame_sound = 1;
            	      Mix_Pause(2); //Mettre en pause la music
            	   }
            	}
				if (play_press(e.button) && env.screen == 1)
				{
					Mix_Resume(2);
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
					player_reset(&player);
					env_reset(&env);
					sprites_reset(ob_sprites, tx_sprites);
					env.screen = 1;
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
					Mix_Pause(0);
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					Mix_Pause(0);
				}
			}
		}
		SDL_RenderClear(rend);
		cursor_mouse(&env);
		if (env.screen == 1)
		{
			Mix_Pause(2);
			Mix_ResumeMusic();
		}
		else
			Mix_PauseMusic();
		if (env.screen == 1)
      	{
      	   	SDL_RenderClear(rend);
      	   	rect_welcom_sc_s = (SDL_Rect){0, 0, 1920, 1440};
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
			update(&player, ob_sprites, &env);
			render(rend, &player, walls, doors, floor, sky, ceil, ob_sprites, &env);
			show_door_code(&player, &env);
			if (env.code_valid)
				open_door(&player, &env);
      	   	rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   	rect_sound_s = (SDL_Rect){752 * frame_sound, 0, 752, 774};
			rect_icon_coin_d = (SDL_Rect){W_W/2-35,10,30,30};
			rect_gun_s = (SDL_Rect){0, 0, 1920, 1080};
      	   	rect_aim_s = (SDL_Rect){0, 0, 576, 576};
			rect_heart_s = (SDL_Rect){0, 0, 200, 200};
			SDL_RenderCopyEx(rend, tx_icon, &rect_sound_s, &rect_sound_d, 0, NULL, SDL_FLIP_NONE);
			gun_animation(rend, tx_gun, &player, shoots);
			rect_aim_d = (SDL_Rect){W_W/2-20, env.mouse_y, 40, 40};			
      	   	SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(rend, tx_sprite4, &rect_icon_coin_s, &rect_icon_coin_d, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(rend, tx_aim, &rect_aim_s, &rect_aim_d, 0, NULL, SDL_FLIP_NONE);
			SDL_SetRenderDrawColor(rend, 255,0,0,255);
			SDL_RenderFillRect(rend, &player.life);
			SDL_RenderCopyEx(rend, tx_heart, &rect_heart_s, &rect_heart_d, 0, NULL, SDL_FLIP_NONE);
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
			if (player.damaged)
				SDL_RenderCopyEx(rend, tx_damage_sc, &rect_damage_sc_s, &rect_damage_sc_d, 0, NULL, SDL_FLIP_NONE);
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
			Mix_Pause(3);
      	   	SDL_RenderClear(rend);
			rect_lose_sc_s = (SDL_Rect){0, 0, 1624, 892};
			SDL_RenderCopyEx(rend, tx_lose_sc, &rect_lose_sc_s, &rect_lose_sc_d, 0, NULL, SDL_FLIP_NONE);
			rect_icon_coin_d = (SDL_Rect){W_W/2-35,W_H/5,30,30};
			SDL_RenderCopyEx(rend, tx_sprite4, &rect_icon_coin_s, &rect_icon_coin_d, 0, NULL, SDL_FLIP_NONE);
			write_text(rend, font2, ft_strjoin("x ", ft_itoa(env.solde)), W_W/2, W_H/5);
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
      	   	SDL_RenderCopyEx(rend, tx_options_pupop, &rect_options_pupop_s, &rect_options_pupop_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_close_btn, &rect_close_btn_s, &rect_close_btn_d, 0, NULL, SDL_FLIP_NONE);
      	}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	Mix_FreeChunk(env.foots_sound);//Libération du son 1
   	Mix_FreeChunk(env.coin_sound);
	Mix_FreeMusic(music); //Libération de la music
	SDL_DestroyTexture(tx_icon);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}