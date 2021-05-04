/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/05 02:38:21 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <stdlib.h>

// void	eat_and_sleep(t_table *table, t_philo *philos)
// {

// }

void	*doit(void *phil)
{
	t_philo	*ph;

	ph = (t_philo *)phil;
	while (1)
	{
		// eat_and_sleep(ph->phtable, ph);
		pthread_mutex_lock(ph->phtable->mutex[ph->number - 1]);
		if (ph->number != ph->phtable->forks)
			pthread_mutex_lock(ph->phtable->mutex[ph->number]);
		else
			pthread_mutex_lock(ph->phtable->mutex[0]);
		gettimeofday(&ph->tv, NULL);
		ph->tstarteat = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec)
			/ 1000 - ph->phtable->tstart;
		print(ph->phtable, ph, 1);
		mysleep(ph->phtable->teat);
		if (ph->number != ph->phtable->forks)
			pthread_mutex_unlock(ph->phtable->mutex[ph->number]);
		else
			pthread_mutex_unlock(ph->phtable->mutex[0]);
		pthread_mutex_unlock(ph->phtable->mutex[ph->number - 1]);
		++ph->ate;
		if (ph->ate == ph->cnteat)
		{
			++ph->phtable->cnt_ate_philo;
			break ;
		}
		print(ph->phtable, ph, 2);
		mysleep(ph->phtable->tsleep);
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
				pthread_mutex_lock(&table->print);
				printf("%d %d died\n", table->timed, philos[i]->number);
				exit(1);
			}
			if (table->cnt_ate_philo == table->forks)
				exit(1);
		}
	}
	return (0);
}

int	create(t_table *table, t_philo **philos)
{
	int				i;
	struct timeval	tv;

	i = -1;
	pthread_mutex_init(&table->print, NULL);
	gettimeofday(&tv, NULL);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
		pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
	look_timedie(table, philos);
	return (0);
}
