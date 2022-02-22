#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
#include "wolf3d.h"

#define PI 3.1415926535
#define mapX 24	//map width
#define mapY 24
#define wallPadding 10
#define cellS 20 //map cube size
#define mapS mapX * cellS
#define WALL_H 50

int sound_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50)
         return (1);
   }
   return (0);
}

int play_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-156 && b.x <= W_W/2-156 + 313 && b.y >= W_H/2 && b.y <= W_H/2 + 159)
         return (1);
   }
   return (0);
}

int menu_icon_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= 10 && b.x <= 60 && b.y >= 10 && b.y <= 60)
         return (1);
   }
   return (0);
}

int menu_buttons_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-100 && b.x <= W_W/2+100)
      {
         if (b.y >= (W_H/6*0)+(12*1) && b.y <= (W_H/6*0)+(12*1) + W_H/6)
            return (1);
         if (b.y >= (W_H/6*1)+(12*2) && b.y <= (W_H/6*1)+(12*2) + W_H/6)
            return (2);
         if (b.y >= (W_H/6*2)+(12*3) && b.y <= (W_H/6*2)+(12*3) + W_H/6)
            return (3);
         if (b.y >= (W_H/6*3)+(12*4) && b.y <= (W_H/6*3)+(12*4) + W_H/6)
            return (4);
         if (b.y >= (W_H/6*4)+(12*5) && b.y <= (W_H/6*4)+(12*5) + W_H/6)
            return (5);
      }
   }
   return (0);
}

int close_btn_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W - 55 && b.x <= W_W - 15 && b.y >= 15 && b.y <= 55)
         return (1);
   }
   return (0);
}

int img_player_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.y >= W_H/2+W_H/6 && b.y <= W_H/2+W_H/6+W_H/2-W_H/4)
      {
         if (b.x >= W_W/5 && b.x <= W_W/5 + W_W/9)
            return (1);
         if (b.x >= W_W-W_W/5-W_W/10 && b.x <= W_W-W_W/5-W_W/10 + W_W/9)
            return (2);
      }
   }
   return (0);
}

float dtor(float d)
{
    return (d * PI / 180.0f);
}

float distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax)*(bx - ax) + (by - ay)*(by - ay)));
}

int text[] =		
	{
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,1,1,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,1,1,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,1,1,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,1,1,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,0,0,0,0,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,
		
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0
};
int map12[] =		//the map array. Edit to change level but keep the outer walls
{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		
};

int map[] =		//the map array. Edit to change level but keep the outer walls
{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		
};

void    create_obj(t_obj *obj)
{
    obj = (t_obj*)malloc(sizeof(t_obj));
}

void    init_obj(t_obj *obj, float x, float y, float z, float frameWidth, float frameHigth, char *textureId, SDL_RendererFlip flip, float speed, float frameCount, float row, float surface_w)
{
    obj->x = x;
    obj->y = y;
    obj->frameWidth = frameWidth;
    obj->frameHigth = frameHigth;
    obj->textureId = textureId;
    obj->flip = flip;
    obj->speed = speed;
    obj->frameCount = frameCount;
    obj->row = row;
	obj->surface_w = surface_w;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	    case 1:
	        return *p;
	        break;

	    case 2:
	        return *(Uint16 *)p;
	        break;

	    case 3:
	        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	            return p[0] << 16 | p[1] << 8 | p[2];
	        else
	            return p[0] | p[1] << 8 | p[2] << 16;
	            break;

	        case 4:
	            return *(Uint32 *)p;
	            break;

	        default:
	            return 0;       /* shouldn't happen, but avoids warnings */
	      }
}

float range_conversion_val(float old_max, float old_min, float new_max, float new_min, float old_value)
{
	float old_range = (old_max - old_min);
	float new_range = (new_max - new_min);  
	float new_value = (((old_value - old_min) * new_range) / old_range) + new_min;
	return (new_value);
}
float safe_angle(float a)
{
	if (a > 2*PI)
			a -= 2*PI;
	if (a < 0)
			a += 2*PI;
	return (a);
}

void safe_map(t_player *player, float pdx, float pdy)
{	
	int x0=0;
	int y0=0;
	if (pdx<0)
		x0=-wallPadding;
	else
		x0=wallPadding;
	if (pdy<0)
		y0=-wallPadding;
	else
		y0=wallPadding;
	int ipx=player->x/cellS;
	int ipx_add_x0=(player->x+x0)/cellS;
	int ipx_sub_x0=(player->x-x0)/cellS;
	int ipy=player->y/cellS;
	int ipy_add_y0=(player->y+y0)/cellS;
	int ipy_sub_y0=(player->y-y0)/cellS;

	if (ipy*mapX + ipx_add_x0 != 0 && map[ipy*mapX + ipx_add_x0] == 0)
		player->x+=pdx*player->speed;
	if (ipy_add_y0*mapX + ipx != 0 && map[ipy_add_y0*mapX + ipx] == 0)
		player->y+=pdy*player->speed;
}

