/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:29:15 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/15 00:56:08 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

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
	pid_t			*pids;
}				t_table;

typedef struct s_philo
{
	int				number;
	sem_t			*sem;
	pthread_t		t;
	pthread_t		tmonitor;
	struct timeval	tv;
	struct timeval	tvp;
	t_table			*phtable;
	int				tstarteat;
	int				cnteat;
	int				ate;
	sem_t			*semeat;
	char			*semeat_name;
	int				time_prnt;
	int				time1_slp;
	int				time2_slp;
	int				t_slp;
}				t_philo;

int		handling_error(int argc, char **argv);
int		ft_atoi(const char *str);
t_philo	**init_table(char **argv, t_table *table);
t_philo	**init_philosophers(char **argv, t_table *table, int number);
int		create(t_table *table, t_philo	**philos);
void	mysleep(int time, t_philo *ph);
void	print(t_table *table, t_philo *philo, int a);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		zero_param(char **argv);

#endif