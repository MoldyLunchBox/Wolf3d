/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:18:39 by yzemmour          #+#    #+#             */
/*   Updated: 2022/05/16 10:18:41 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void draw_square(SDL_Renderer *rend, int size, int x, int y)
{
	int ix = x-size/2;
	int iy = y-size/2;
	for (int i = 0; i<size; i++)
	{
		SDL_RenderDrawLine(rend, ix, iy, ix+size, iy);
		iy++;
	}
}

void cursor_mouse(t_envirenment *env)
{
	if (env->screen == 2 && env->cursor)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}

void    create_obj(t_obj *obj)
{
    obj = (t_obj*)malloc(sizeof(t_obj));
}