/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:17:51 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:17:55 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void load_sprites_tex(t_envirenment *env, SDL_Texture **tx_sprites)
{
	tx_sprites[0] = SDL_CreateTextureFromSurface(env->rend, env->sprites[0]);
	tx_sprites[1] = SDL_CreateTextureFromSurface(env->rend, env->sprites[1]);
	tx_sprites[2] = SDL_CreateTextureFromSurface(env->rend, env->sprites[2]);
	tx_sprites[3] = SDL_CreateTextureFromSurface(env->rend, env->sprites[3]);
	tx_sprites[4] = SDL_CreateTextureFromSurface(env->rend, env->sprites[4]);
	tx_sprites[5] = SDL_CreateTextureFromSurface(env->rend, env->sprites[5]);
	tx_sprites[6] = SDL_CreateTextureFromSurface(env->rend, env->sprites[6]);
	tx_sprites[7] = SDL_CreateTextureFromSurface(env->rend, env->sprites[7]);
}

void load_decoration(t_decoration_surface *s)
{
	s->icon = IMG_Load("resources/images/decoration/sound.png");
   	s->welcom_sc = IMG_Load("resources/images/decoration/welcom_sc.png");
   	s->wolf3d = IMG_Load("resources/images/decoration/wolf3d.png");
   	s->play = IMG_Load("resources/images/decoration/play.png");
	s->quit = IMG_Load("resources/images/decoration/quit.png");
   	s->menu_icon = IMG_Load("resources/images/decoration/menu_icon.png");
   	s->menu_sc = IMG_Load("resources/images/decoration/menu_sc.png");
   	s->menu_btns = IMG_Load("resources/images/decoration/menu_buttons.png");
   	s->options_pupop = IMG_Load("resources/images/decoration/options_pupop.png");
   	s->close_btn = IMG_Load("resources/images/decoration/close_btn.png");
	s->rust_code_sc = IMG_Load("resources/images/decoration/rust_code_sc.png");
	s->back_btn = IMG_Load("resources/images/decoration/back_btn.png");
	s->calculator = IMG_Load("resources/images/decoration/calculator.png");
	s->lose_sc = IMG_Load("resources/images/decoration/lose_sc.png");
	s->coin = IMG_Load("resources/images/sprites/coin.png");
	s->aim = IMG_Load("resources/images/decoration/aim.png");
	s->heart = IMG_Load("resources/images/decoration/heart.png");
	s->damage_sc = IMG_Load("resources/images/decoration/damage_sc.png");
}

void create_decoration_texture(t_envirenment *env, t_decoration_texture *t, t_decoration_surface s)
{
	t->tx_icon_coin = SDL_CreateTextureFromSurface(env->rend, s.coin);
   	t->tx_icon = SDL_CreateTextureFromSurface(env->rend, s.icon);
   	t->tx_welcom_sc = SDL_CreateTextureFromSurface(env->rend, s.welcom_sc);
   	t->tx_wolf3d = SDL_CreateTextureFromSurface(env->rend, s.wolf3d);
   	t->tx_play = SDL_CreateTextureFromSurface(env->rend, s.play);
   	t->tx_quit = SDL_CreateTextureFromSurface(env->rend, s.quit);
   	t->tx_menu_icon = SDL_CreateTextureFromSurface(env->rend, s.menu_icon);
   	t->tx_aim = SDL_CreateTextureFromSurface(env->rend, s.aim);
   	t->tx_heart = SDL_CreateTextureFromSurface(env->rend, s.heart);
   	t->tx_menu_sc = SDL_CreateTextureFromSurface(env->rend, s.menu_sc);
   	t->tx_menu_btns = SDL_CreateTextureFromSurface(env->rend, s.menu_btns);
   	t->tx_options_pupop = SDL_CreateTextureFromSurface(env->rend, s.options_pupop);
   	t->tx_close_btn = SDL_CreateTextureFromSurface(env->rend, s.close_btn);
   	t->tx_rust_code_sc = SDL_CreateTextureFromSurface(env->rend, s.rust_code_sc);
   	t->tx_back_btn = SDL_CreateTextureFromSurface(env->rend, s.back_btn);
   	t->tx_calculator = SDL_CreateTextureFromSurface(env->rend, s.calculator);
   	t->tx_lose_sc = SDL_CreateTextureFromSurface(env->rend, s.lose_sc);
   	t->tx_damage_sc = SDL_CreateTextureFromSurface(env->rend, s.damage_sc);
	env->floor = IMG_Load("resources/floor_derty.png");
	env->ceil = IMG_Load("resources/ceil.png");
	env->sky = IMG_Load("resources/night_sky.png");
}