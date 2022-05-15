#ifndef WOLF3D_H
#define WOLF3D_H
#define W_W 800
#define W_H 600
#define mapWidth  24
#define mapHeight  24
#define numRays 800
#define num_type_sprites 8
#include <math.h>
#include "./libft/libft.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
#include <string.h>

#define PI 3.1415926535
#define wallPadding 10
#define cellS 20 //map cube size
#define WALL_H 50
typedef struct	s_player
{
	float x;
	float y;
	float a;
	float rotatSpeed;
	float size;
	float dist[numRays];
	float speed;
	float fov;
	int frame_gun_x;
	int frame_gun_y;
	SDL_bool gun_animation;
	SDL_bool is_shoot;
	SDL_bool damaged;
	int blood;
	SDL_Rect life;

}				t_player;

typedef struct	s_ray
{
	int num;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float ca;
	float dist;
	float dist_h;
	float hx;
	float hy;
	float dist_v;
	float vx;
	float vy;
	float shade;
}				t_ray;

typedef struct	s_texture
{
	int num;
	int vmt;
	int hmt;
	SDL_Surface *img;
	float ty_step;
	float ty_offset;
	float ty;
	float tx;
	float scaling;
}				t_texture;

typedef struct	s_environment
{
	SDL_bool is_run;
	TTF_Font  *font1;
	TTF_Font  *font2;
	SDL_Window *window;
	SDL_Renderer *rend;
	SDL_Surface *walls[14];
	SDL_Surface *quit[4];
	SDL_Surface *doors[7];
	SDL_Surface *shoots[9];
	SDL_Surface *sprites[num_type_sprites];
	SDL_Surface *floor;
	SDL_Surface *ceil;
	SDL_Surface *sky;
	int *map;
	int map_size;
	int len_code;
	int door_position;
	int map_length;
	char rust_code[6];
	int screen;
	int fps;
	int fps_quit;
	int frame_sound;
	int frame_door;
	int frame_quit;
	int fade;
	int num_sprites;
	int solde;
	int menu_btn_clicked;
	int previous_screen;
	int options_pupop_showed;
	Mix_Music *music;
	Mix_Chunk *foots_sound;
   	Mix_Chunk *coin_sound;
	Mix_Chunk *bg_music;
	Mix_Chunk *enemy_sound;
	Mix_Chunk *gun_fire_sound;
	Mix_Chunk *aid_kit_sound;
	Mix_Chunk *pain_sound;
	int mouse_x;
	int mouse_y;
	SDL_bool code_valid;
	SDL_bool minimap;
	SDL_bool texture;
	SDL_bool skybox;
	SDL_bool cursor;
	SDL_bool bg_music_active;
	int enemy_num;
}				t_envirenment;

typedef struct  s_obj
{
    float               x;
    float               y;
    float               frame_width;
    float               frame_higth;
    int                	state;
    float    			size_x;
	float    			size_y;
    float               frame_num;
    float               row;
	float				h;
	float				w;
	float				surface_w;
	float				dist_to_player;
	SDL_Texture 		*texture;
	int 				fps;
	SDL_bool			alive;
	int					damage;
	int					prev_state;
	int					id;
	
}   			t_obj;

typedef struct	s_vars_obj
{
	float x;
	float y;
	float frame_width;
	float frame_higth;
	float state;
	float size_x;
	float size_y;
	float frame_num;
	float surface_w;
	int	prev_state;
}				t_vars_obj;

typedef struct  s_pnt
{
	float ma;
	float mi;
}				t_pnt;

typedef struct	s_var_int
{
	int x0;
	int y0;
	int ipx;
	int ipx_add_x0;
	int ipx_sub_x0;
	int ipy;
	int ipy_add_y0;
	int ipy_sub_y0;
}				t_var_int;

typedef struct	s_color
{
	int red;
	int green;
	int blue;
}				t_color;

typedef struct	s_rend_vars
{
	int	mx;
	int	my;
	int	mp;
	int	dof;
}				t_rend_vars;

