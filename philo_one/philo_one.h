/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:58:55 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/29 01:08:03 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table
{
	pthread_mutex_t	**mutex;
	int	forks;
	int tdie;
	int teat;
	int tsleep;
	int	cnteat;
}				t_table;

typedef struct s_philo
{
	int	number;
	pthread_t	t;
	t_table	*phtable;
}				t_philo;

// typedef struct s_all
// {
// 	t_philo	**philos;
// 	t_table	*phtable;
// 	pthread_mutex_t	mutex;
// }				t_all;

int	handling_error(int argc, char **argv);
int	ft_atoi(const char *str);
int	init(char **argv);

#endif