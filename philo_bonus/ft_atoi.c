/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 02:10:56 by jainavas          #+#    #+#             */
/*   Updated: 2024/08/12 02:10:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	minus;

	i = spaces(str);
	minus = 0;
	res = 0;
	if (str[i] == '-')
	{
		minus++;
		i++;
	}
	else
		if (str[i] == '+')
			i++;
	while (ft_isdigit((int)str[i]) == 1)
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (minus % 2 == 1)
		res = -res;
	return (res);
}
