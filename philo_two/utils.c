/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:24:56 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 00:19:36 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	zero_param(char **argv)
{
	int	a;
	int	i;

	i = 0;
	while (argv[++i] != NULL)
	{
		a = ft_atoi(argv[i]);
		if (a == 0 )
		{
			write(2, "Invalid arguments: zero\n", 24);
			return (1);
		}
	}
	return (0);
}

int	handling_error(int argc, char **argv)
{
	int	i;
	int	k;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error number of arguments.\n", 27);
		return (1);
	}
	while (argv[++i] != NULL)
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][k] > 57 || argv[i][k] < 48 )
			{
				write(2, "Invalid arguments.\n", 19);
				return (1);
			}
			++k;
		}
	}
	return (0);
}

void	mysleep(int time, t_philo *ph)
{
	ph->t_slp = 0;
	gettimeofday(&ph->tv, NULL);
	ph->time1_slp = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec) / 1000;
	while (ph->t_slp < (time))
	{
		usleep(50);
		gettimeofday(&ph->tv, NULL);
		ph->time2_slp = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec) / 1000;
		ph->t_slp = ph->time2_slp - ph->time1_slp;
	}
}

void	print(t_table *table, t_philo *ph, int a)
{
	sem_wait(table->semprint);
	if (table->flag == 0 && a != 4)
	{
		sem_post(table->semprint);
		return ;
	}
	gettimeofday(&ph->tvp, NULL);
	ph->time_prnt = (ph->tvp.tv_sec *1000000 + ph->tvp.tv_usec)
		/ 1000 - table->tstart;
	if (a == 1)
	{
		printf("%d %d has taken a fork\n", ph->time_prnt, ph->number);
		printf("%d %d is eating\n", ph->time_prnt, ph->number);
	}
	else if (a == 2)
		printf("%d %d is sleeping\n", ph->time_prnt, ph->number);
	else if (a == 3)
		printf("%d %d is thinking\n", ph->time_prnt, ph->number);
	else if (a == 4)
		printf("%d %d died\n", table->timed, ph->number);
	sem_post(table->semprint);
}
