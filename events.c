/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:26:38 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:26:41 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_down_event(t_envirenment *env,  SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE)
		env->is_run = SDL_FALSE;
	if (e.key.keysym.sym == SDLK_m)
		env->minimap = !env->minimap;
	if (e.key.keysym.sym == SDLK_t)
		env->texture = !env->texture;
	if (e.key.keysym.sym == SDLK_k)
		env->skybox = !env->skybox;
	if (e.key.keysym.sym == SDLK_BACKSPACE && env->screen == 4)
	{
		if (env->len_code > 1)
		{
			env->rust_code[env->len_code - 1] = '\0';
			env->len_code--;
		}
	}
	if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
      	Mix_Resume(0);
	if (e.key.keysym.sym == SDLK_p)
		env->cursor = !env->cursor;
}

void	mouse_event(t_envirenment *env, t_player *player, SDL_Event e, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (env->screen == 2)
	{
		//fire shoot
		player->gun_animation = SDL_TRUE;
		player->frame_gun_x = 0;
		player->is_shoot = SDL_TRUE;
		Mix_PlayChannel(1, env->gun_fire_sound, 0);
	}
    sound_press(e.button, env);
	play_press(e.button, env);
	quit_press(e.button, env); 
    menu_icon_press(e.button, env);
    close_btn_press(e.button, env);
    menu_buttons_press(e.button, env, player, ob_sprites, tx_sprites);
	back_btn_press(e.button, env, player);
	replay_press(e.button, env);
}

void event(SDL_Event e, t_envirenment *env, t_player *player, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (e.type == SDL_QUIT)
		env->is_run = SDL_FALSE;
	if (e.type == SDL_TEXTINPUT && env->screen == 4 && env->len_code < 5)
	{
		 strcat(env->rust_code, e.text.text);
		 env->len_code++;
	}
	if (e.type == SDL_MOUSEMOTION)
	{
		env->mouse_x = e.motion.x;
		env->mouse_y = e.motion.y;
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
		mouse_event(env, player, e, ob_sprites, tx_sprites);
	if (e.type == SDL_KEYDOWN)
		key_down_event(env, e);
	if (e.type == SDL_KEYUP)
		if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
			Mix_Pause(0);
}

