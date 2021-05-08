/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:24:56 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/08 12:19:36 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	handling_error(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error number of arguments.\n", 27);
		return (1);
	}
	while (argv[i] != NULL)
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][k] > 57 || argv[i][k] < 48)
			{
				write(2, "Invalid arguments.\n", 19);
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

void	mysleep(int time)
{
	int				time1;
	int				time2;
	struct timeval	tv;
	struct timezone	tz;
	int				t;

	t = 0;
	gettimeofday(&tv, &tz);
	time1 = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (t < (time))
	{
		usleep(50);
		gettimeofday(&tv, &tz);
		time2 = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
		t = time2 - time1;
	}
}

void	print(t_table *table, t_philo *philo, int a)
{
	struct timeval	tv;
	int				time;

	sem_wait(table->semprint);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec *1000000 + tv.tv_usec) / 1000 - table->tstart;
	if (a == 1)
	{
		printf("%d %d has taken a fork\n", time, philo->number);
		printf("%d %d is eating\n", time, philo->number);
	}
	if (a == 2)
		printf("%d %d is sleeping\n", time, philo->number);
	if (a == 3)
		printf("%d %d is thinking\n", time, philo->number);
	sem_post(table->semprint);
}