typedef struct	s_decoration_surface
{
	SDL_Surface *welcom_sc;
   	SDL_Surface *wolf3d;
   	SDL_Surface *play;
	SDL_Surface *quit;
   	SDL_Surface *menu_icon;
   	SDL_Surface *icon;
   	SDL_Surface *menu_sc;
   	SDL_Surface *menu_btns;
   	SDL_Surface *options_pupop;
   	SDL_Surface *close_btn;
	SDL_Surface *rust_code_sc;
	SDL_Surface *back_btn;
	SDL_Surface *calculator;
	SDL_Surface *lose_sc;
	SDL_Surface *coin;
	SDL_Surface *gun;
	SDL_Surface *aim;
	SDL_Surface *heart;
	SDL_Surface *damage_sc;
}				t_decoration_surface;

typedef struct	s_decoration_texture
{
	SDL_Texture *tx_icon_coin;
	SDL_Texture *tx_icon;
	SDL_Texture *tx_welcom_sc;
	SDL_Texture *tx_wolf3d;
	SDL_Texture *tx_play;
	SDL_Texture *tx_quit;
	SDL_Texture *tx_menu_icon;
	SDL_Texture *tx_aim;
	SDL_Texture *tx_heart;
	SDL_Texture *tx_menu_sc;
	SDL_Texture *tx_menu_btns;
	SDL_Texture *tx_options_pupop;
	SDL_Texture *tx_close_btn;
	SDL_Texture *tx_rust_code_sc;
	SDL_Texture *tx_back_btn;
	SDL_Texture *tx_calculator;
	SDL_Texture *tx_lose_sc;
	SDL_Texture *tx_damage_sc;
}				t_decoration_texture;

typedef struct	s_rect_decoration
{
	SDL_Rect rect_icon_coin_s;
	SDL_Rect rect_icon_coin_d;
	SDL_Rect rect_sound_s;
	SDL_Rect rect_sound_d;
	SDL_Rect rect_welcom_sc_s;
	SDL_Rect rect_welcom_sc_d;
	SDL_Rect rect_wolf3d_s;
	SDL_Rect rect_wolf3d_d;
	SDL_Rect rect_play_s;
	SDL_Rect rect_play_d;
	SDL_Rect rect_quit_s;
	SDL_Rect rect_quit_d;
	SDL_Rect rect_menu_icon_s;
	SDL_Rect rect_menu_icon_d;
	SDL_Rect rect_aim_s;
	SDL_Rect rect_aim_d;
	SDL_Rect rect_heart_s;
	SDL_Rect rect_heart_d;
	SDL_Rect rect_menu_sc_s;
	SDL_Rect rect_menu_sc_d;
	SDL_Rect rect_menu_btns_home_s;
	SDL_Rect rect_menu_btns_home_d;
	SDL_Rect rect_menu_btns_resume_s;
	SDL_Rect rect_menu_btns_resume_d;
	SDL_Rect rect_menu_btns_restart_s;
	SDL_Rect rect_menu_btns_restart_d;
	SDL_Rect rect_menu_btns_options_s;
	SDL_Rect rect_menu_btns_options_d;
	SDL_Rect rect_menu_btns_exit_s;
	SDL_Rect rect_menu_btns_exit_d;
	SDL_Rect rect_options_pupop_s;
	SDL_Rect rect_options_pupop_d;
	SDL_Rect rect_close_btn_s;
	SDL_Rect rect_close_btn_d;
	SDL_Rect rect_rust_code_sc_s;
	SDL_Rect rect_rust_code_sc_d;
	SDL_Rect rect_back_btn_s;
	SDL_Rect rect_back_btn_d;
	SDL_Rect rect_calculator_s;
	SDL_Rect rect_calculator_d;
	SDL_Rect rect_lose_sc_s;
	SDL_Rect rect_lose_sc_d;
	SDL_Rect rect_damage_sc_s;
	SDL_Rect rect_damage_sc_d;
	SDL_Rect life_border;
}				t_rect_decoration;


void init_game(t_envirenment *env, t_player *player);
void env_reset(t_envirenment *env);
void player_reset(t_player *player);
float dtor(float d);
void	parsing(t_envirenment *env, char *file);
void load_walls(t_envirenment *env);
void load_doors(t_envirenment *env);
void load_shoots(t_envirenment *env);
void load_sprites(t_envirenment *env);
#endif