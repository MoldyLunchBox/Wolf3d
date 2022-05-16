/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:51:55 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/16 09:51:56 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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