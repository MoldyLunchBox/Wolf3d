#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "wolf3d.h"

#define PI 3.1415926535
#define mapX 24	//map width
#define mapY 24
#define wallPadding 10
#define cellS 20 //map cube size
#define mapS mapX * cellS
#define WALL_H 50

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
	player->speed = 5;
	player->fov = 60.0;
}

void update(t_player *player, SDL_Renderer *rend)
{
	const uint8_t* keys = SDL_GetKeyboardState(NULL);

	float dx = 0.0f, dy = 0.0f;

	if (keys[SDL_SCANCODE_DOWN])
    {
		dx -= cos(player->a);
        dy += sin(player->a);
	}
	if (keys[SDL_SCANCODE_UP])
    {
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
				x0+=600;
			x0=x0%600;
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

	/****************************** END-VARIABLES ****************************/
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return (1);
    }
	SDL_Window *window = SDL_CreateWindow(
		"Wolf3D",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W_W,
		W_H,
		0);
	if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (rend == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
	/************************ load textures **********************************/ 
	SDL_Surface *wall = IMG_Load("resources/wall.png");
	SDL_Surface *door = IMG_Load("resources/door1.jpg");
	SDL_Surface *floor = IMG_Load("resources/floor.png");
	SDL_Surface *ceil = IMG_Load("resources/ceil.png");
	SDL_Surface *sky = IMG_Load("resources/sky.png");
	SDL_Surface *key = IMG_Load("resources/pillar.png");

	SDL_Surface *image[2];

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
	t_obj	ob_key;
	init_obj(&ob_key, 20*20, 20*20, 20, 820, 1694, "key", SDL_FLIP_NONE, 0.8, 0, 0, key->w);
	//SDL_SetRenderDrawColor(rend, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_bool is_run = SDL_TRUE;
	SDL_bool minimap = SDL_FALSE;
	SDL_bool texture = SDL_FALSE;
	SDL_bool skybox = SDL_FALSE;
	while (is_run)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				is_run = SDL_FALSE;
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
		}
		SDL_RenderClear(rend);
		update(&player, rend);
		render(rend, skybox, texture, minimap, &player, image, floor, sky, ceil, tx_key, ob_key);
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}