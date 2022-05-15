#include "wolf3d.h"




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
	obj->prev_state = vars_obj.prev_state;
	obj->texture = texture;
	obj->alive = SDL_TRUE;
	obj->fps = 2;
	obj->row = 0;
	obj->damage = 3;
	obj->dist_to_player = 15;
}

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
	1, 6, 3, 1, 7, 1, 1, 5, 1, 4, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	4, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 8, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1,
	1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1,
	5, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 5, 0, 0, 1, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
	8, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 3, 1, 0, 1, 1,
	1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	1, 1, 1, 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 7,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 4,
	1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	6, 0, 0, 0, 0, 0, 1, 3, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 9, 7, 5, 1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1,
	1, 1, 7, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 7, 4, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1,
};

void sprites_reset(t_obj *ob_sprites, SDL_Texture **tx_sprites, t_envirenment *env)
{
	int s;

	s = 0;
	while (s < env->num_sprites)
	{
		ob_sprites[s].id = s;
		s++;
	}
	//static
	init_obj(&ob_sprites[0], (t_vars_obj){12*cellS+10, 12*cellS+10, 820, 1694, 1, 2, 1, 0, 820, 1}, tx_sprites[0]);
	init_obj(&ob_sprites[1], (t_vars_obj){3*cellS+10, 2*cellS, 280, 270, 1, 3, 3, 0, 280, 1}, tx_sprites[1]);
	init_obj(&ob_sprites[2], (t_vars_obj){10*cellS+10, 7*cellS+10, 260, 310, 1, 3, 3, 0, 260, 1}, tx_sprites[6]);
	init_obj(&ob_sprites[3], (t_vars_obj){15*cellS+10, 7*cellS+10, 900, 900, 5, 2, 3, 0, 900, 5}, tx_sprites[7]);
	init_obj(&ob_sprites[4], (t_vars_obj){15*cellS+10, 7*cellS+10, 295, 400, 1, 3, 3, 0, 295, 1}, tx_sprites[4]);

	//enemy
	init_obj(&ob_sprites[5], (t_vars_obj){0*cellS, 0*cellS, 910, 1493, 2, 3, 2, 0, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[6], (t_vars_obj){16*cellS, 4*cellS, 910, 1493, 2, 3, 2, 3, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[7], (t_vars_obj){2*cellS, 15*cellS, 910, 1493, 2, 3, 2, 6, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[8], (t_vars_obj){3*cellS, 13*cellS, 910, 1493, 2, 3, 2, 8, 910, 2}, tx_sprites[2]);

	init_obj(&ob_sprites[9], (t_vars_obj){1*cellS+10, 19*cellS+10, 910, 1493, 2, 3, 2, 0, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[10], (t_vars_obj){8*cellS, 22*cellS+10, 910, 1493, 2, 3, 2, 3, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[11], (t_vars_obj){18*cellS, 20*cellS+10, 910, 1493, 2, 3, 2, 6, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[12], (t_vars_obj){22*cellS+10, 3*cellS+10, 910, 1493, 2, 3, 2, 8, 910, 2}, tx_sprites[2]);

	init_obj(&ob_sprites[13], (t_vars_obj){22*cellS+10, 7*cellS+10, 910, 1493, 2, 3, 2, 0, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[14], (t_vars_obj){13*cellS, 13*cellS+10, 910, 1493, 2, 3, 2, 3, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[15], (t_vars_obj){7*cellS+10, 1*cellS+10, 910, 1493, 2, 3, 2, 6, 910, 2}, tx_sprites[2]);
	init_obj(&ob_sprites[16], (t_vars_obj){10*cellS+10, 16*cellS+10, 910, 1493, 2, 3, 2, 8, 910, 2}, tx_sprites[2]);

	//aid_kit
	init_obj(&ob_sprites[17], (t_vars_obj){2*cellS+10, 22*cellS+10, 223, 200, 4, 4, 4, 0, 223, 4}, tx_sprites[5]);

	//coin
	init_obj(&ob_sprites[18], (t_vars_obj){9*cellS+10, 1*cellS+7, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[19], (t_vars_obj){9*cellS+20, 1*cellS+7, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[20], (t_vars_obj){9*cellS+30, 1*cellS+7, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[21], (t_vars_obj){9*cellS+40, 1*cellS+7, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[22], (t_vars_obj){9*cellS+10, 1*cellS+22, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[23], (t_vars_obj){9*cellS+20, 1*cellS+22, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[24], (t_vars_obj){9*cellS+30, 1*cellS+22, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[25], (t_vars_obj){9*cellS+40, 1*cellS+22, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[26], (t_vars_obj){9*cellS+10, 1*cellS+37, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[27], (t_vars_obj){9*cellS+20, 1*cellS+37, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[28], (t_vars_obj){9*cellS+30, 1*cellS+37, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[29], (t_vars_obj){9*cellS+40, 1*cellS+37, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[30], (t_vars_obj){9*cellS+10, 1*cellS+52, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[31], (t_vars_obj){9*cellS+20, 1*cellS+52, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[32], (t_vars_obj){9*cellS+30, 1*cellS+52, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);
	init_obj(&ob_sprites[33], (t_vars_obj){9*cellS+40, 1*cellS+52, 512, 512, 3, 5, 5, 0, 512, 3}, tx_sprites[3]);

	init_obj(&ob_sprites[34], (t_vars_obj){17*cellS+10, 11*cellS+10, 820, 1694, 1, 2, 1, 0, 820, 1}, tx_sprites[0]);
	init_obj(&ob_sprites[35], (t_vars_obj){17*cellS+10, 12*cellS+10, 820, 1694, 1, 2, 1, 0, 820, 1}, tx_sprites[0]);
	init_obj(&ob_sprites[36], (t_vars_obj){17*cellS+10, 13*cellS+10, 820, 1694, 1, 2, 1, 0, 820, 1}, tx_sprites[0]);
	init_obj(&ob_sprites[37], (t_vars_obj){17*cellS+10, 14*cellS+10, 820, 1694, 1, 2, 1, 0, 820, 1}, tx_sprites[0]);
}




void sound_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
   	{
      	if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50 && env->screen == 2 && env->options_pupop_showed == 0)
	  	{
			if(Mix_Paused(2) == 1)
      	 	{
      	 	   env->frame_sound = 0;
      	 	   Mix_Resume(2);
      	 	}
      	 	else
      	 	{
      	 	   env->frame_sound = 1;
      	 	   Mix_Pause(2);
      	 	}
	  	}
   }
}

void cursor_mouse(t_envirenment *env)
{
	if (env->screen == 2 && env->cursor)
	{
		// SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		// SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
	}
}
void play_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3 && b.y <= W_H/3 + 155 && env->screen == 1)
		{
			Mix_Resume(2);
			SDL_Rect r = (SDL_Rect){0,0,W_W,W_H};
    		env->screen = 2;
		}
   }
}
    	
void quit_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3+200 && b.y <= W_H/3+200+155 && env->screen == 1)
        {
			env->is_run = SDL_FALSE;
		}
   }
}

void menu_icon_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= 10 && b.x <= 60 && b.y >= 10 && b.y <= 60)
        {
			if (env->screen == 2 && env->options_pupop_showed == 0)
       			env->screen = 3;
			else if (env->screen == 3 && env->options_pupop_showed == 0)
				env->screen = 2;
		}
   }
}

void menu_buttons_press(SDL_MouseButtonEvent b, t_envirenment *env, t_player *player, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
   	if(b.button == SDL_BUTTON_LEFT)
   	{
      	if (b.x >= W_W/2-100 && b.x <= W_W/2+100 && env->screen == 3 && env->options_pupop_showed == 0)
      	{
        	if (b.y >= (W_H/6*0)+(12*1) && b.y <= (W_H/6*0)+(12*1) + W_H/6)
        	   env->screen = 1;
        	if (b.y >= (W_H/6*1)+(12*2) && b.y <= (W_H/6*1)+(12*2) + W_H/6)
        	   env->screen = 2;
        	if (b.y >= (W_H/6*2)+(12*3) && b.y <= (W_H/6*2)+(12*3) + W_H/6)
        	{
				sprites_reset(ob_sprites, tx_sprites, env);
			   	env_reset(env);
			   	player_reset(player);
			   	env->screen = 2;
    	   	}
        	if (b.y >= (W_H/6*3)+(12*4) && b.y <= (W_H/6*3)+(12*4) + W_H/6)
        	   env->options_pupop_showed = 1;
        	if (b.y >= (W_H/6*4)+(12*5) && b.y <= (W_H/6*4)+(12*5) + W_H/6)
            	env->is_run = SDL_FALSE;
      }
   }
}

void close_btn_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
   	{
   	   	if (b.x >= W_W - 55 && b.x <= W_W - 15 && b.y >= 15 && b.y <= 55 && env->options_pupop_showed == 1)
			env->options_pupop_showed = 0;
   	}
}

void back_btn_press(SDL_MouseButtonEvent b, t_envirenment *env, t_player *player)
{
   if(b.button == SDL_BUTTON_LEFT)
   {
    	if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50 && env->screen == 4)
        {
			env->len_code = 1;
			env->rust_code[1] = '\0';
			player_reset(player);
    		env->screen = 2;
		}
   }
}

void replay_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT && env->screen == 5)
		env_reset(env);
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

void    create_obj(t_obj *obj)
{
    obj = (t_obj*)malloc(sizeof(t_obj));
}


Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	if (x >= surface->w )
		x = surface->w -1;
	if (y >= surface->h  )
		y = surface->h -1;


    int bpp= surface->format->BytesPerPixel;
    Uint8 *p= (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; 

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
	else if (bpp == 4)
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

void enemy_collision(t_obj *enemy, t_obj *ob_sprites, t_envirenment *env)
{
	int s;

	s = 0;
	while (s < env->num_sprites)
	{
		if (enemy->id != ob_sprites[s].id && distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y) < 3)
		{
			if (enemy->x < ob_sprites[s].x && enemy->y < ob_sprites[s].y)
			{
				enemy->x-=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
				enemy->y-=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
			}
			if (enemy->x < ob_sprites[s].x && enemy->y > ob_sprites[s].y)
			{
				enemy->x-=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
				enemy->y+=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
			}
			if (enemy->x > ob_sprites[s].x && enemy->y < ob_sprites[s].y)
			{
				enemy->x+=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
				enemy->y-=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
			}
			if (enemy->x > ob_sprites[s].x && enemy->y > ob_sprites[s].y)
			{
				enemy->x+=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
				enemy->y+=(3-distance(enemy->x, enemy->y, ob_sprites[s].x, ob_sprites[s].y));
			}
		}
		s++;
	}
}

void hit_sprites(t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	int s;

	s = 0;

	while (s < env->num_sprites)
	{
		if ((ob_sprites[s].state == 1 || ob_sprites[s].state == 2) && ob_sprites[s].dist_to_player < 11)
		{
			if (player->x < ob_sprites[s].x && player->y < ob_sprites[s].y)
			{
				player->x-=(11-ob_sprites[s].dist_to_player);
				player->y-=(11-ob_sprites[s].dist_to_player);
			}
			if (player->x < ob_sprites[s].x && player->y > ob_sprites[s].y)
			{
				player->x-=(11-ob_sprites[s].dist_to_player);
				player->y+=(11-ob_sprites[s].dist_to_player);
			}
			if (player->x > ob_sprites[s].x && player->y < ob_sprites[s].y)
			{
				player->x+=(11-ob_sprites[s].dist_to_player);
				player->y-=(11-ob_sprites[s].dist_to_player);
			}
			if (player->x > ob_sprites[s].x && player->y > ob_sprites[s].y)
			{
				player->x+=(11-ob_sprites[s].dist_to_player);
				player->y+=(11-ob_sprites[s].dist_to_player);
			}
		}
		if (ob_sprites[s].prev_state == 5)
		{
			if (ob_sprites[s].dist_to_player < 11)
				ob_sprites[s].state = 0;
			else
				ob_sprites[s].state = ob_sprites[s].prev_state;
		} 
		s++;
	}
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
	if ((vars.ipy * env->map_size + vars.ipx_add_x0 != 0 && env->map[vars.ipy * env->map_size + vars.ipx_add_x0] == 0))
		player->x += pdx * player->speed;
	if ((vars.ipy_add_y0 * env->map_size + vars.ipx != 0 && env->map[vars.ipy_add_y0 * env->map_size + vars.ipx] == 0))
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
	if (env->map[vars.ipy_add_y0 * env->map_size + vars.ipx_add_x0] == 2 && env->code_valid == SDL_FALSE)
		env->screen = 4;
}

void open_door(t_envirenment *env)
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
		env->map[env->door_position] = 0;
	}
}

void quit_animation(t_envirenment *env)
{
	env->fps_quit--;
	if(env->fps_quit == 0)
	{
		env->frame_quit++;
		env->fps_quit = 2;
	}
	if (env->frame_quit == 3)
	{
		env->frame_quit = 0;
	}
}


void gun_animation(SDL_Renderer *rend, t_player *player, SDL_Surface **shoots)
{
	SDL_Texture *tx_gun;
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
	
		if (env->mouse_x == W_W-1)
			SDL_WarpMouseInWindow(env->window, 1, env->mouse_y);
		if (env->mouse_x == 0)
			SDL_WarpMouseInWindow(env->window, W_W-1, env->mouse_y);
		player->a = -range_conversion_val((t_pnt){W_W, 0}, (t_pnt){1*PI, -1*PI}, env->mouse_x);
	
	safe_angle(player->a);
	safe_map(player, dx, dy, env);
	hit_sprites(player, ob_sprites, env);
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

void enemy_movement(t_envirenment *env, t_player *player, t_obj *ob_sprites)
{
	t_var_int vars;

	vars.ipx = (int)ob_sprites->x/cellS;
	vars.ipy = (int)ob_sprites->y/cellS;
	vars.ipx_add_x0 = ((int)ob_sprites->x + 15)/cellS;
	vars.ipy_add_y0 = ((int)ob_sprites->y + 15)/cellS;
	vars.ipx_sub_x0 = ((int)ob_sprites->x - 15)/cellS;
	vars.ipy_sub_y0 = ((int)ob_sprites->y - 15)/cellS;
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) > 12 
	&& distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 100 && ob_sprites->alive)
	{
		printf("%d\n", ob_sprites->id);
		if (ob_sprites->x > player->x && env->map[vars.ipy*env->map_size+vars.ipx_sub_x0] == 0)
			ob_sprites->x-=0.7;
		if (ob_sprites->x < player->x && env->map[vars.ipy*env->map_size+vars.ipx_add_x0] == 0)
			ob_sprites->x+=0.7;
		if (ob_sprites->y > player->y && env->map[vars.ipy_sub_y0*env->map_size+vars.ipx] == 0)
			ob_sprites->y-=0.7;
		if (ob_sprites->y < player->y && env->map[vars.ipy_add_y0*env->map_size+vars.ipx] == 0)
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
	if (distance(player->x, player->y, ob_sprites->x, ob_sprites->y) < 12 && ob_sprites->alive)
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
			enemy_movement(env, player, &ob_sprites[i]);
			enemy_collision(&ob_sprites[i], ob_sprites, env);
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
	sx = range_conversion_val((t_pnt){dtor(player->fov/2), -dtor(player->fov/2)}, (t_pnt){W_W , -ob_sprites->w}, diff_angles);
	on_floor = ((WALL_H * 220) / ob_sprites->dist_to_player) / 2;
	if (ob_sprites->state == 5)
		on_floor *= -1;
	if (ob_sprites->state == 2)
		enemy_damage_die(player, ob_sprites, env, (t_pnt){sx, on_floor});
	j = (int)sx;
	while (j < (int)(sx + ob_sprites->w) && j < 800)
	{
		if (j > 800)
			printf("aaaaa");
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
void select_texture(t_texture *t, SDL_Surface **walls, SDL_Surface **quit, SDL_Surface **doors, t_envirenment *env)
{
	if (t->num == 1)
		(t->img) = walls[0];
	if (t->num == 2)
		(t->img) = doors[env->frame_door];
	if (t->num == 3)
		(t->img) = walls[1];
	if (t->num == 4)
		(t->img) = walls[2];
	if (t->num == 5)
		(t->img) = walls[3];
	if (t->num == 6)
		(t->img) = walls[4];
	if (t->num == 7)
		(t->img) = walls[5];
	if (t->num == 8)
		(t->img) = walls[6];
	if (t->num == 9)
		(t->img) = walls[7];
	if (t->num == 10)
		(t->img) = walls[8];
	if (t->num == 11)
		(t->img) = walls[9];
	if (t->num == 12)
		(t->img) = walls[10];
	if (t->num == 13)
		(t->img) = walls[11];
	if (t->num == 14)
		(t->img) = walls[12];
	if (t->num == 15)
		(t->img) = walls[13];
	if (t->num == 16)
		(t->img) = quit[env->frame_quit];
}

void color_fix(t_color *c)
{
	if (c->red > 255)
		c->red = 255;
	if (c->red < 0)
		c->red = 0;
	if (c->green > 255)
		c->green = 255;
	if (c->green < 0)
		c->green = 0;
	if (c->blue > 255)
		c->blue = 255;
	if (c->blue < 0)
		c->blue = 0;
}

void wall_with_texture(SDL_Renderer *rend, t_ray *r, t_texture *t)
{
	t_color c;
	float darkness;
	SDL_Color rgb;
	unsigned int data;

	darkness = range_conversion_val((t_pnt){cellS * 24, 0}, (t_pnt){0, 1}, r->dist);
	if (t->num == 2)
		r->shade = 1;
	data = getpixel((t->img), (int)(t->tx), (int)(t->ty));
	SDL_GetRGB(data, (t->img)->format, &rgb.r, &rgb.g, &rgb.b);
	c = (t_color){rgb.r * r->shade * darkness, rgb.g * r->shade * darkness, rgb.b * r->shade * darkness};
	color_fix(&c);
	SDL_SetRenderDrawColor(rend, c.red, c.green, c.blue, 255);
}

void rend_wall(SDL_Renderer *rend, t_ray *r, t_texture *t, double line_h, t_envirenment *env, SDL_Rect *line)
{
	int y;
	
	y = 0;
	while (y < line_h)
	{
		line->y = (W_H / 2) - (line_h / 2) + y;
		if (env->texture)
			wall_with_texture(rend, r, t);
		SDL_RenderFillRect(rend, line);
		t->ty += t->ty_step;
		y++;
	}
}

void rend_floor(SDL_Renderer *rend, t_ray *r, t_texture *t, t_envirenment *env, SDL_Rect *line, int y, t_player *player, SDL_Surface *floor)
{
	float darkness;
	float dy;
	float raFix;
	SDL_Color rgb;
	Uint32 data;

	darkness = range_conversion_val((t_pnt){W_H, (W_H / 2)}, (t_pnt){1, 0}, y);
	line->y = y;
	dy = y - (W_H / 2.0);
	r->ra = safe_angle(r->ra);
	raFix = cos(player->a - r->ra);
	t->tx = player->x * 28 + cos(r->ra) * 220 * floor->w / dy / raFix;
	t->ty = player->y * 28 - sin(r->ra) * 220 * floor->w / dy / raFix;
	SDL_SetRenderDrawColor(rend, 200, 100, 50, 255);
	if (env->texture)
	{
		data = getpixel(floor, (int)(t->tx)&(floor->w - 1), (int)(t->ty)&(floor->w - 1));
		SDL_GetRGB(data, floor->format, &rgb.r, &rgb.g, &rgb.b);
		SDL_SetRenderDrawColor(rend, rgb.r * darkness, rgb.g * darkness, rgb.b * darkness, 255);
	}
	SDL_RenderFillRect(rend, line);
}

void rend_ceil(SDL_Renderer *rend, t_ray *r, t_texture *t, t_envirenment *env, SDL_Rect *line, int y, t_player *player, SDL_Surface *ceil)
{
	float darkness;
	SDL_Color rgb;
	Uint32 data;

	darkness = range_conversion_val((t_pnt){W_H, (W_H / 2)}, (t_pnt){1, 0}, y);
	line->y = (W_H/2.0) - (y - (W_H/2.0)) - 1;
	SDL_SetRenderDrawColor(rend, 150, 150, 200, 255);
	if (env->texture && !env->skybox)
	{
		data = getpixel(ceil, (int)(t->tx)&(ceil->w - 1), (int)(t->ty)&(ceil->w - 1));
		SDL_GetRGB(data, ceil->format, &rgb.r, &rgb.g, &rgb.b);
		SDL_SetRenderDrawColor(rend, rgb.r * darkness, rgb.g * darkness, rgb.b * darkness, 255);
		SDL_RenderFillRect(rend, line);
	}
	if (!env->texture)
		SDL_RenderFillRect(rend, line);
}
void texture_cords(t_texture *t, t_ray *r, float *line_h)
{
	t->ty_step = (t->img)->w / (float)*line_h;
	t->ty_offset = 0;
	if (*line_h > W_H)
	{
		t->ty_offset = (*line_h - W_H) / 2.0;
		*line_h = W_H;
	}
	if (*line_h <= 0)
		*line_h = 1;
	
	t->ty = t->ty_offset * t->ty_step;	
	t->scaling=(float)(t->img)->w/cellS;
	if (r->shade == 1)
	{
		t->tx = (int)(r->rx*t->scaling)%(t->img)->w;
		if (r->ra > PI)
			t->tx=((t->img)->w-1)-t->tx;
	}
	else
	{
		t->tx = (int)(r->ry*t->scaling)%(t->img)->w;
		if (r->ra > PI/2 && r->ra < (3*PI)/2)
			t->tx=((t->img)->w-1)-t->tx;
	}
}

void render_view(SDL_Renderer *rend, t_player *player, t_ray r, t_texture t, SDL_Surface **walls, SDL_Surface **quit, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *ceil, t_envirenment *env)
{
	float line_h;
	SDL_Rect line;
	int y;

	line.w = W_W/numRays;
	line.x = r.num*line.w;
	line.h = 1;
	
	line_h = (WALL_H * 220) / r.dist; //220 how player far to screen
	select_texture(&t, walls, quit, doors, env);
	texture_cords(&t, &r, &line_h);
	rend_wall(rend, &r, &t, line_h, env, &line);
	y = (W_H / 2) + (line_h / 2);
	while (y < W_H)
	{
		rend_floor(rend, &r, &t, env, &line, y, player, floor);
		rend_ceil(rend, &r, &t, env, &line, y, player, ceil);
		y++;
	}
}

void horizontal_direction(t_ray *ray, t_rend_vars *v, t_player *player, t_envirenment *env)
{
	if (ray->ra != 0. && ray->ra != PI)
		{
			float aTan = 1/(tan(ray->ra));
			if (ray->ra < PI) //look up
			{
				ray->ry = (((int)(player->y) / cellS) * cellS - 0.0001);
				ray->rx = player->x - (ray->ry - player->y)*aTan;
				ray->yo = -(cellS);
				ray->xo = -ray->yo*aTan;
			}
			if (ray->ra > PI) //look down
			{
				ray->ry = (((int)(player->y) / cellS) * cellS) + cellS;
				ray->rx = player->x - (ray->ry - player->y)*aTan;
				ray->yo = cellS;
				ray->xo = -ray->yo*aTan;
			}
		}
		else //look rigth or left
		{
			ray->rx = player->x;
			ray->ry = player->y;
			v->dof = env->map_size;
		}
}

void horizontal_line(t_envirenment *env, t_ray *ray, t_texture *tex, t_rend_vars *v, t_player *player)
{
	v->dof = 0;
	ray->dist_h = 100000;
	ray->hx = player->x;
	ray->hy = player->y;
	horizontal_direction(ray, v, player, env);
	while (v->dof < env->map_size)
	{
		v->mx = (int)(ray->rx)/cellS;
		v->my = (int)(ray->ry)/cellS;
		v->mp = v->my*env->map_size + v->mx;
		if (v->mp > 0 && v->mp < env->map_size*env->map_size && env->map[v->mp] >= 1)
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->dist_h = distance(player->x, player->y, ray->hx, ray->hy);
			v->dof = env->map_size;
			tex->hmt=env->map[v->mp];
		}	
		else
		{
			ray->rx+=ray->xo;
			ray->ry+=ray->yo;
			v->dof+=1;
		}
	}
}

void vertical_direction(t_ray *ray, t_rend_vars *v, t_player *player, t_envirenment *env)
{
	float aTan;

	aTan = (tan(ray->ra));
	if (ray->ra > PI/2 && ray->ra < (3*PI)/2)
	{
		ray->rx = (((int)(player->x) / cellS) * cellS - 0.0001);
		ray->ry = player->y - (ray->rx - player->x)*aTan;
		ray->xo = -(cellS);
		ray->yo = -ray->xo*aTan;
	}
	if (ray->ra < PI/2 || ray->ra > (3*PI)/2)
	{
		ray->rx = (((int)(player->x) / cellS) * cellS) + cellS;
		ray->ry = player->y - (ray->rx - player->x)*aTan;
		ray->xo = cellS;
		ray->yo = -ray->xo*aTan;
	}
	if (ray->ra == 0. || ray->ra == PI)
	{
		ray->rx = player->x;
		ray->ry = player->y;
		v->dof = env->map_size;
	}
}
void vertical_line(t_envirenment *env, t_ray *ray, t_texture *tex, t_rend_vars *v, t_player *player)
{
	v->dof = 0;
	ray->dist_v = 100000;
	ray->vx = player->x;
	ray->vy = player->y;
	vertical_direction(ray, v, player, env);
	while (v->dof < env->map_size)
	{
		v->mx = (int)(ray->rx)/cellS;
		v->my = (int)(ray->ry)/cellS;
		v->mp = v->my*env->map_size + v->mx;
		if (v->mp > 0 && v->mp < env->map_size*env->map_size && env->map[v->mp] >= 1)
		{
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->dist_v = distance(player->x, player->y, ray->vx, ray->vy);
			v->dof = env->map_size;
			tex->vmt=env->map[v->mp];
		}	
		else
		{
			ray->rx+=ray->xo;
			ray->ry+=ray->yo;
			v->dof+=1;
		}
	}
}

void closer_line(SDL_Renderer *rend, t_ray *ray, t_texture *tex)
{
	if (ray->dist_v < ray->dist_h)
	{
		tex->num = tex->vmt;
		ray->shade = 0.5;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dist = ray->dist_v;
		if((ray->ra >= PI/2 && ray->ra <= (3*PI)/2))
			SDL_SetRenderDrawColor(rend, 0, 0, 150, 255);
		else
			SDL_SetRenderDrawColor(rend, 0, 150, 0, 255);
	}
	if (ray->dist_h < ray->dist_v)
	{
		tex->num = tex->hmt;
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->dist = ray->dist_h;
		if (ray->ra <= PI)
			SDL_SetRenderDrawColor(rend, 200, 0, 200, 255);
		else
			SDL_SetRenderDrawColor(rend, 200, 200, 0, 255);
	}
}

void render_rays(SDL_Renderer *rend, t_player *player, SDL_Surface **walls, SDL_Surface **quit, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *ceil, t_envirenment *env)
{
	t_rend_vars v;
	t_ray ray;
	t_texture tex;
	
	tex.vmt = 0;
	tex.hmt = 0;
	tex.img = walls[0];
	ray.ra = player->a + dtor(player->fov / 2);
	ray.num = 0;
	while (ray.num < numRays)
	{
		ray.ra = safe_angle(ray.ra);
		horizontal_line(env, &ray, &tex, &v, player);
		vertical_line(env, &ray, &tex, &v, player);
		ray.shade = 1;
		closer_line(rend, &ray, &tex);
		ray.ca = safe_angle(player->a - ray.ra);
		ray.dist *=cos(ray.ca); 
		player->dist[ray.num] = ray.dist;
		render_view(rend, player, ray, tex, walls, quit, doors, floor, ceil, env);
		ray.ra-=dtor(player->fov / W_W);
		ray.ra = safe_angle(ray.ra);
		ray.num++;
	}
}

void draw_map_scene(t_envirenment *env, SDL_Renderer *rend)
{
	t_var_int v;

	v.y0 = -1;
	while (++v.y0 < env->map_size)
	{
		v.x0 = -1;
		while (++v.x0 < env->map_size)
		{
			v.ipy = v.y0 * cellS - 1;
			while (++v.ipy < v.y0 * cellS + cellS)
			{
				v.ipx = v.x0 * cellS - 1;
				while (++v.ipx < v.x0 * cellS + cellS)
				{
					if (env->map[v.y0 * env->map_size + v.x0] >= 1)
						SDL_SetRenderDrawColor(rend, 150, 150, 150, 255);
					else
						SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
					SDL_RenderDrawPoint(rend, v.ipx, v.ipy);
				}
			}
		}
	}
}

void render_map(SDL_Renderer *rend, t_player *player, t_obj *ob_sprites, t_envirenment *env)
{
	int s;

	draw_map_scene(env, rend);
	draw_player(player, rend);
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	s = 0;

	if (env->map_size == 24)
		while (s < env->num_sprites)
		{
			if (ob_sprites[s].state != 0)
				draw_square(rend, 4, ob_sprites[s].x, ob_sprites[s].y);
			s++;
		}
}

void	draw_sky(SDL_Renderer *rend, SDL_Surface *sky, t_player *player)
{
	int x;
	int y;
	int x0;
	SDL_Color rgb;
	Uint32 data;

	x = 0;
	while (x < W_W)
	{
		y = 0;
		while (y < W_H/2)
		{			
			x0 = (int)(player->a * 3 / PI * 180.0f) - x;
			if (x0 < 0)
				x0 += W_W;
			x0 = x0 % W_W;
			data = getpixel(sky, x0, y);
			SDL_GetRGB(data, sky->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
			SDL_RenderDrawPoint(rend, x, y);
			y++;
		}
		x++;
	}
}

void render(SDL_Renderer *rend, t_player *player, SDL_Surface **walls, SDL_Surface **quit, SDL_Surface **doors, SDL_Surface *floor, SDL_Surface *sky, SDL_Surface *ceil, t_obj *ob_sprites, t_envirenment *env)
{
	if (env->skybox)
		draw_sky(rend, sky, player);
    render_rays(rend, player, walls, quit, doors, floor, ceil, env);
	if (env->map_size == 24)
		draw_sprite(rend, player, ob_sprites, env);
    if (env->minimap)
        render_map(rend, player, ob_sprites, env);
}

void write_text(SDL_Renderer *rend, TTF_Font *font, char *str, int x, int y)
{
	SDL_Color color;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Rect Message_rect;

	color = (SDL_Color){200, 100, 0, 255};
	surfaceMessage = TTF_RenderText_Blended(font, str, color); 
	Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;
	SDL_RenderCopy(rend, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}


void load_sprites_tex(t_envirenment *env, SDL_Texture **tx_sprites)
{
	tx_sprites[0] = SDL_CreateTextureFromSurface(env->rend, env->sprites[0]);
	tx_sprites[1] = SDL_CreateTextureFromSurface(env->rend, env->sprites[1]);
	tx_sprites[2] = SDL_CreateTextureFromSurface(env->rend, env->sprites[2]);
	tx_sprites[3] = SDL_CreateTextureFromSurface(env->rend, env->sprites[3]);
	tx_sprites[4] = SDL_CreateTextureFromSurface(env->rend, env->sprites[4]);
	tx_sprites[5] = SDL_CreateTextureFromSurface(env->rend, env->sprites[5]);
	tx_sprites[6] = SDL_CreateTextureFromSurface(env->rend, env->sprites[6]);
	tx_sprites[7] = SDL_CreateTextureFromSurface(env->rend, env->sprites[7]);
}

void load_decoration(t_decoration_surface *s)
{
	s->icon = IMG_Load("resources/images/decoration/sound.png");
   	s->welcom_sc = IMG_Load("resources/images/decoration/welcom_sc.png");
   	s->wolf3d = IMG_Load("resources/images/decoration/wolf3d.png");
   	s->play = IMG_Load("resources/images/decoration/play.png");
	s->quit = IMG_Load("resources/images/decoration/quit.png");
   	s->menu_icon = IMG_Load("resources/images/decoration/menu_icon.png");
   	s->menu_sc = IMG_Load("resources/images/decoration/menu_sc.png");
   	s->menu_btns = IMG_Load("resources/images/decoration/menu_buttons.png");
   	s->options_pupop = IMG_Load("resources/images/decoration/options_pupop.png");
   	s->close_btn = IMG_Load("resources/images/decoration/close_btn.png");
	s->rust_code_sc = IMG_Load("resources/images/decoration/rust_code_sc.png");
	s->back_btn = IMG_Load("resources/images/decoration/back_btn.png");
	s->calculator = IMG_Load("resources/images/decoration/calculator.png");
	s->lose_sc = IMG_Load("resources/images/decoration/lose_sc.png");
	s->coin = IMG_Load("resources/images/sprites/coin.png");
	s->aim = IMG_Load("resources/images/decoration/aim.png");
	s->heart = IMG_Load("resources/images/decoration/heart.png");
	s->damage_sc = IMG_Load("resources/images/decoration/damage_sc.png");
}

void create_decoration_texture(t_envirenment *env, t_decoration_texture *t, t_decoration_surface s)
{
	t->tx_icon_coin = SDL_CreateTextureFromSurface(env->rend, s.coin);
   	t->tx_icon = SDL_CreateTextureFromSurface(env->rend, s.icon);
   	t->tx_welcom_sc = SDL_CreateTextureFromSurface(env->rend, s.welcom_sc);
   	t->tx_wolf3d = SDL_CreateTextureFromSurface(env->rend, s.wolf3d);
   	t->tx_play = SDL_CreateTextureFromSurface(env->rend, s.play);
   	t->tx_quit = SDL_CreateTextureFromSurface(env->rend, s.quit);
   	t->tx_menu_icon = SDL_CreateTextureFromSurface(env->rend, s.menu_icon);
   	t->tx_aim = SDL_CreateTextureFromSurface(env->rend, s.aim);
   	t->tx_heart = SDL_CreateTextureFromSurface(env->rend, s.heart);
   	t->tx_menu_sc = SDL_CreateTextureFromSurface(env->rend, s.menu_sc);
   	t->tx_menu_btns = SDL_CreateTextureFromSurface(env->rend, s.menu_btns);
   	t->tx_options_pupop = SDL_CreateTextureFromSurface(env->rend, s.options_pupop);
   	t->tx_close_btn = SDL_CreateTextureFromSurface(env->rend, s.close_btn);
   	t->tx_rust_code_sc = SDL_CreateTextureFromSurface(env->rend, s.rust_code_sc);
   	t->tx_back_btn = SDL_CreateTextureFromSurface(env->rend, s.back_btn);
   	t->tx_calculator = SDL_CreateTextureFromSurface(env->rend, s.calculator);
   	t->tx_lose_sc = SDL_CreateTextureFromSurface(env->rend, s.lose_sc);
   	t->tx_damage_sc = SDL_CreateTextureFromSurface(env->rend, s.damage_sc);
	env->floor = IMG_Load("resources/floor_derty.png");
	env->ceil = IMG_Load("resources/ceil.png");
	env->sky = IMG_Load("resources/night_sky.png");
}

void init_rect_decoration(t_rect_decoration *rd)
{
	rd->rect_icon_coin_s = (SDL_Rect){0,0,512,512};
   	rd->rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	rd->rect_welcom_sc_s = (SDL_Rect){0, 0, 1920, 1440};
   	rd->rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_wolf3d_s = (SDL_Rect){0, 0, 867, 364};
   	rd->rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   	rd->rect_play_s = (SDL_Rect){0, 0, 250, 155};
   	rd->rect_play_d = (SDL_Rect){W_W/2-125, W_H/3, 250, 155};
   	rd->rect_quit_s = (SDL_Rect){0, 0, 250, 155};
   	rd->rect_quit_d = (SDL_Rect){W_W/2-125, W_H/3 + 200, 250, 155};
   	rd->rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
   	rd->rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
	rd->rect_aim_s = (SDL_Rect){0, 0, 576, 576};
   	rd->rect_aim_d = (SDL_Rect){W_W/2-20, W_H/2+5, 40, 40};
	rd->rect_heart_s = (SDL_Rect){0, 0, 200, 200};
   	rd->rect_heart_d = (SDL_Rect){10, W_H-50, 40, 40};
   	rd->rect_menu_sc_s = (SDL_Rect){0, 0, 800, 600};
   	rd->rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_menu_btns_home_s = (SDL_Rect){0, 0, 281, 137};
   	rd->rect_menu_btns_home_d = (SDL_Rect){W_W/2 - 100, (W_H/6*0)+(12*1), 200, W_H/6};
   	rd->rect_menu_btns_resume_s = (SDL_Rect){0, 1*137, 281, 137};
   	rd->rect_menu_btns_resume_d = (SDL_Rect){W_W/2 - 100, (W_H/6*1)+(12*2), 200, W_H/6};
   	rd->rect_menu_btns_restart_s = (SDL_Rect){0, 2*137, 281, 137};
   	rd->rect_menu_btns_restart_d = (SDL_Rect){W_W/2 - 100, (W_H/6*2)+(12*3), 200, W_H/6};
   	rd->rect_menu_btns_options_s = (SDL_Rect){0, 3*137, 281, 137};
   	rd->rect_menu_btns_options_d = (SDL_Rect){W_W/2 - 100, (W_H/6*3)+(12*4), 200, W_H/6};
   	rd->rect_menu_btns_exit_s = (SDL_Rect){0, 4*137, 281, 137};
   	rd->rect_menu_btns_exit_d = (SDL_Rect){W_W/2 - 100, (W_H/6*4)+(12*5), 200, W_H/6};
   	rd->rect_options_pupop_s = (SDL_Rect){0, 0, 771, 638};
   	rd->rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   	rd->rect_close_btn_s = (SDL_Rect){0, 0, 300, 300};
   	rd->rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   	rd->rect_rust_code_sc_s = (SDL_Rect){0, 0, 250, 250};
   	rd->rect_rust_code_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_back_btn_s = (SDL_Rect){0, 0, 120, 120};
   	rd->rect_back_btn_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	rd->rect_calculator_s = (SDL_Rect){0, 0, 150, 46};
   	rd->rect_calculator_d = (SDL_Rect){W_W/2-90, 60, 200, 70};
   	rd->rect_lose_sc_s = (SDL_Rect){0, 0, 1624, 892};
   	rd->rect_lose_sc_d = (SDL_Rect){0, 0, W_W, W_H};
	rd->rect_damage_sc_s = (SDL_Rect){0, 0, 800, 600};
   	rd->rect_damage_sc_d = (SDL_Rect){0, 0, W_W, W_H};
	rd->life_border = (SDL_Rect){38, W_H - 34, W_W/4 + 4, 9};
}

void init_sound_effect(t_envirenment *env)
{
	env->music = Mix_LoadMUS("resources/sounds/music.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME/4);
   	Mix_AllocateChannels(7);
   	env->foots_sound = Mix_LoadWAV("resources/sounds/footsteps.wav");
   	env->coin_sound = Mix_LoadWAV("resources/sounds/coin_sound.wav");
	env->bg_music = Mix_LoadWAV("resources/sounds/bg_music.wav");
	env->enemy_sound = Mix_LoadWAV("resources/sounds/enemy_sound.wav");
	env->gun_fire_sound = Mix_LoadWAV("resources/sounds/gun_fire_sound.wav");
	env->aid_kit_sound = Mix_LoadWAV("resources/sounds/aid_kit_sound.wav");
	env->pain_sound = Mix_LoadWAV("resources/sounds/pain_sound.wav");
   	Mix_VolumeChunk(env->foots_sound, MIX_MAX_VOLUME);
   	Mix_VolumeChunk(env->coin_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env->bg_music, MIX_MAX_VOLUME/10);
	Mix_VolumeChunk(env->enemy_sound, MIX_MAX_VOLUME/4);
	Mix_VolumeChunk(env->gun_fire_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env->aid_kit_sound, MIX_MAX_VOLUME);
	Mix_VolumeChunk(env->pain_sound, MIX_MAX_VOLUME);
	Mix_PlayMusic(env->music, -1);
   	Mix_PlayChannel(0, env->foots_sound, -1);
	Mix_PlayChannel(2, env->bg_music, -1);
	Mix_PlayChannel(3, env->enemy_sound, -1);
	Mix_PlayChannel(6, env->pain_sound, -1);
   	Mix_Pause(0);
	Mix_Pause(2);
	Mix_Pause(3);
	Mix_Pause(6);
}

void	mouse_event(t_envirenment *env, t_player *player, SDL_Event e, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (env->screen == 2)
	{
		//fire shoot
		player->gun_animation = SDL_TRUE;
		player->frame_gun_x = 0;
		player->is_shoot = SDL_TRUE;
		Mix_PlayChannel(1, env->gun_fire_sound, 0);
	}
    sound_press(e.button, env);
	play_press(e.button, env);
	quit_press(e.button, env); 
    menu_icon_press(e.button, env);
    close_btn_press(e.button, env);
    menu_buttons_press(e.button, env, player, ob_sprites, tx_sprites);
	back_btn_press(e.button, env, player);
	replay_press(e.button, env);
}

void	key_down_event(t_envirenment *env,  SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
		env->is_run = SDL_FALSE;
	if (e.key.keysym.sym == SDLK_m)
		env->minimap = !env->minimap;
	if (e.key.keysym.sym == SDLK_t)
		env->texture = !env->texture;
	if (e.key.keysym.sym == SDLK_k)
		env->skybox = !env->skybox;
	if (e.key.keysym.sym == SDLK_BACKSPACE && env->screen == 4)
	{
		if (env->len_code > 1)
		{
			env->rust_code[env->len_code - 1] = '\0';
			env->len_code--;
		}
	}
	if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
      	Mix_Resume(0);
	if (e.key.keysym.sym == SDLK_p)
		env->cursor = !env->cursor;
}

void in_screen_1(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd)
{
	if (env->screen == 1)
    {
		Mix_Pause(2);
		Mix_ResumeMusic();
       	SDL_RenderCopy(env->rend, t->tx_welcom_sc, &rd->rect_welcom_sc_s, &rd->rect_welcom_sc_d);
       	SDL_RenderCopy(env->rend, t->tx_wolf3d, &rd->rect_wolf3d_s, &rd->rect_wolf3d_d);
       	SDL_RenderCopy(env->rend, t->tx_play, &rd->rect_play_s, &rd->rect_play_d);
		SDL_RenderCopy(env->rend, t->tx_quit, &rd->rect_quit_s, &rd->rect_quit_d);
    }
	else
		Mix_PauseMusic();
}

void fadding(t_envirenment *env)
{
	SDL_Rect r;

	if (env->fade > 0)
	{
		SDL_SetRenderDrawBlendMode(env->rend, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(env->rend, 0, 0 ,0, env->fade);
		r = (SDL_Rect){0, 0, W_W, W_H};
		SDL_RenderFillRect(env->rend, &r);
		env->fade -= 10;
	}
}

void in_screen_2(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd, t_obj *ob_sprites, t_player *player)
{
	if (env->screen == 2)
    {
		update(player, ob_sprites, env);
		render(env->rend, player, env->walls, env->quit, env->doors, env->floor, env->sky, env->ceil, ob_sprites, env);
		gun_animation(env->rend, player, env->shoots);
		show_door_code(player, env);
		if (env->code_valid)
			open_door(env);
		quit_animation(env);
       	rd->rect_sound_s = (SDL_Rect){752 * env->frame_sound, 0, 752, 774};
		rd->rect_icon_coin_d = (SDL_Rect){W_W/2-35,10,30,30};
		rd->rect_aim_d = (SDL_Rect){W_W/2-20, env->mouse_y, 40, 40};			
		SDL_RenderCopy(env->rend, t->tx_icon, &rd->rect_sound_s, &rd->rect_sound_d);
       	SDL_RenderCopy(env->rend, t->tx_menu_icon, &rd->rect_menu_icon_s, &rd->rect_menu_icon_d);
		SDL_RenderCopy(env->rend, t->tx_icon_coin, &rd->rect_icon_coin_s, &rd->rect_icon_coin_d);
		SDL_RenderCopy(env->rend, t->tx_aim, &rd->rect_aim_s, &rd->rect_aim_d);
		SDL_SetRenderDrawColor(env->rend, 255,255,255,255);
		SDL_RenderFillRect(env->rend, &rd->life_border);
		SDL_SetRenderDrawColor(env->rend, 255,0,0,255);
		SDL_RenderFillRect(env->rend, &player->life);
		SDL_RenderCopy(env->rend, t->tx_heart, &rd->rect_heart_s, &rd->rect_heart_d);
		write_text(env->rend, env->font2, ft_strjoin("x ", ft_itoa(env->solde)), W_W/2, 10);
		fadding(env);
		if (player->damaged)
			SDL_RenderCopy(env->rend, t->tx_damage_sc, &rd->rect_damage_sc_s, &rd->rect_damage_sc_d);
	}
}

void in_screen_3_4(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd)
{
	if (env->screen == 3)
    {
       SDL_RenderClear(env->rend);
       SDL_RenderCopy(env->rend, t->tx_menu_sc, &rd->rect_menu_sc_s, &rd->rect_menu_sc_d);
       SDL_RenderCopy(env->rend, t->tx_menu_icon, &rd->rect_menu_icon_s, &rd->rect_menu_icon_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_home_s, &rd->rect_menu_btns_home_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_resume_s, &rd->rect_menu_btns_resume_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_restart_s, &rd->rect_menu_btns_restart_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_options_s, &rd->rect_menu_btns_options_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_exit_s, &rd->rect_menu_btns_exit_d);
    }
	if (env->screen == 4)
    {
       	SDL_RenderClear(env->rend);
       	SDL_RenderCopy(env->rend, t->tx_rust_code_sc, &rd->rect_rust_code_sc_s, &rd->rect_rust_code_sc_d);
       	SDL_RenderCopy(env->rend, t->tx_back_btn, &rd->rect_back_btn_s, &rd->rect_back_btn_d);
		SDL_RenderCopy(env->rend, t->tx_calculator, &rd->rect_calculator_s, &rd->rect_calculator_d);
		write_text(env->rend, env->font1, env->rust_code, W_W/2-90, 75);
    }
	if (strcmp(env->rust_code, " 1337") == 0 && env->screen == 4)
	{
		env->code_valid = SDL_TRUE;
		env->screen = 2;
	}
}

void in_screen_5(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd, t_player *player, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (env->screen == 5)
    {
		Mix_Pause(3);
		Mix_Pause(6);
       	SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, t->tx_lose_sc, &rd->rect_lose_sc_s, &rd->rect_lose_sc_d);
		rd->rect_icon_coin_d = (SDL_Rect){W_W/2-35,W_H/5,30,30};
		SDL_RenderCopy(env->rend, t->tx_icon_coin, &rd->rect_icon_coin_s, &rd->rect_icon_coin_d);
		write_text(env->rend, env->font2, ft_strjoin("x ", ft_itoa(env->solde)), W_W/2, W_H/5);
		player_reset(player);
		sprites_reset(ob_sprites, tx_sprites, env);
    }
	if (env->options_pupop_showed == 1)
    {
       	SDL_RenderCopy(env->rend, t->tx_options_pupop, &rd->rect_options_pupop_s, &rd->rect_options_pupop_d);
       	SDL_RenderCopy(env->rend, t->tx_close_btn, &rd->rect_close_btn_s, &rd->rect_close_btn_d);
    }
}

void event(SDL_Event e, t_envirenment *env, t_player *player, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (e.type == SDL_QUIT)
		env->is_run = SDL_FALSE;
	if (e.type == SDL_TEXTINPUT && env->screen == 4 && env->len_code < 5)
	{
		 strcat(env->rust_code, e.text.text);
		 env->len_code++;
	}
	if (e.type == SDL_MOUSEMOTION)
	{
		env->mouse_x = e.motion.x;
		env->mouse_y = e.motion.y;
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
		mouse_event(env, player, e, ob_sprites, tx_sprites);
	if (e.type == SDL_KEYDOWN)
		key_down_event(env, e);
	if (e.type == SDL_KEYUP)
		if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
			Mix_Pause(0);
}





int main(int argc, char *argv[])
{
	t_envirenment env;
	t_player player;
	parsing(&env, argv[1]);
	init_game(&env, &player);
	load_walls(&env);
	load_doors(&env);
	
	load_shoots(&env);
	load_sprites(&env);
	SDL_Texture *tx_sprites[num_type_sprites];
	load_sprites_tex(&env, tx_sprites);
	t_decoration_surface s;
	load_decoration(&s);
	t_decoration_texture t;
	create_decoration_texture(&env, &t, s);
	t_rect_decoration rd;
	init_rect_decoration(&rd);
   	init_sound_effect(&env);
	t_obj ob_sprites[env.num_sprites];
	sprites_reset(ob_sprites, tx_sprites, &env);
	SDL_Event e;
	while (env.is_run)
	{
		while (SDL_PollEvent(&e))
			event(e, &env, &player, ob_sprites, tx_sprites);
		SDL_RenderClear(env.rend);
		cursor_mouse(&env);
		in_screen_1(&env, &t, &rd);
		in_screen_2(&env, &t, &rd, ob_sprites, &player);
		in_screen_3_4(&env, &t, &rd);
		in_screen_5(&env, &t, &rd, &player, ob_sprites, tx_sprites);
		SDL_RenderPresent(env.rend);
	}
	Mix_FreeChunk(env.foots_sound);
   	Mix_FreeChunk(env.coin_sound);
	Mix_FreeMusic(env.music);
	SDL_DestroyRenderer(env.rend);
	SDL_DestroyWindow(env.window);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}