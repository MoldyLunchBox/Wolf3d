/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:11:52 by amya              #+#    #+#             */
/*   Updated: 2022/05/15 17:22:22 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void player_reset(t_player *player)
{
	player->x = 2 * cellS + 2.0f;
    player->y = 2 * cellS + 2.0f;
    player->a = dtor(1.0f);
	player->rotatSpeed = dtor(20.0f);
	player->size = cellS / 5;
	player->speed = 4;
	player->fov = 60.0;
	player->frame_gun_x = 0;
	player->frame_gun_y = 0;
	player->gun_animation = SDL_FALSE;
	player->is_shoot = SDL_FALSE;
	
	player->blood = W_W/4;
	player->life = (SDL_Rect){40, W_H - 32, player->blood, 5};
	player->damaged = SDL_FALSE;
}

void env_reset(t_envirenment *env)
{
	env->is_run = SDL_TRUE;
	env->code_valid = SDL_FALSE;
	env->rust_code[0] = ' ';
	env->len_code = 1;
	env->rust_code[1] = '\0';
   	env->options_pupop_showed = 0;
	env->screen = 1;
	env->fps = 2;
	env->fps_quit = 2;
	env->frame_sound = 0;
	env->frame_quit = 0;
	env->frame_door=0;
	env->fade = 220;
	env->num_sprites = 38;
	env->solde = 0;
	env->minimap = SDL_FALSE;
	env->texture = SDL_TRUE;
	env->skybox = SDL_FALSE;
	env->cursor = SDL_TRUE;
	env->bg_music_active = SDL_TRUE;
	env->enemy_num = 12;
	if (env->door_position != -1)
		env->map[env->door_position] = 2;
	env->map_length = env->map_size * cellS;
}


void init_game(t_envirenment *env, t_player *player)
{
	env_reset(env);
	player_reset(player);
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	env->font1 = TTF_OpenFont("/Library/Fonts/Arial.ttf", 42);
	env->font2 = TTF_OpenFont("/Library/Fonts/Arial.ttf", 26);
	env->window = SDL_CreateWindow(
		"Wolf3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		W_W,
		W_H,
		SDL_WINDOW_SHOWN);
	env->rend = SDL_CreateRenderer(env->window, -1, SDL_RENDERER_ACCELERATED);
}

