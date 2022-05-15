/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:16:49 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 19:16:51 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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