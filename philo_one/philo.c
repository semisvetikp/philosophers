/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:34:51 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/29 01:20:45 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init(char **argv)
{
	int		i;
	int		number;
	t_table	table;
	t_philo	**philos;

	i = 0;
	number = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo *) * number);
	table.forks = number;
	while (i < number)
	{
		pthread_mutex_init(table.mutex[i], NULL);
		++i;
	}
	i = -1;
	while (++i < number)
		philos[i]->number = i + 1;
	table.tdie = ft_atoi(argv[2]);
	table.teat = ft_atoi(argv[3]);
	table.tsleep = ft_atoi(argv[4]);
	return (0);
}