void player_reset(t_player *player)
{
	player->x = 2*cellS + 2.0f; //depent to map
    player->y = 2*cellS + 2.0f; //depent to map
    player->a = dtor(1.0f);
	player->rotatSpeed = dtor(4.0f); // 0.5 not map 2.0 with map
	player->size = cellS / 5;
	player->speed = 3;
	player->fov = 60.0;
	player->player_num = 1;
	player->frame_player_x = 4;
   	player->frame_player_y = 1;
	
}

void update(t_player *player, SDL_Renderer *rend)
{
	const uint8_t* keys = SDL_GetKeyboardState(NULL);

	float dx = 0.0f, dy = 0.0f;

	if (keys[SDL_SCANCODE_DOWN])
    {
		player->frame_player_x++;
        player->frame_player_y = 0;
       
		dx -= cos(player->a);
        dy += sin(player->a);
	}
	if (keys[SDL_SCANCODE_UP])
    {
		player->frame_player_x++;
        player->frame_player_y = 1;
		dx += cos(player->a);
        dy -= sin(player->a);
	}
	if (keys[SDL_SCANCODE_A])
	{
		player->a += player->rotatSpeed;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
	}
	if (keys[SDL_SCANCODE_D])
	{
		player->a -= player->rotatSpeed;
		if (player->a < 0)
			player->a += 2 * PI;
	}
	if (player->frame_player_x > 7)
       player->frame_player_x = 0;
    if (player->frame_player_x < 0)
       player->frame_player_x = 7;
	safe_map(player, dx, dy);
}

void draw_player(t_player *player, SDL_Renderer *rend)
{
	int i;
	int j;
	i = (player->y);
	while (i < player->y + player->size)
	{
		j = (player->x);
		while (j < player->x + player->size)
		{
			SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
			SDL_RenderDrawPoint(rend, j, i);
			j++;
		}
		i++;
	}
	SDL_RenderDrawLine(rend, player->x+player->size/2, player->y+player->size/2, player->x + 20 * cos(player->a) + player->size/2, player->y - 20 * sin(player->a) + player->size/2);
}

void draw_sprite(SDL_Renderer *rend, t_player *player, SDL_Texture *tx_key, t_obj ob_key)
{
	float dx = ob_key.x - player->x;
	float dy = ob_key.y - player->y;
	
	float tmp_ang = fmodf((atan2(dx, dy)) + 2*PI, 2*PI) + PI/2;
	tmp_ang = safe_angle(tmp_ang);
	float tmp_player_a = player->a + PI ;
	tmp_player_a = safe_angle(tmp_player_a);
	float min_a = tmp_player_a - dtor(player->fov / 2);
	float max_a = tmp_player_a + dtor(player->fov / 2);

	SDL_Rect rect0, rect1;

	if (tmp_ang > min_a && tmp_ang < max_a)
	{
		float adjust_h;
		if (tmp_ang-min_a >= 0.5)
			adjust_h = tmp_ang-min_a;
		if (tmp_ang-min_a < 0.5)
			adjust_h = 1 - (tmp_ang-min_a);
		adjust_h-=0.5;
		printf("%f\n",adjust_h);
		float s_dist = distance(player->x, player->y, ob_key.x, ob_key.y);
		ob_key.h = ((WALL_H * 220) / (s_dist - (adjust_h*10)));
		ob_key.w = ((WALL_H * 220) / s_dist)/3;
		float diff_a = tmp_player_a - tmp_ang;
		float sx = range_conversion_val(dtor(player->fov/2), -dtor(player->fov/2), W_W , 0, diff_a); //ob_key.size decalage pour sprite width

		// printf("%f %f\n", ob_key.h, ob_key.w);
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
		for (int i = (int)sx; i < (int)sx + ob_key.w; i++)
		{
			if (s_dist-(adjust_h*10) < player->dist[i])
			{
				float on_floor = ((WALL_H * 220) / s_dist) / 2;
				
				rect0 = (SDL_Rect){ob_key.frameWidth * ob_key.frameCount + ((float)ob_key.surface_w/ob_key.w * (i-(int)sx)), ob_key.frameHigth * ob_key.row, (float)ob_key.surface_w/ob_key.w, ob_key.frameHigth};
				rect1 = (SDL_Rect){i, W_H/2 /*+ on_floor */- ob_key.h /2, 1, ob_key.h};
				if(SDL_RenderCopyEx(rend, tx_key, &rect0, &rect1, 0, NULL, SDL_FLIP_NONE) != 0)
				{
					printf("create tx_key Error: %s\n", SDL_GetError());
    			    SDL_Quit();
				}
			}
		}
	}
}

