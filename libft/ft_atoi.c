/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:30:58 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/20 12:16:17 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		si;

	i = 0;
	res = 0;
	si = 1;
	str = (char*)str;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		si = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * si);
}
