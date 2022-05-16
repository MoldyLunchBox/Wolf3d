/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:00:30 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 19:00:33 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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