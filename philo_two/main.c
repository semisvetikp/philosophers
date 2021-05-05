/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:33:05 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/06 00:58:09 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_philo	**init_philosophers(char **argv, t_table *table)
{
	int		i;
	int		number;
	t_philo	**philos;

	i = 0;
	number = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo *) * number);
	if (philos == NULL)
		return (NULL);
	while (i < number)
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
		++i;
	}
	return (philos);
}

t_philo	**init_table(char **argv, t_table *table)
{
	int		i;
	int		number;
	t_philo	**philos;

	i = 0;
	number = ft_atoi(argv[1]);
	table->forks = number;
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

	if (handling_error(argc, argv))
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
