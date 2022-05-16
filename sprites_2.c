/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:08:28 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/16 10:08:30 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
