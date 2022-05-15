/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:25:14 by amya              #+#    #+#             */
/*   Updated: 2022/05/15 17:25:22 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void load_walls(t_envirenment *env)
{
	env->walls[0] = IMG_Load("resources/images/walls/wall.png");
	env->walls[1] = IMG_Load("resources/images/walls/wall_code.png");
	env->walls[2] = IMG_Load("resources/images/walls/wall_9.png");
	env->walls[3] = IMG_Load("resources/images/walls/wall_1.png");
	env->walls[4] = IMG_Load("resources/images/walls/wall_2.png");
	env->walls[5] = IMG_Load("resources/images/walls/wall_3.png");
	env->walls[6] = IMG_Load("resources/images/walls/wall_4.png");
	env->walls[7] = IMG_Load("resources/images/walls/wall_5.png");
	env->walls[8] = IMG_Load("resources/images/walls/wall_6.png");
	env->walls[9] = IMG_Load("resources/images/walls/wall_7.png");
	env->walls[10] = IMG_Load("resources/images/walls/wall_8.png");
	env->walls[11] = IMG_Load("resources/images/walls/wall_key.png");
	env->walls[12] = IMG_Load("resources/images/walls/wall_10.png");
	env->walls[13] = IMG_Load("resources/images/walls/wall_11.png");
	env->quit[0] = IMG_Load("resources/images/walls/quit1.png");
	env->quit[1] = IMG_Load("resources/images/walls/quit2.png");
	env->quit[2] = IMG_Load("resources/images/walls/quit3.png");
	env->quit[3] = IMG_Load("resources/images/walls/quit4.png");
}

void load_doors(t_envirenment *env)
{
	env->doors[0] = IMG_Load("resources/images/doors/door.png");
	env->doors[1] = IMG_Load("resources/images/doors/door1.png");
	env->doors[2] = IMG_Load("resources/images/doors/door2.png");
	env->doors[3] = IMG_Load("resources/images/doors/door3.png");
	env->doors[4] = IMG_Load("resources/images/doors/door4.png");
	env->doors[5] = IMG_Load("resources/images/doors/door5.png");
	env->doors[6] = IMG_Load("resources/images/doors/door6.png");
}

void load_shoots(t_envirenment *env)
{
	env->shoots[0] = IMG_Load("resources/images/shoot/shoot1.png");
	env->shoots[1] = IMG_Load("resources/images/shoot/shoot2.png");
	env->shoots[2] = IMG_Load("resources/images/shoot/shoot3.png");
	env->shoots[3] = IMG_Load("resources/images/shoot/shoot4.png");
	env->shoots[4] = IMG_Load("resources/images/shoot/shoot5.png");
	env->shoots[5] = IMG_Load("resources/images/shoot/shoot6.png");
	env->shoots[6] = IMG_Load("resources/images/shoot/shoot7.png");
	env->shoots[7] = IMG_Load("resources/images/shoot/shoot8.png");
	env->shoots[8] = IMG_Load("resources/images/shoot/shoot9.png");
}

void load_sprites(t_envirenment *env)
{
	env->sprites[0] = IMG_Load("resources/images/sprites/pillar.png");
	env->sprites[1] = IMG_Load("resources/images/sprites/trash.png");
	env->sprites[2] = IMG_Load("resources/images/sprites/enemy.png");
	env->sprites[3] = IMG_Load("resources/images/sprites/coin.png");
	env->sprites[4] = IMG_Load("resources/images/sprites/table.png");
	env->sprites[5] = IMG_Load("resources/images/sprites/aid_kit.png");
	env->sprites[6] = IMG_Load("resources/images/sprites/barrel.png");
	env->sprites[7] = IMG_Load("resources/images/sprites/lamp.png");
}
