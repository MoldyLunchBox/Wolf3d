/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:39:02 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:39:06 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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