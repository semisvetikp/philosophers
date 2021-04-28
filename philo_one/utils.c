/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:24:56 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/28 20:27:42 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	handling_error(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Error number of arguments.\n");
		return (1);
	}
	while (argv[i] != NULL)
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][k] > 57 || argv[i][k] < 48)
			{
				printf("Invalid arguments.\n");
				return (1);
			}
			k++;
		}
		i++;
	}
	return (0);
}

static int	ft_p(int flag)
{
	if (flag == -1)
		return (0);
	else if (flag == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	flag;
	int	res;
	int	p;

	flag = 1;
	res = 0;
	p = 0;
	while ((*str == ' ') || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -flag;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		p++;
		str++;
		if (p > 19)
			return (ft_p(flag));
	}
	return (res * flag);
}
