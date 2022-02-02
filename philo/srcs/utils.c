/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:52:30 by echerell          #+#    #+#             */
/*   Updated: 2022/02/03 00:04:54 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_numb(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	n;
	long	sign;

	sign = 1;
	n = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i++] - '0');
		if (n < 0 && sign == 1)
			return (-1);
		if (n < 0 && sign == -1)
			return (0);
	}
	return ((int)(n * sign));
}

unsigned long	get_time()
{
	struct timeval	tv;
	unsigned long	ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

unsigned long	get_ts(struct timeval tv)
{
	struct timeval	cur_tv;
	unsigned long	sub;

	gettimeofday(&cur_tv, NULL);
	sub = (cur_tv.tv_sec * 1000 + cur_tv.tv_usec / 1000) -
			(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (sub);
}