void render_view(SDL_Renderer *rend, t_player *player, t_ray r, t_texture t, SDL_Surface **images, SDL_Surface *floor, SDL_Surface *ceil, SDL_bool show_texture, SDL_bool show_skybox)
{
	float line_h;
	SDL_Rect line;
	int y;

	line.w = W_W/numRays;
	line.x = r.num*line.w;
	line.h = 1;
	
	line_h = (WALL_H * 220) / r.dist; //220 how player far to screen

	if (t.num == 1)
		(t.img) = images[0];
	if (t.num == 2)
		(t.img) = images[1];
	t.ty_step = (t.img)->w / (float)line_h;
	t.ty_offset = 0;
	if (line_h > W_H)
	{
		t.ty_offset = (line_h - W_H) / 2.0;
		line_h = W_H;
	}
	if (line_h <= 0)
		line_h = 1;
	// printf("%f\n", line_h);
	
	t.ty = t.ty_offset * t.ty_step;	
	t.scaling=(float)(t.img)->w/cellS;
	if (r.shade == 1)
	{
		t.tx = (int)(r.rx*t.scaling)%(t.img)->w; //scaling = scal (t.img)
		if (r.ra > PI)
			t.tx=((t.img)->w-1)-t.tx; // flip direction left/right
	}
	else
	{
		t.tx = (int)(r.ry*t.scaling)%(t.img)->w;
		if (r.ra > PI/2 && r.ra < (3*PI)/2)
			t.tx=((t.img)->w-1)-t.tx; // flip direction left/right
	}
	//wall
	for (y = 0; y < line_h; y++)
	{
		line.y = (W_H / 2) - (line_h / 2) + y; //offset to center
		// float c = text[(int)(ty)*32 + (int)(t.tx)] * r.shade;
		// SDL_SetRenderDrawColor(rend, 255 - (c * 100), 255 - (c * 100), 255 - (c * 100), 255);
		if (show_texture)
		{
			SDL_Color rgb;
			Uint32 data = getpixel((t.img), (int)(t.tx), (int)(t.ty));
			SDL_GetRGB(data, (t.img)->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r*r.shade, rgb.g*r.shade, rgb.b*r.shade, 255);
		}
		SDL_RenderFillRect(rend, &line);
		t.ty+=t.ty_step;
	}
	for (y = (W_H / 2) + (line_h / 2); y < W_H; y++)
	{
		// draw floor
		line.y = y;
		float dy = y-(W_H/2.0);
		r.ra = safe_angle(r.ra);
		float raFix = cos(player->a - r.ra);
		t.tx = player->x*10 + cos(r.ra)*220*floor->w/dy/raFix;
		t.ty = player->y*10 - sin(r.ra)*220*floor->w/dy/raFix;
		SDL_SetRenderDrawColor(rend, 200, 100, 50, 255);
		// float c = text[((int)(t.ty)&31)*32 + ((int)(t.tx)&31)] * 0.7;
		// SDL_SetRenderDrawColor(rend, 255 - (c * 100), 255 - (c * 100), 255 - (c * 100), 255);
		
		SDL_Color rgb;
		Uint32 data;
		if (show_texture)
		{
			data = getpixel(floor, (int)(t.tx)&(floor->w-1), (int)(t.ty)&(floor->w-1));
			SDL_GetRGB(data, floor->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
		}
		SDL_RenderFillRect(rend, &line);
		// draw ceiling
		line.y = (W_H/2.0) - (y - (W_H/2.0)) - 1;
		SDL_SetRenderDrawColor(rend, 150, 150, 200, 255);
		if (show_texture && !show_skybox)
		{
			data = getpixel(ceil, (int)(t.tx)&(ceil->w-1), (int)(t.ty)&(ceil->w-1));
			SDL_GetRGB(data, ceil->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
			SDL_RenderFillRect(rend, &line);
		}
		
		if (!show_texture)
			SDL_RenderFillRect(rend, &line);
	}

}

void render_rays(SDL_Renderer *rend, t_player *player, SDL_bool show_map, SDL_bool show_texture, SDL_bool show_skybox, SDL_Surface **images, SDL_Surface *floor, SDL_Surface *ceil)
{
	int mx,my,mp,dof; //m=map, p=position, r=ray, dof=deept of field
	t_ray ray;
	t_texture tex;
	
	tex.vmt = 0;
	tex.hmt = 0;
	tex.img = images[0];
	ray.ra = player->a + dtor(player->fov / 2);
	
	for (ray.num = 0; ray.num < numRays; ray.num++)
	{
		ray.ra = safe_angle(ray.ra);
		// check horizental line
		dof = 0;
		ray.dist_h = 100000;
		ray.hx = player->x;
		ray.hy = player->y;
		if (ray.ra != 0. && ray.ra != PI)
		{
			float aTan = 1/(tan(ray.ra));
			if (ray.ra < PI) //look up
			{
				ray.ry = (((int)(player->y) / cellS) * cellS - 0.0001);
				ray.rx = player->x - (ray.ry - player->y)*aTan;
				ray.yo = -(cellS);
				ray.xo = -ray.yo*aTan;
			}
			if (ray.ra > PI) //look down
			{
				ray.ry = (((int)(player->y) / cellS) * cellS) + cellS;
				ray.rx = player->x - (ray.ry - player->y)*aTan;
				ray.yo = cellS;
				ray.xo = -ray.yo*aTan;
			}
		}
		else //look rigth or left
		{
			ray.rx = player->x;
			ray.ry = player->y;
			dof = mapX;
		}
		
		while (dof < mapX)
		{
			mx = (int)(ray.rx)/cellS;
			my = (int)(ray.ry)/cellS;
			mp = my*mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] >= 1) //hit wall
			{
				ray.hx = ray.rx;
				ray.hy = ray.ry;
				ray.dist_h = distance(player->x, player->y, ray.hx, ray.hy);
				dof = mapX;
				tex.hmt=map[mp];
			}	
			else
			{
				// printf("tt\n");
				ray.rx+=ray.xo;
				ray.ry+=ray.yo;
				dof+=1;
			}
		}

		//check vertical line
		dof = 0;
		ray.dist_v = 100000;
		ray.vx = player->x;
		ray.vy = player->y;
	
		float aTan = (tan(ray.ra));
		if (ray.ra > PI/2 && ray.ra < (3*PI)/2) //look left
		{
			ray.rx = (((int)(player->x) / cellS) * cellS - 0.0001);
			ray.ry = player->y - (ray.rx - player->x)*aTan;
			ray.xo = -(cellS);
			ray.yo = -ray.xo*aTan;
		}
		if (ray.ra < PI/2 || ray.ra > (3*PI)/2) //look right
		{
			ray.rx = (((int)(player->x) / cellS) * cellS) + cellS;
			ray.ry = player->y - (ray.rx - player->x)*aTan;
			ray.xo = cellS;
			ray.yo = -ray.xo*aTan;
		}
		if (ray.ra == 0. || ray.ra == PI)//look stright rigth or left
		{
			ray.rx = player->x;
			ray.ry = player->y;
			dof = mapX;
		}
		// printf("%f %f %f\n", ray.ra, player->a, tan(ray.ra));
		
		while (dof < mapX)
		{
			mx = (int)(ray.rx)/cellS;
			my = (int)(ray.ry)/cellS;
			mp = my*mapX + mx;
			if (mp > 0 && mp < mapX*mapY && map[mp] >= 1) //hit wall
			{
				ray.vx = ray.rx;
				ray.vy = ray.ry;
				ray.dist_v = distance(player->x, player->y, ray.vx, ray.vy);
				dof = mapY;
				tex.vmt=map[mp];
			}	
			else
			{
				ray.rx+=ray.xo;
				ray.ry+=ray.yo;
				dof+=1;
			}
		}
		ray.shade = 1;
		if (ray.dist_v < ray.dist_h)
		{
			tex.num = tex.vmt;
			ray.shade = 0.5;
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist = ray.dist_v;
			if((ray.ra >= PI/2 && ray.ra <= (3*PI)/2))
				SDL_SetRenderDrawColor(rend, 0, 0, 150, 255);
			else
				SDL_SetRenderDrawColor(rend, 0, 150, 0, 255);
		}
		if (ray.dist_h < ray.dist_v)
		{
			tex.num = tex.hmt;
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist = ray.dist_h;
			if (ray.ra <= PI)
				SDL_SetRenderDrawColor(rend, 200, 0, 200, 255);
			else
				SDL_SetRenderDrawColor(rend, 200, 200, 0, 255);
		}
		ray.ca = safe_angle(player->a - ray.ra);
		
		ray.dist *=cos(ray.ca); //fix fisheye 
		
		player->dist[ray.num] = ray.dist;
		render_view(rend, player, ray, tex, images, floor, ceil, show_texture, show_skybox);

		ray.ra-=dtor(0.1);
	}
}


