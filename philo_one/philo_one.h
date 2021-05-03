/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:58:55 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/03 16:47:49 by jradioac         ###   ########.fr       */
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
	pthread_mutex_t print;
	int	forks;
	int tdie;
	int teat;
	int tsleep;
	int	cnteat;
	int timestamp;
	int tstart;
}				t_table;

typedef struct s_philo
{
	int	number;
	pthread_t	t;
	struct timeval tv;
	t_table	*phtable;
	int tstarteat;
	int ts_eat;
	int ts_slp;
	int ts_th;
}				t_philo;

int	handling_error(int argc, char **argv);
int	ft_atoi(const char *str);
t_philo **init(char **argv, t_table *table);
int create(t_table *table, t_philo	**philos);
void mysleep(int time);

#endif