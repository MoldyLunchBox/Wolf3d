/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:54:35 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/16 09:54:37 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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