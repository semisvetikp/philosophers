/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:58:55 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/06 00:57:51 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_table
{
	sem_t			*semtable;
	sem_t			*semprint;
	int				forks;
	int				tdie;
	int				teat;
	int				tsleep;
	int				tstart;
	struct timeval	ttv;
	int				timed;
	int				timesub;
	int				cnt_ate_philo;
}				t_table;

typedef struct s_philo
{
	int				number;
	pthread_t		t;
	struct timeval	tv;
	t_table			*phtable;
	int				tstarteat;
	int				cnteat;
	int				ate;
}				t_philo;

int		handling_error(int argc, char **argv);
int		ft_atoi(const char *str);
t_philo	**init_table(char **argv, t_table *table);
t_philo	**init_philosophers(char **argv, t_table *table);
int		create(t_table *table, t_philo	**philos);
void	mysleep(int time);
void	print(t_table *table, t_philo *philo, int a);

#endif