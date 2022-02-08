/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:16:13 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 01:33:01 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	size_t	i;
	size_t	n2;

	i = 0;
	n2 = 0;
	if (!s1 || !s2)
		return (NULL);
	cat = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!cat)
		return (NULL);
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[n2])
	{
		cat[i] = s2[n2];
		i++;
		n2++;
	}
	cat[i] = '\0';
	return (cat);
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

void	remove_block(sem_t *parent_block, unsigned int nb_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_philo)
	{
		sem_post(parent_block);
		i++;
	}
}
