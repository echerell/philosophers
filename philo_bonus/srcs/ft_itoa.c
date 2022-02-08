/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:57:31 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 01:56:57 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

static	long	ft_make_tmp(int n)
{
	if (n < 0)
		return (-(long)n);
	return ((long)n);
}

static	int	ft_count_nbr(long tmp, size_t i)
{
	while (tmp >= 1)
	{
		i++;
		tmp /= 10;
	}
	return (i);
}

static	void	ft_make_str(char *str, long tmp, size_t i, int sign)
{
	while (i)
	{
		str[i--] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (sign == -1)
		str[i] = '-';
	else
		str[i] = tmp % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	long	tmp;
	size_t	i;

	i = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		i++;
	}
	tmp = ft_make_tmp(n);
	i = ft_count_nbr(tmp, i);
	if (n == 0)
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	tmp = ft_make_tmp(n);
	ft_make_str(str, tmp, i, sign);
	return (str);
}
