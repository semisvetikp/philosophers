/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/02 01:02:07 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	time1 = (tv.tv_sec *1000000 + tv.tv_usec);
	while (t < (time * 1000))
	{
		usleep(50);
		gettimeofday(&tv, &tz);
		time2 = (tv.tv_sec *1000000 + tv.tv_usec);
		t = time2 - time1;
	}
	// printf("t:%d\n", t);
}


void *doit(void *phil)
{
	int t;
	t_philo ph;
	struct timeval tv;
	struct timezone tz;

	ph = *(t_philo *)phil;
	t = ph.phtable->timestamp;
	while (1)
	{
		gettimeofday(&tv, &tz);
		t = (tv.tv_sec *1000000 + tv.tv_usec) / 1000 - ph.phtable->tstart;
		if (t - ph.tstarteat > ph.phtable->tdie)
		{
			printf("%d #%d died\n", t, ph.number);
			exit(1);
		}
		printf("%d #%d is thinking\n", t, ph.number);
		pthread_mutex_lock(ph.phtable->mutex[ph.number - 1]);
		if (ph.number != ph.phtable->forks)
			pthread_mutex_lock(ph.phtable->mutex[ph.number]);
		else
			pthread_mutex_lock(ph.phtable->mutex[0]);
		gettimeofday(&tv, &tz);
		t = (tv.tv_sec *1000000 + tv.tv_usec) / 1000 - ph.phtable->tstart;
		ph.tstarteat = t;
		mysleep(ph.phtable->teat);
		printf("%d #%d is eating\n", t, ph.number);
		if (ph.number != ph.phtable->forks)
			pthread_mutex_unlock(ph.phtable->mutex[ph.number]);
		else
			pthread_mutex_unlock(ph.phtable->mutex[0]);
		pthread_mutex_unlock(ph.phtable->mutex[ph.number - 1]);
		gettimeofday(&tv, &tz);
		t = (tv.tv_sec *1000000 + tv.tv_usec) / 1000 - ph.phtable->tstart;
		printf("%d #%d is sleeping\n", t, ph.number);
		mysleep(ph.phtable->teat);
	}
	return NULL;
}

int create(t_table *table, t_philo **philos)
{
	int i;
	struct timeval tv;
	struct timezone tz;

	i = -1;
	// printf("die:%d\n", philos[2]->phtable->tdie);
	gettimeofday(&tv, &tz);
	table->tstart = (tv.tv_sec *1000000 + tv.tv_usec) / 1000;
	while (++i < table->forks)
	{
		pthread_create(&(philos[i]->t), NULL, doit, (void *)philos[i]);
		// mysleep(500);
	}
	while(1)
		continue;
	return (0);
}
