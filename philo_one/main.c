/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:33:05 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 00:31:23 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_one.h"

t_philo	**init_philosophers(char **argv, t_table *table)
{
	int		i;
	int		number;
	t_philo	**philos;

	i = -1;
	number = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo *) * number);
	if (philos == NULL)
		return (NULL);
	while (++i < number)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		philos[i]->phtable = table;
		philos[i]->tstarteat = -1;
		philos[i]->number = i + 1;
		if (argv[5] != NULL)
			philos[i]->cnteat = ft_atoi(argv[5]);
		philos[i]->ate = 0;
		pthread_mutex_init(&philos[i]->eat, NULL);
	}
	table->flag = 1;
	return (philos);
}

t_philo	**init_table(char **argv, t_table *table)
{
	int		i;
	int		number;
	t_philo	**philos;

	i = 0;
	number = ft_atoi(argv[1]);
	table->mutex = malloc(sizeof(pthread_mutex_t *) * number);
	if (table->mutex == NULL)
		return (NULL);
	table->forks = number;
	while (i < number)
	{
		table->mutex[i] = malloc(sizeof(pthread_mutex_t));
		if (table->mutex[i] == NULL)
			return (NULL);
		pthread_mutex_init(table->mutex[i], NULL);
		++i;
	}
	table->tdie = ft_atoi(argv[2]);
	table->teat = ft_atoi(argv[3]);
	table->tsleep = ft_atoi(argv[4]);
	table->cnt_ate_philo = 0;
	philos = init_philosophers(argv, table);
	return (philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	**philos;

	if (handling_error(argc, argv) || zero_param(argv))
		return (1);
	philos = init_table(argv, &table);
	if (philos == NULL)
	{
		write(2, "Malloc can't allocate memory.\n", 30);
		return (1);
	}
	create(&table, philos);
	return (0);
}
