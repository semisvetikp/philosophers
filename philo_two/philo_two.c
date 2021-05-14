/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 00:50:38 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	died_ate(t_table *table, t_philo **philos, int i)
{
	if (philos[i]->tstarteat != -1 && table->timesub > table->tdie)
	{
		sem_wait(philos[i]->semeat);
		table->flag = 0;
		print(table, philos[i], 4);
		sem_post(philos[i]->semeat);
		sem_unlink("/semtable");
		sem_unlink("/semprint");
		sem_unlink(philos[i]->semeat_name);
		return (1);
	}
	if (table->cnt_ate_philo == table->forks)
	{
		sem_unlink("/semtable");
		sem_unlink("/semprint");
		sem_unlink(philos[i]->semeat_name);
		return (1);
	}
	return (0);
}

void	eating(t_table *table, t_philo *ph)
{
	sem_wait(table->semtable);
	sem_wait(table->semtable);
	sem_wait(ph->semeat);
	gettimeofday(&ph->tv, NULL);
	ph->tstarteat = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec)
		/ 1000 - ph->phtable->tstart;
	print(ph->phtable, ph, 1);
	sem_post(ph->semeat);
	mysleep(ph->phtable->teat, ph);
	sem_post(table->semtable);
	sem_post(table->semtable);
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
			if (died_ate(table, philos, i))
				return (1);
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
		return (1);
	gettimeofday(&tv, NULL);
	while (++i < table->forks)
		pthread_detach(philos[i]->t);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	i = -1;
	while (++i < table->forks)
	{
		ret = pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
		if (ret != 0)
			return (1);
		usleep(20);
	}
	look_timedie(table, philos);
	return (0);
}
