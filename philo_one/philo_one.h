/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:58:55 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 00:22:04 by jradioac         ###   ########.fr       */
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
	pthread_mutex_t	print;
	int				forks;
	int				tdie;
	int				teat;
	int				tsleep;
	int				tstart;
	struct timeval	ttv;
	int				timed;
	int				timesub;
	int				cnt_ate_philo;
	int				flag;
}				t_table;

typedef struct s_philo
{
	int				number;
	pthread_t		t;
	struct timeval	tv;
	struct timeval	tvp;
	pthread_mutex_t	eat;
	t_table			*phtable;
	int				tstarteat;
	int				cnteat;
	int				ate;
	int				time_prnt;
	int				time1_slp;
	int				time2_slp;
	int				t_slp;
}				t_philo;

int		handling_error(int argc, char **argv);
int		ft_atoi(const char *str);
t_philo	**init_table(char **argv, t_table *table);
t_philo	**init_philosophers(char **argv, t_table *table);
int		create(t_table *table, t_philo	**philos);
void	mysleep(int time, t_philo *ph);
void	print(t_table *table, t_philo *philo, int a);
int		zero_param(char **argv);

#endif