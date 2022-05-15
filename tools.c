/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:18:41 by amya              #+#    #+#             */
/*   Updated: 2022/05/15 17:18:53 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

float dtor(float d)
{
    return (d * PI / 180.0f);
}

void write_text(SDL_Renderer *rend, TTF_Font *font, char *str, int x, int y)
{
	SDL_Color color;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Rect Message_rect;

	color = (SDL_Color){200, 100, 0, 255};
	surfaceMessage = TTF_RenderText_Blended(font, str, color); 
	Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;
	SDL_RenderCopy(rend, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void fadding(t_envirenment *env)
{
	SDL_Rect r;

	if (env->fade > 0)
	{
		SDL_SetRenderDrawBlendMode(env->rend, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(env->rend, 0, 0 ,0, env->fade);
		r = (SDL_Rect){0, 0, W_W, W_H};
		SDL_RenderFillRect(env->rend, &r);
		env->fade -= 10;
	}
}

float safe_angle(float a)
{
	if (a > 2*PI)
		a -= 2*PI;
	if (a < 0)
		a += 2*PI;
	return (a);
}

float safe_angle_180(float a)
{
	if (a > PI)
		a -= PI;
	if (a < -PI)
		a += PI;
	return (a);
}