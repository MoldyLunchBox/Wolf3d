/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:19:52 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 19:19:53 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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