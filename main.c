#include "wolf3d.h"






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