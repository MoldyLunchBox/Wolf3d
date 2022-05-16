/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:05:19 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/16 10:05:21 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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