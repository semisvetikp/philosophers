/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 12:15:24 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <stdlib.h>

void	eating(t_table *table, t_philo *ph)
{
	pthread_mutex_lock(table->mutex[ph->number - 1]);
	if (ph->number != table->forks)
		pthread_mutex_lock(table->mutex[ph->number]);
	else
		pthread_mutex_lock(table->mutex[0]);
	pthread_mutex_lock(&ph->eat);
	gettimeofday(&ph->tv, NULL);
	ph->tstarteat = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec)
		/ 1000 - table->tstart;
	print(table, ph, 1);
	pthread_mutex_unlock(&ph->eat);
	mysleep(table->teat, ph);
	if (ph->number != table->forks)
		pthread_mutex_unlock(table->mutex[ph->number]);
	else
		pthread_mutex_unlock(table->mutex[0]);
	pthread_mutex_unlock(table->mutex[ph->number - 1]);
}

void	*doit(void *phil)
{
	t_philo	*ph;

	ph = (t_philo *)phil;
	while (ph->phtable->flag == 1)
	{
		eating(ph->phtable, ph);
		++ph->ate;
		if (ph->ate == ph->cnteat)
		{
			++ph->phtable->cnt_ate_philo;
			ph->tstarteat = -1;
			break ;
		}
		print(ph->phtable, ph, 2);
		mysleep(ph->phtable->tsleep, ph);
		print(ph->phtable, ph, 3);
	}
	return (NULL);
}

int	look_timedie(t_table *table, t_philo **philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->forks)
		{
			gettimeofday(&table->ttv, NULL);
			table->timed = (table->ttv.tv_sec *1000000 + table->ttv.tv_usec)
				/ 1000 - table->tstart;
			table->timesub = table->timed - philos[i]->tstarteat;
			if (philos[i]->tstarteat != -1 && table->timesub > table->tdie)
			{
				pthread_mutex_lock(&philos[i]->eat);
				table->flag = 0;
				print(table, philos[i], 4);
				pthread_mutex_unlock(&philos[i]->eat);
				return (0);
			}
			if (table->cnt_ate_philo == table->forks)
				return (0);
		}
	}
	return (0);
}

int	create(t_table *table, t_philo **philos)
{
	int				i;
	struct timeval	tv;
	int				ret;

	i = -1;
	pthread_mutex_init(&table->print, NULL);
	gettimeofday(&tv, NULL);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
	{
		ret = pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
		if (ret != 0)
			return (1);
		usleep(10);
	}
	look_timedie(table, philos);
	i = -1;
	while (++i < table->forks)
		pthread_join(philos[i]->t, NULL);
	return (0);
}
