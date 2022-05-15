/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:51:01 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:51:03 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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