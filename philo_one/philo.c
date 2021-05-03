/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/04 02:28:20 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <stdlib.h>

t_philo **init(char **argv, t_table *table)
{
	int		i;
	int		number;
	t_philo	**philos;

	i = 0;
	number = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo *) * number);
	table->mutex = malloc(sizeof(pthread_mutex_t *) * number);
	if (philos == NULL || table->mutex == NULL)
		return(NULL);
	table->forks = number;
	while (i < number)
	{
		philos[i] = malloc(sizeof(t_philo));
		table->mutex[i] = malloc(sizeof(pthread_mutex_t));
		philos[i]->phtable = table;
		philos[i]->tstarteat = -1;
		pthread_mutex_init(table->mutex[i], NULL);
		++i;
	}
	i = -1;
	while (++i < number)
		philos[i]->number = i + 1;
	table->tdie = ft_atoi(argv[2]);
	table->teat = ft_atoi(argv[3]);
	table->tsleep = ft_atoi(argv[4]);
	create(table, philos);
	return (philos);
}

void mysleep(int time)
{
	int time1;
	int time2;
	struct timeval tv;
	struct timezone tz;
	int t;

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
	// printf("t:%d\n", t);
}


void print(t_table *table, t_philo *philo, int a)
{
	struct timeval tv;
	int time;
	
	pthread_mutex_lock(&table->print);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec *1000000 + tv.tv_usec) / 1000 - table->tstart;
	if ( a == 1)
	{
		printf("%d %d has taken a fork\n", time, philo->number);
		printf("%d %d is eating\n", time, philo->number);
	}
	if ( a == 2)
		printf("%d %d is sleeping\n", time, philo->number);
	if ( a == 3)
		printf("%d %d is thinking\n", time, philo->number);
	pthread_mutex_unlock(&table->print);
}


void *doit(void *phil)
{
	t_philo *ph;

	ph = (t_philo *)phil;
	while (1)
	{
		pthread_mutex_lock(ph->phtable->mutex[ph->number - 1]);
		if (ph->number != ph->phtable->forks)
			pthread_mutex_lock(ph->phtable->mutex[ph->number]);
		else
			pthread_mutex_lock(ph->phtable->mutex[0]);
		gettimeofday(&ph->tv, NULL);
		ph->ts_eat = (ph->tv.tv_sec *1000000 + ph->tv.tv_usec) / 1000 - ph->phtable->tstart;
		print(ph->phtable, ph, 1);
		mysleep(ph->phtable->teat);
		if (ph->number != ph->phtable->forks)
			pthread_mutex_unlock(ph->phtable->mutex[ph->number]);
		else
			pthread_mutex_unlock(ph->phtable->mutex[0]);
		pthread_mutex_unlock(ph->phtable->mutex[ph->number - 1]);
		print(ph->phtable, ph, 2);
		mysleep(ph->phtable->tsleep);
		print(ph->phtable, ph, 3);
	}
	return NULL;
}

int create(t_table *table, t_philo **philos)
{
	int i;
	struct timeval tv;
	int timed;

	i = -1;
	pthread_mutex_init(&table->print, NULL);
	gettimeofday(&tv, NULL);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
		pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
	while(1)
	{
		i = 0;
		while (i < table->forks)
		{
			gettimeofday(&tv, NULL);
			timed = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
			timed = timed - table->tstart - philos[i]->tstarteat;
			if (philos[i]->tstarteat != -1 && timed > table->tdie)
			{
				pthread_mutex_lock(&table->print);
				printf("%d %d died\n", timed, philos[i]->number);
				exit(1);				
			}
			i++;
		}
	}
	return (0);
}
