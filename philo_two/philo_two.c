/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/06 01:20:27 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	unlink_exit(void)
{
	sem_unlink("/semtable");
	sem_unlink("/semprint");
	exit(1);
}

void	*doit(void *phil)
{
	t_philo	*ph;

	ph = (t_philo *)phil;
	while (1)
	{
		sem_wait(ph->phtable->semtable);
		sem_wait(ph->phtable->semtable);
		gettimeofday(&ph->tv, NULL);
		ph->tstarteat = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec)
			/ 1000 - ph->phtable->tstart;
		print(ph->phtable, ph, 1);
		mysleep(ph->phtable->teat);
		sem_post(ph->phtable->semtable);
		sem_post(ph->phtable->semtable);
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
				sem_post(table->semprint);
				printf("%d %d died\n", table->timed, philos[i]->number);
				unlink_exit();
			}
			if (table->cnt_ate_philo == table->forks)
				unlink_exit();
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
	sem_unlink("/semtable");
	sem_unlink("/semprint");
	table->semtable = sem_open("/semtable", O_CREAT, 0666, table->forks);
	table->semprint = sem_open("/semprint", O_CREAT, 0666, 1);
	if (table->semtable == SEM_FAILED || table->semprint == SEM_FAILED)
		exit(1);
	gettimeofday(&tv, NULL);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
	{
		ret = pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
		if (ret != 0)
			exit(1);
		usleep(10);
	}
	look_timedie(table, philos);
	return (0);
}
