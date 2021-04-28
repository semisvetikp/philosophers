/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:33:05 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/29 00:29:05 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_one.h"

int	main(int argc, char **argv)
{

	if (handling_error(argc, argv))
		return (1);
	init(argv);
	if (argc == 5)
	{
		printf("OK\n");
		return (0);
	}
	else if (argc == 6)
	{
		printf("OK\n");
		return (0);
	}
}