void render_map(t_player *player, SDL_Renderer *rend)
{
	int x, y, xo, yo;
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			yo = y * cellS;
			while (yo < y * cellS + cellS)
			{
				xo = x * cellS;
				while (xo < x * cellS + cellS)
				{
					if (map[y * mapX + x] >= 1)
						SDL_SetRenderDrawColor(rend, 150, 150, 150, 255);
					else
						SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
					if (x * cellS == xo || y * cellS == yo)
						SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
					SDL_RenderDrawPoint(rend, xo, yo);
					xo++;
				}
				yo++;
			}
		}
	}
	draw_player(player, rend);
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderDrawPoint(rend, 20*20, 20*20);
	SDL_RenderDrawPoint(rend, 20*20+1, 20*20);
	SDL_RenderDrawPoint(rend, 20*20-1, 20*20);
	SDL_RenderDrawPoint(rend, 20*20, 20*20+1);
	SDL_RenderDrawPoint(rend, 20*20, 20*20-1);

}

void	draw_sky(SDL_Renderer *rend, SDL_Surface *sky, t_player *player)
{
	int x, y, x0;

	for(x=0; x<600; x++)
	{

		for(y=0; y<300; y++)
		{			
			x0 = (int)(player->a*5 / PI * 180.0f) - x;
			if (x0 < 0)
				x0+=800;
			x0=x0%800;
			SDL_Color rgb;
			Uint32 data = getpixel(sky, x0, y);
			SDL_GetRGB(data, sky->format, &rgb.r, &rgb.g, &rgb.b);
			SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
			SDL_RenderDrawPoint(rend, x, y);
		}
	}
}

