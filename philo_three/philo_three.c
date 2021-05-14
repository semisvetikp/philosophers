/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:30:48 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 01:24:32 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	while (1)
	{
		eating(ph->phtable, ph);
		++ph->ate;
		if (ph->ate == ph->cnteat)
		{
			ph->tstarteat = -1;
			exit(0);
		}
		print(ph->phtable, ph, 2);
		mysleep(ph->phtable->tsleep, ph);
		print(ph->phtable, ph, 3);
	}
	return (NULL);
}

int	start(t_table *table, t_philo *philos)
{
	int	ret;

	ret = pthread_create(&(philos->t), NULL, doit, (void *)philos);
	if (ret != 0)
		exit(1);
	while (1)
	{
		sem_wait(table->semprint);
		gettimeofday(&table->ttv, NULL);
		table->timed = (table->ttv.tv_sec *1000000 + table->ttv.tv_usec)
			/ 1000 - table->tstart;
		table->timesub = table->timed - philos->tstarteat;
		if (philos->tstarteat != -1 && table->timesub > table->tdie)
		{
			sem_wait(philos->semeat);
			printf("%d %d died\n", table->timed, philos->number);
			sem_post(philos->semeat);
			sem_unlink("/semtable");
			sem_unlink("/semprint");
			sem_unlink(philos->semeat_name);
			exit(1);
		}
		sem_post(table->semprint);
	}
	return (0);
}

int	waitdie(t_table *table)
{
	int	status;
	int	j;

	while (1)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			j = -1;
			while (++j < table->forks)
				kill(table->pids[j], 9);
			return (1);
		}
		if (WEXITSTATUS(status) == 0)
			++table->cnt_ate_philo;
		if (table->cnt_ate_philo == table->forks)
			return (0);
	}
}

int	create(t_table *table, t_philo **philos)
{
	int				i;
	struct timeval	tv;

	i = -1;
	sem_unlink("/semprint");
	sem_unlink("/semtable");
	table->semprint = sem_open("/semprint", O_CREAT, 0666, 1);
	table->semtable = sem_open("/semtable", O_CREAT, 0666, table->forks);
	if (table->semprint == SEM_FAILED)
		exit(1);
	gettimeofday(&tv, NULL);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
			start(table, philos[i]);
		usleep(10);
	}
	waitdie(table);
	return (0);
}
