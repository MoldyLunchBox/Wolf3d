#include "wolf3d.h"


void init_rect_decoration(t_rect_decoration *rd)
{
	rd->rect_icon_coin_s = (SDL_Rect){0,0,512,512};
   	rd->rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	rd->rect_welcom_sc_s = (SDL_Rect){0, 0, 1920, 1440};
   	rd->rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_wolf3d_s = (SDL_Rect){0, 0, 867, 364};
   	rd->rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   	rd->rect_play_s = (SDL_Rect){0, 0, 250, 155};
   	rd->rect_play_d = (SDL_Rect){W_W/2-125, W_H/3, 250, 155};
   	rd->rect_quit_s = (SDL_Rect){0, 0, 250, 155};
   	rd->rect_quit_d = (SDL_Rect){W_W/2-125, W_H/3 + 200, 250, 155};
   	rd->rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
   	rd->rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
	rd->rect_aim_s = (SDL_Rect){0, 0, 576, 576};
   	rd->rect_aim_d = (SDL_Rect){W_W/2-20, W_H/2+5, 40, 40};
	rd->rect_heart_s = (SDL_Rect){0, 0, 200, 200};
   	rd->rect_heart_d = (SDL_Rect){10, W_H-50, 40, 40};
   	rd->rect_menu_sc_s = (SDL_Rect){0, 0, 800, 600};
   	rd->rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_menu_btns_home_s = (SDL_Rect){0, 0, 281, 137};
   	rd->rect_menu_btns_home_d = (SDL_Rect){W_W/2 - 100, (W_H/6*0)+(12*1), 200, W_H/6};
   	rd->rect_menu_btns_resume_s = (SDL_Rect){0, 1*137, 281, 137};
   	rd->rect_menu_btns_resume_d = (SDL_Rect){W_W/2 - 100, (W_H/6*1)+(12*2), 200, W_H/6};
   	rd->rect_menu_btns_restart_s = (SDL_Rect){0, 2*137, 281, 137};
   	rd->rect_menu_btns_restart_d = (SDL_Rect){W_W/2 - 100, (W_H/6*2)+(12*3), 200, W_H/6};
   	rd->rect_menu_btns_options_s = (SDL_Rect){0, 3*137, 281, 137};
   	rd->rect_menu_btns_options_d = (SDL_Rect){W_W/2 - 100, (W_H/6*3)+(12*4), 200, W_H/6};
   	rd->rect_menu_btns_exit_s = (SDL_Rect){0, 4*137, 281, 137};
   	rd->rect_menu_btns_exit_d = (SDL_Rect){W_W/2 - 100, (W_H/6*4)+(12*5), 200, W_H/6};
   	rd->rect_options_pupop_s = (SDL_Rect){0, 0, 771, 638};
   	rd->rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   	rd->rect_close_btn_s = (SDL_Rect){0, 0, 300, 300};
   	rd->rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   	rd->rect_rust_code_sc_s = (SDL_Rect){0, 0, 250, 250};
   	rd->rect_rust_code_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	rd->rect_back_btn_s = (SDL_Rect){0, 0, 120, 120};
   	rd->rect_back_btn_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	rd->rect_calculator_s = (SDL_Rect){0, 0, 150, 46};
   	rd->rect_calculator_d = (SDL_Rect){W_W/2-90, 60, 200, 70};
   	rd->rect_lose_sc_s = (SDL_Rect){0, 0, 1624, 892};
   	rd->rect_lose_sc_d = (SDL_Rect){0, 0, W_W, W_H};
	rd->rect_damage_sc_s = (SDL_Rect){0, 0, 800, 600};
   	rd->rect_damage_sc_d = (SDL_Rect){0, 0, W_W, W_H};
	rd->life_border = (SDL_Rect){38, W_H - 34, W_W/4 + 4, 9};
}


int main(int argc, char *argv[])
{
	t_envirenment env;
	t_player player;
	parsing(&env, argv[1]);
	init_game(&env, &player);
	load_walls(&env);
	load_doors(&env);
	
	load_shoots(&env);
	load_sprites(&env);
	SDL_Texture *tx_sprites[num_type_sprites];
	load_sprites_tex(&env, tx_sprites);
	t_decoration_surface s;
	load_decoration(&s);
	t_decoration_texture t;
	create_decoration_texture(&env, &t, s);
	t_rect_decoration rd;
	init_rect_decoration(&rd);
   	init_sound_effect(&env);
	t_obj ob_sprites[env.num_sprites];
	sprites_reset(ob_sprites, tx_sprites, &env);
	SDL_Event e;
	while (env.is_run)
	{
		while (SDL_PollEvent(&e))
			event(e, &env, &player, ob_sprites, tx_sprites);
		SDL_RenderClear(env.rend);
		cursor_mouse(&env);
		in_screen_1(&env, &t, &rd);
		in_screen_2(&env, &t, &rd, ob_sprites, &player);
		in_screen_3_4(&env, &t, &rd);
		in_screen_5(&env, &t, &rd, &player, ob_sprites, tx_sprites);
		SDL_RenderPresent(env.rend);
	}
	Mix_FreeChunk(env.foots_sound);
   	Mix_FreeChunk(env.coin_sound);
	Mix_FreeMusic(env.music);
	SDL_DestroyRenderer(env.rend);
	SDL_DestroyWindow(env.window);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}