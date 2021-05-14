/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:18:23 by jradioac          #+#    #+#             */
/*   Updated: 2021/05/13 21:23:20 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_intl(int n)
{
	int	k;

	k = 0;
	if (n <= 0)
	{
		n = -n;
		k++;
	}
	while (n)
	{
		k++;
		n = n / 10;
	}
	return (k);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		l;
	int		m;

	m = n;
	l = ft_intl(n);
	s = (char *)malloc(sizeof(char) * (l + 1));
	if (s == NULL)
		return (NULL);
	if (n < 0)
		m = -m;
	while (l)
	{
		l--;
		s[l] = m % 10 + '0';
		m = m / 10;
	}
	if (n < 0)
		s[0] = '-';
	s[ft_intl(n)] = '\0';
	return (s);
}

int	ft_atoi(const char *str)
{
	int	flag;
	int	res;

	flag = 1;
	res = 0;
	while ((*str == ' ') || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -flag;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * flag);
}
