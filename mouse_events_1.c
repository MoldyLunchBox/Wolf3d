/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:35:37 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:35:47 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void sound_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
   	{
      	if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50 && env->screen == 2 && env->options_pupop_showed == 0)
	  	{
			if(Mix_Paused(2) == 1)
      	 	{
      	 	   env->frame_sound = 0;
      	 	   Mix_Resume(2);
      	 	}
      	 	else
      	 	{
      	 	   env->frame_sound = 1;
      	 	   Mix_Pause(2);
      	 	}
	  	}
   }
}

void play_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3 && b.y <= W_H/3 + 155 && env->screen == 1)
		{
			Mix_Resume(2);
			SDL_Rect r = (SDL_Rect){0,0,W_W,W_H};
    		env->screen = 2;
		}
   }
}

void quit_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= W_W/2-125 && b.x <= W_W/2+125 && b.y >= W_H/3+200 && b.y <= W_H/3+200+155 && env->screen == 1)
        {
			env->is_run = SDL_FALSE;
		}
   }
}

void menu_icon_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
	{
    	if (b.x >= 10 && b.x <= 60 && b.y >= 10 && b.y <= 60)
        {
			if (env->screen == 2 && env->options_pupop_showed == 0)
       			env->screen = 3;
			else if (env->screen == 3 && env->options_pupop_showed == 0)
				env->screen = 2;
		}
   }
}

void close_btn_press(SDL_MouseButtonEvent b, t_envirenment *env)
{
   	if(b.button == SDL_BUTTON_LEFT)
   	{
   	   	if (b.x >= W_W - 55 && b.x <= W_W - 15 && b.y >= 15 && b.y <= 55 && env->options_pupop_showed == 1)
			env->options_pupop_showed = 0;
   	}
}