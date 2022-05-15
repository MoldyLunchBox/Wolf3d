/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:56:00 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/15 18:56:01 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void in_screen_1(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd)
{
	if (env->screen == 1)
    {
		Mix_Pause(2);
		Mix_ResumeMusic();
       	SDL_RenderCopy(env->rend, t->tx_welcom_sc, &rd->rect_welcom_sc_s, &rd->rect_welcom_sc_d);
       	SDL_RenderCopy(env->rend, t->tx_wolf3d, &rd->rect_wolf3d_s, &rd->rect_wolf3d_d);
       	SDL_RenderCopy(env->rend, t->tx_play, &rd->rect_play_s, &rd->rect_play_d);
		SDL_RenderCopy(env->rend, t->tx_quit, &rd->rect_quit_s, &rd->rect_quit_d);
    }
	else
		Mix_PauseMusic();
}


void in_screen_2(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd, t_obj *ob_sprites, t_player *player)
{
	if (env->screen == 2)
    {
		update(player, ob_sprites, env);
		render(env->rend, player, env->walls, env->quit, env->doors, env->floor, env->sky, env->ceil, ob_sprites, env);
		gun_animation(env->rend, player, env->shoots);
		show_door_code(player, env);
		if (env->code_valid)
			open_door(env);
		quit_animation(env);
       	rd->rect_sound_s = (SDL_Rect){752 * env->frame_sound, 0, 752, 774};
		rd->rect_icon_coin_d = (SDL_Rect){W_W/2-35,10,30,30};
		rd->rect_aim_d = (SDL_Rect){W_W/2-20, env->mouse_y, 40, 40};			
		SDL_RenderCopy(env->rend, t->tx_icon, &rd->rect_sound_s, &rd->rect_sound_d);
       	SDL_RenderCopy(env->rend, t->tx_menu_icon, &rd->rect_menu_icon_s, &rd->rect_menu_icon_d);
		SDL_RenderCopy(env->rend, t->tx_icon_coin, &rd->rect_icon_coin_s, &rd->rect_icon_coin_d);
		SDL_RenderCopy(env->rend, t->tx_aim, &rd->rect_aim_s, &rd->rect_aim_d);
		SDL_SetRenderDrawColor(env->rend, 255,255,255,255);
		SDL_RenderFillRect(env->rend, &rd->life_border);
		SDL_SetRenderDrawColor(env->rend, 255,0,0,255);
		SDL_RenderFillRect(env->rend, &player->life);
		SDL_RenderCopy(env->rend, t->tx_heart, &rd->rect_heart_s, &rd->rect_heart_d);
		write_text(env->rend, env->font2, ft_strjoin("x ", ft_itoa(env->solde)), W_W/2, 10);
		fadding(env);
		if (player->damaged)
			SDL_RenderCopy(env->rend, t->tx_damage_sc, &rd->rect_damage_sc_s, &rd->rect_damage_sc_d);
	}
}

void in_screen_3_4(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd)
{
	if (env->screen == 3)
    {
       SDL_RenderClear(env->rend);
       SDL_RenderCopy(env->rend, t->tx_menu_sc, &rd->rect_menu_sc_s, &rd->rect_menu_sc_d);
       SDL_RenderCopy(env->rend, t->tx_menu_icon, &rd->rect_menu_icon_s, &rd->rect_menu_icon_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_home_s, &rd->rect_menu_btns_home_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_resume_s, &rd->rect_menu_btns_resume_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_restart_s, &rd->rect_menu_btns_restart_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_options_s, &rd->rect_menu_btns_options_d);
       SDL_RenderCopy(env->rend, t->tx_menu_btns, &rd->rect_menu_btns_exit_s, &rd->rect_menu_btns_exit_d);
    }
	if (env->screen == 4)
    {
       	SDL_RenderClear(env->rend);
       	SDL_RenderCopy(env->rend, t->tx_rust_code_sc, &rd->rect_rust_code_sc_s, &rd->rect_rust_code_sc_d);
       	SDL_RenderCopy(env->rend, t->tx_back_btn, &rd->rect_back_btn_s, &rd->rect_back_btn_d);
		SDL_RenderCopy(env->rend, t->tx_calculator, &rd->rect_calculator_s, &rd->rect_calculator_d);
		write_text(env->rend, env->font1, env->rust_code, W_W/2-90, 75);
    }
	if (strcmp(env->rust_code, " 1337") == 0 && env->screen == 4)
	{
		env->code_valid = SDL_TRUE;
		env->screen = 2;
	}
}

void in_screen_5(t_envirenment *env, t_decoration_texture *t, t_rect_decoration *rd, t_player *player, t_obj *ob_sprites, SDL_Texture **tx_sprites)
{
	if (env->screen == 5)
    {
		Mix_Pause(3);
		Mix_Pause(6);
       	SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, t->tx_lose_sc, &rd->rect_lose_sc_s, &rd->rect_lose_sc_d);
		rd->rect_icon_coin_d = (SDL_Rect){W_W/2-35,W_H/5,30,30};
		SDL_RenderCopy(env->rend, t->tx_icon_coin, &rd->rect_icon_coin_s, &rd->rect_icon_coin_d);
		write_text(env->rend, env->font2, ft_strjoin("x ", ft_itoa(env->solde)), W_W/2, W_H/5);
		player_reset(player);
		sprites_reset(ob_sprites, tx_sprites, env);
    }
	if (env->options_pupop_showed == 1)
    {
       	SDL_RenderCopy(env->rend, t->tx_options_pupop, &rd->rect_options_pupop_s, &rd->rect_options_pupop_d);
       	SDL_RenderCopy(env->rend, t->tx_close_btn, &rd->rect_close_btn_s, &rd->rect_close_btn_d);
    }
}