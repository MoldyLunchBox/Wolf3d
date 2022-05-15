/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:21:04 by amya              #+#    #+#             */
/*   Updated: 2022/05/15 17:23:01 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_exit(char *msg)
{
	ft_putendl(msg);
	exit(1);
}


void	fill_map_line(char **ar, t_envirenment *env, int start)
{
	int i;

	i = 0;
	while (ar[i])
	{
		if ((!ft_atoi(ar[i]) && ft_strcmp(ar[i], "0")) || ft_atoi(ar[i]) < 0)
			error_exit("map must include strickly numbers");
		env->map[start] = ft_atoi(ar[i]);
		if (env->map[start] == 2)
		{
			if(env->door_position == -1)
				env->door_position = start;
			else
				error_exit("there must only be one door");
		}
		i++;
		start++;
	}
}

int	ft_size_of_2d(char **test)
{
	int i = 0;
	while (test[i])
		i++;
	return i;
}

void	parsing(t_envirenment *env, char *file)
{
	char *line;
	int	fd;
	char **ar;
	int i = 0;
	int elems;
	env->map_size = 0;
	env->door_position = -1;

	elems = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("map file cant be opened");
	while(get_next_line(fd, &line) > 0)
	{
		ar = ft_strsplit(line, ' ');
		if (elems  == 0)
		{
			env->map_size = ft_size_of_2d(ar);
			if (env->map_size <= 3)
				error_exit("map dimenssions must be atleast 3X3");
			env->map = (int *)malloc(sizeof(int) * env->map_size * env->map_size);
		}
		else
		{
			if (env->map_size != ft_size_of_2d(ar))
				error_exit("all lines must have identical lengths");
		}
		fill_map_line(ar, env, elems * env->map_size);
		elems++;
	}
	close(fd);
	if (elems != env->map_size || env->map_size == 0)
		error_exit("map length and height must be identical and atleast 3X3");
}