void render(SDL_Renderer *rend, SDL_bool show_skybox, SDL_bool show_texture, SDL_bool show_map, t_player *player, SDL_Surface **images, SDL_Surface *floor, SDL_Surface *sky, SDL_Surface *ceil, SDL_Texture *tx_key, t_obj ob_key)
{
	if (show_skybox)
		draw_sky(rend, sky, player);
    render_rays(rend, player, show_map, show_texture, show_skybox, images, floor, ceil);
	draw_sprite(rend, player, tx_key, ob_key);
    if (show_map)
        render_map(player, rend);
}

int main(int argc, char *argv[])
{
	/****************************** START-VARIABLES ****************************/
	t_player player;
	player_reset(&player);

	SDL_Surface *wall = IMG_Load("resources/wall.png");
	SDL_Surface *door = IMG_Load("resources/door1.jpg");
	SDL_Surface *floor = IMG_Load("resources/floor.png");
	SDL_Surface *ceil = IMG_Load("resources/ceil.png");
	SDL_Surface *sky = IMG_Load("resources/menu_sc.png");
	SDL_Surface *key = IMG_Load("resources/pillar.png");
	
	
   	SDL_Surface *welcom_sc;
   	SDL_Surface *wolf3d;
   	SDL_Surface *play;
   	SDL_Surface *menu_icon;
   	SDL_Surface *icon;
   	SDL_Surface *player1;
   	SDL_Surface *player2;
   	SDL_Surface *menu_sc;
   	SDL_Surface *menu_btns;
   	int menu_btn_clicked = 0;
   	int previous_screen = 1;
   	SDL_Surface *options_pupop;
   	int options_pupop_showed = 0;
   	SDL_Surface *close_btn;
   	int img_player_selected = 1;
   	SDL_Surface *img_player1;
   	SDL_Surface *img_player2;
   	SDL_Surface *selection_img_player;

	double frame_sound = 0;
   	int screen = 1;

	SDL_Surface *image[2];

	/****************************** END-VARIABLES ****************************/
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return (1);
    }
	SDL_Window *window = SDL_CreateWindow(
		"Wolf3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		W_W,
		W_H,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (rend == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) //Initialisation de l'API Mixer
   	{
   	   printf("3%s", Mix_GetError());
   	   return (1);
   	}

   	Mix_VolumeMusic(MIX_MAX_VOLUME/4);

	/************************ load textures **********************************/ 

	if (wall == NULL)
	{
    	printf("Failed to load image at 'resource/wall.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (door == NULL)
	{
    	printf("Failed to load image at 'resource/door.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	image[0] = wall;
	image[1] = door;

	if (floor == NULL)
	{
    	printf("Failed to load image at 'resource/floor.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (ceil == NULL)
	{
    	printf("Failed to load image at 'resource/ceil.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (sky == NULL)
	{
    	printf("Failed to load image at 'resource/sky.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	if (key == NULL)
	{
    	printf("Failed to load image at 'resource/key.png': %s\n", SDL_GetError());
		SDL_Quit();
    	return (1);
	}

	SDL_Texture *tx_key;
	tx_key = SDL_CreateTextureFromSurface(rend, key);
	if(tx_key == NULL)
	{
		SDL_FreeSurface(key);
		printf("create tx_key Error: %s\n", SDL_GetError());
        SDL_Quit();
	}

   	
   	icon = IMG_Load("resources/sound.png");
   	if (!icon)
   	{
   	   printf("4%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_sound_s;
   	SDL_Rect rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   	SDL_Texture *tx_icon = SDL_CreateTextureFromSurface(rend, icon);
   	SDL_FreeSurface(icon);

   	player1 = IMG_Load("resources/player1.png");
   	if (!player1)
   	{
   	   printf("5%s", SDL_GetError());
   	   return (1);
   	}
   	player2 = IMG_Load("resources/player2.png");
   	if (!player2)
   	{
   	   printf("5%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_player_s;
   	SDL_Rect rect_player_d = (SDL_Rect){W_W/2 - 200, W_H - 270, 400, 450};
   	SDL_Texture *tx_player1 = SDL_CreateTextureFromSurface(rend, player1);
   	SDL_Texture *tx_player2 = SDL_CreateTextureFromSurface(rend, player2);
   	SDL_FreeSurface(player1);
   	SDL_FreeSurface(player2);

   	welcom_sc = IMG_Load("resources/welcom_sc.png");
   	if (!welcom_sc)
   	{
   	   printf("6%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_welcom_sc_s;
   	SDL_Rect rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_welcom_sc = SDL_CreateTextureFromSurface(rend, welcom_sc);
   	SDL_FreeSurface(welcom_sc);

   	wolf3d = IMG_Load("resources/wolf3d.png");
   	if (!wolf3d)
   	{
   	   printf("7%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_wolf3d_s;
   	SDL_Rect rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   	SDL_Texture *tx_wolf3d = SDL_CreateTextureFromSurface(rend, wolf3d);
   	SDL_FreeSurface(wolf3d);

   	play = IMG_Load("resources/play.png");
   	if (!play)
   	{
   	   printf("8%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_play_s;
   	SDL_Rect rect_play_d = (SDL_Rect){W_W/2-150, W_H/2, 300, 160};
   	SDL_Texture *tx_play = SDL_CreateTextureFromSurface(rend, play);
   	SDL_FreeSurface(play);

   	menu_icon = IMG_Load("resources/menu_icon.png");
   	if (!menu_icon)
   	{
   	   printf("9%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_icon_s;
   	SDL_Rect rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
   	SDL_Texture *tx_menu_icon = SDL_CreateTextureFromSurface(rend, menu_icon);
   	SDL_FreeSurface(menu_icon);

   	menu_sc = IMG_Load("resources/menu_sc.png");
   	if (!menu_sc)
   	{
   	   printf("10%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_sc_s;
   	SDL_Rect rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   	SDL_Texture *tx_menu_sc = SDL_CreateTextureFromSurface(rend, menu_sc);
   	SDL_FreeSurface(menu_sc);

   	menu_btns = IMG_Load("resources/menu_buttons.png");
   	if (!menu_btns)
   	{
   	   printf("11%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_menu_btns_home_s;
   	SDL_Rect rect_menu_btns_home_d = (SDL_Rect){W_W/2 - 100, (W_H/6*0)+(12*1), 200, W_H/6};
   	SDL_Rect rect_menu_btns_resume_s;
   	SDL_Rect rect_menu_btns_resume_d = (SDL_Rect){W_W/2 - 100, (W_H/6*1)+(12*2), 200, W_H/6};
   	SDL_Rect rect_menu_btns_restart_s;
   	SDL_Rect rect_menu_btns_restart_d = (SDL_Rect){W_W/2 - 100, (W_H/6*2)+(12*3), 200, W_H/6};
   	SDL_Rect rect_menu_btns_options_s;
   	SDL_Rect rect_menu_btns_options_d = (SDL_Rect){W_W/2 - 100, (W_H/6*3)+(12*4), 200, W_H/6};
   	SDL_Rect rect_menu_btns_exit_s;
   	SDL_Rect rect_menu_btns_exit_d = (SDL_Rect){W_W/2 - 100, (W_H/6*4)+(12*5), 200, W_H/6};
   	SDL_Texture *tx_menu_btns = SDL_CreateTextureFromSurface(rend, menu_btns);
   	SDL_FreeSurface(menu_btns);

   	options_pupop = IMG_Load("resources/options_pupop.png");
   	if (!options_pupop)
   	{
   	   printf("12%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_options_pupop_s;
   	SDL_Rect rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   	SDL_Texture *tx_options_pupop = SDL_CreateTextureFromSurface(rend, options_pupop);
   	SDL_FreeSurface(options_pupop);

   	close_btn = IMG_Load("resources/close_btn.png");
   	if (!close_btn)
   	{
   	   printf("13%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_close_btn_s;
   	SDL_Rect rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   	SDL_Texture *tx_close_btn = SDL_CreateTextureFromSurface(rend, close_btn);
   	SDL_FreeSurface(close_btn);

   	img_player1 = IMG_Load("resources/img_player1.png");
   	if (!img_player1)
   	{
   	   printf("14%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_img_player1_s;
   	SDL_Rect rect_img_player1_d = (SDL_Rect){W_W/5, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   	SDL_Texture *tx_img_player1 = SDL_CreateTextureFromSurface(rend, img_player1);
   	SDL_FreeSurface(img_player1);

   	img_player2 = IMG_Load("resources/img_player2.png");
   	if (!img_player2)
   	{
   	   printf("15%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_img_player2_s;
   	SDL_Rect rect_img_player2_d = (SDL_Rect){W_W-W_W/5-W_W/10, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   	SDL_Texture *tx_img_player2 = SDL_CreateTextureFromSurface(rend, img_player2);
   	SDL_FreeSurface(img_player2);

   	selection_img_player = IMG_Load("resources/selection_img_player.png");
   	if (!selection_img_player)
   	{
   	   printf("16%s", SDL_GetError());
   	   return (1);
   	}

   	SDL_Rect rect_selection_img_player_s;
   	SDL_Rect rect_selection_img_player_d;
   	SDL_Texture *tx_selection_img_player = SDL_CreateTextureFromSurface(rend, selection_img_player);
   	SDL_FreeSurface(selection_img_player);

   	Mix_Music *musique;
   	musique = Mix_LoadMUS("resources/musique.wav");
   	Mix_PlayMusic(musique, -1);

   	Mix_AllocateChannels(2);
   	Mix_Chunk *son1;
   	Mix_Chunk *son2;
   	son1 = Mix_LoadWAV("resources/running.wav");
   	son2 = Mix_LoadWAV("resources/meow.wav");
   	Mix_VolumeChunk(son1, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
   	Mix_VolumeChunk(son2, MIX_MAX_VOLUME);

   	Mix_PlayChannel(0, son1, -1);//Joue le son1 1 sur le canal 1 ; le joue une fois (0 + 1)
   	Mix_Pause(0);

	t_obj	ob_key;
	init_obj(&ob_key, 20*20, 20*20, 20, 820, 1694, "key", SDL_FLIP_NONE, 0.8, 0, 0, key->w);
	//SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_bool is_run = SDL_TRUE;
	SDL_bool minimap = SDL_FALSE;
	SDL_bool texture = SDL_FALSE;
	SDL_bool skybox = SDL_FALSE;
	SDL_Event e;
	while (is_run)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				is_run = SDL_FALSE;
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
            	if (sound_press(e.button) && screen == 2 && options_pupop_showed == 0)
            	{
            	   if(Mix_PausedMusic() == 1) //Si la musique est en pause
            	   {
            	      frame_sound = 0;
            	      Mix_ResumeMusic(); //Reprendre la musique
            	   }
            	   else
            	   {
            	      frame_sound = 1;
            	      Mix_PauseMusic(); //Mettre en pause la musique
            	   }
            	}
				if (play_press(e.button) && screen == 1 && options_pupop_showed == 0)
               		screen = 2;

            	if (menu_icon_press(e.button) && screen != 3 && options_pupop_showed == 0)
            	{
            	   previous_screen = screen;
            	   screen = 3;
            	}
            	else if (menu_icon_press(e.button) && screen == 3 && options_pupop_showed == 0)
            	   screen = previous_screen;
            	if (close_btn_press(e.button) && options_pupop_showed == 1)
            	   options_pupop_showed = 0;
            	img_player_selected = img_player_press(e.button);
            	if (img_player_selected && options_pupop_showed == 1)
            	   player.player_num = img_player_selected;
            	menu_btn_clicked = menu_buttons_press(e.button);
            	if (menu_btn_clicked && screen == 3 && options_pupop_showed == 0)
            	{
            	   	if (menu_btn_clicked == 1)
            	   		screen = 1;
            	   	if (menu_btn_clicked == 2)
            	   	{
					   
            	   	}
            	   	if (menu_btn_clicked == 3)
            	   	{
					   
            	   	}
            	   	if (menu_btn_clicked == 4)
            	   		options_pupop_showed = 1;
            	   	if (menu_btn_clicked == 5)
            			is_run   = SDL_FALSE;
            	}
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					is_run = SDL_FALSE;
				if (e.key.keysym.sym == SDLK_r)
					player_reset(&player);
				if (e.key.keysym.sym == SDLK_m)
					minimap = !minimap;
				if (e.key.keysym.sym == SDLK_t)
					texture = !texture;
				if (e.key.keysym.sym == SDLK_s)
					skybox = !skybox;
			}
			if (e.type == SDL_KEYDOWN)
			{		
				if (e.key.keysym.sym == SDLK_UP)
				{
                  	Mix_Resume(0);
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
                  	Mix_Resume(0);
				}
			}
			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_UP)
				{
					player.frame_player_x = 4;
   					player.frame_player_y = 1;
					Mix_Pause(0);
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					player.frame_player_x = 4;
   					player.frame_player_y = 0;
					Mix_Pause(0);
				}
			}
		}

		SDL_RenderClear(rend);
		if (screen == 1)
      	{
      	   SDL_RenderClear(rend);
      	   rect_welcom_sc_s = (SDL_Rect){0, 0, 612, 344};
      	   rect_wolf3d_s = (SDL_Rect){0, 0, 867, 364};
      	   rect_play_s = (SDL_Rect){0, 0, 313, 159};
      	   rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   SDL_RenderCopyEx(rend, tx_welcom_sc, &rect_welcom_sc_s, &rect_welcom_sc_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_wolf3d, &rect_wolf3d_s, &rect_wolf3d_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_play, &rect_play_s, &rect_play_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      	}
		if (screen == 2)
      	{
      	   	SDL_RenderClear(rend);
			update(&player, rend);
			render(rend, skybox, texture, minimap, &player, image, floor, sky, ceil, tx_key, ob_key);
      	   	rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   	rect_sound_s = (SDL_Rect){752 * frame_sound, 0, 752, 774};
      	   	rect_player_s = (SDL_Rect){100 * player.frame_player_x, 100 * player.frame_player_y, 100, 100};
      	   	SDL_RenderCopyEx(rend, tx_icon, &rect_sound_s, &rect_sound_d, 0, NULL, SDL_FLIP_NONE);
      	   	if (player.player_num == 1)
      	   	   SDL_RenderCopyEx(rend, tx_player1, &rect_player_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
      	   	else
      	   	   SDL_RenderCopyEx(rend, tx_player2, &rect_player_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
      	   	SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      	}
		if (screen == 3)
      	{
      	   SDL_RenderClear(rend);
      	   rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
      	   rect_menu_sc_s = (SDL_Rect){0, 0, 800, 600};
      	   rect_menu_btns_home_s = (SDL_Rect){0, 0, 281, 137};
      	   rect_menu_btns_resume_s = (SDL_Rect){0, 1*137, 281, 137};
      	   rect_menu_btns_restart_s = (SDL_Rect){0, 2*137, 281, 137};
      	   rect_menu_btns_options_s = (SDL_Rect){0, 3*137, 281, 137};
      	   rect_menu_btns_exit_s = (SDL_Rect){0, 4*137, 281, 137};
      	   SDL_RenderCopyEx(rend, tx_menu_sc, &rect_menu_sc_s, &rect_menu_sc_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_home_s, &rect_menu_btns_home_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_resume_s, &rect_menu_btns_resume_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_restart_s, &rect_menu_btns_restart_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_options_s, &rect_menu_btns_options_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_menu_btns, &rect_menu_btns_exit_s, &rect_menu_btns_exit_d, 0, NULL, SDL_FLIP_NONE);
      	}
		if (options_pupop_showed == 1)
      	{
      	   rect_options_pupop_s = (SDL_Rect){0, 0, 771, 638};
      	   rect_close_btn_s = (SDL_Rect){0, 0, 300, 300};
      	   rect_img_player1_s = (SDL_Rect){0, 0, 52, 92};
      	   SDL_RenderCopyEx(rend, tx_options_pupop, &rect_options_pupop_s, &rect_options_pupop_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_close_btn, &rect_close_btn_s, &rect_close_btn_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_img_player1, &rect_img_player1_s, &rect_img_player1_d, 0, NULL, SDL_FLIP_NONE);
      	   SDL_RenderCopyEx(rend, tx_img_player2, &rect_img_player1_s, &rect_img_player2_d, 0, NULL, SDL_FLIP_NONE);
      	   if (player.player_num == 1)
      	      rect_selection_img_player_d = rect_img_player1_d;
      	   else
      	      rect_selection_img_player_d = rect_img_player2_d;
      	   SDL_RenderCopyEx(rend, tx_selection_img_player, &rect_img_player1_s, &rect_selection_img_player_d, 0, NULL, SDL_FLIP_NONE);
      	}
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	Mix_FreeChunk(son1);//Libération du son 1
   	Mix_FreeChunk(son2);
	Mix_FreeMusic(musique); //Libération de la musique
	SDL_DestroyTexture(tx_icon);
   	SDL_DestroyTexture(tx_player1);
   	SDL_DestroyTexture(tx_player2);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}