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

void	in_screen_1(t_envirenment *env, t_decor_texture *t, t_rect_decor *rd)
{
	if (env->screen == 1)
	{
		Mix_Pause(2);
		Mix_ResumeMusic();
		SDL_RenderCopy(env->rend, t->tx_welcom_sc, &rd->rect_welcom_sc_s,
			&rd->rect_welcom_sc_d);
		SDL_RenderCopy(env->rend, t->tx_wolf3d, &rd->rect_wolf3d_s,
			&rd->rect_wolf3d_d);
		SDL_RenderCopy(env->rend, t->tx_play, &rd->rect_play_s,
			&rd->rect_play_d);
		SDL_RenderCopy(env->rend, t->tx_quit, &rd->rect_quit_s,
			&rd->rect_quit_d);
	}
	else
		Mix_PauseMusic();
	if (env->options_pupop_showed == 1)
	{
		SDL_RenderCopy(env->rend, env->t.tx_options_pupop,
			&env->rd.rect_options_pupop_s, &env->rd.rect_options_pupop_d);
		SDL_RenderCopy(env->rend, env->t.tx_close_btn,
			&env->rd.rect_close_btn_s, &env->rd.rect_close_btn_d);
	}
}

void	in_screen_2_suiv(t_envirenment *env, t_player *player)
{
	SDL_SetRenderDrawColor(env->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(env->rend, &env->rd.life_border);
	SDL_SetRenderDrawColor(env->rend, 255, 0, 0, 255);
	SDL_RenderFillRect(env->rend, &player->life);
	SDL_RenderCopy(env->rend, env->t.tx_heart, &env->rd.rect_heart_s,
		&env->rd.rect_heart_d);
	wr(env, ft_strjoin("x ", ft_itoa(env->solde)),
		(t_p){W_W / 2, 10});
	fadding(env);
	if (player->damaged)
		SDL_RenderCopy(env->rend, env->t.tx_damage_sc,
			&env->rd.rect_damage_sc_s, &env->rd.rect_damage_sc_d);
}

void	in_screen_2(t_envirenment *env, t_player *player)
{
	if (env->screen == 2)
	{
		update(player, env->ob_sprites, env);
		render(env, player);
		gun_animation(env->rend, player, env->shoots);
		show_door_code(player, env);
		if (env->code_valid)
			open_door(env);
		quit_animation(env);
		env->rd.rect_sound_s = (SDL_Rect){752 * env->frame_sound, 0, 752, 774};
		env->rd.rect_icon_coin_d = (SDL_Rect){W_W / 2 - 35, 10, 30, 30};
		env->rd.rect_aim_d = (SDL_Rect){W_W / 2 - 20, env->mouse_y, 40, 40};
		SDL_RenderCopy(env->rend, env->t.tx_icon, &env->rd.rect_sound_s,
			&env->rd.rect_sound_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_icon,
			&env->rd.rect_menu_icon_s, &env->rd.rect_menu_icon_d);
		SDL_RenderCopy(env->rend, env->t.tx_icon_coin,
			&env->rd.rect_icon_coin_s, &env->rd.rect_icon_coin_d);
		SDL_RenderCopy(env->rend, env->t.tx_aim, &env->rd.rect_aim_s,
			&env->rd.rect_aim_d);
		in_screen_2_suiv(env, player);
	}
}

void	in_screen_3(t_envirenment *env)
{
	if (env->screen == 3)
	{
		SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, env->t.tx_menu_sc,
			&env->rd.rect_menu_sc_s, &env->rd.rect_menu_sc_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_icon,
			&env->rd.rect_menu_icon_s, &env->rd.rect_menu_icon_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_btns,
			&env->rd.rect_menu_btns_home_s, &env->rd.rect_menu_btns_home_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_btns,
			&env->rd.rect_menu_btns_resume_s, &env->rd.rect_menu_btns_resume_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_btns,
			&env->rd.rect_menu_btns_rstr_s, &env->rd.rect_menu_btns_rstr_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_btns,
			&env->rd.rect_menu_btns_ops_s, &env->rd.rect_menu_btns_ops_d);
		SDL_RenderCopy(env->rend, env->t.tx_menu_btns,
			&env->rd.rect_menu_btns_exit_s, &env->rd.rect_menu_btns_exit_d);
	}
	if (strcmp(env->rust_code, " 1337") == 0 && env->screen == 4)
	{
		env->code_valid = SDL_TRUE;
		env->screen = 2;
	}
}

void	in_screen_4_5(t_envirenment *env, t_player *player)
{
	if (env->screen == 4)
	{
		SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, env->t.tx_rust_code_sc,
			&env->rd.rect_rust_code_sc_s, &env->rd.rect_rust_code_sc_d);
		SDL_RenderCopy(env->rend, env->t.tx_back_btn,
			&env->rd.rect_back_btn_s, &env->rd.rect_back_btn_d);
		SDL_RenderCopy(env->rend, env->t.tx_calculator,
			&env->rd.rect_calculator_s, &env->rd.rect_calculator_d);
		wr(env, env->rust_code, (t_p){W_W / 2 - 85, 85});
	}
	if (env->screen == 5)
	{
		Mix_Pause(3);
		Mix_Pause(6);
		SDL_RenderClear(env->rend);
		SDL_RenderCopy(env->rend, env->t.tx_lose_sc, &env->rd.rect_lose_sc_s,
			&env->rd.rect_lose_sc_d);
		env->rd.rect_icon_coin_d = (SDL_Rect){W_W / 2 - 35, W_H / 5, 30, 30};
		SDL_RenderCopy(env->rend, env->t.tx_icon_coin,
			&env->rd.rect_icon_coin_s, &env->rd.rect_icon_coin_d);
		wr(env, ft_strjoin("x ", ft_itoa(env->solde)), (t_p){W_W / 2, W_H / 5});
		player_reset(player);
		sprites_reset(env->ob_sprites, env->tx_sprites, env);
	}
}
