/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 22:41:13 by echerell          #+#    #+#             */
/*   Updated: 2022/02/03 00:32:21 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_dead(t_philo *philo)
{
	unsigned long	sub;

	if (*philo->dead)
		return (0);
	pthread_mutex_lock(&philo->lunch_time);
	sub = get_time() - philo->last_meal;
	if (sub >= philo->indata->ttd)
	{
		pthread_mutex_unlock(&philo->lunch_time);
		if (!(*philo->dead))
		{
			*philo->dead = 1;
			pthread_mutex_lock(philo->print);
			printf("%lu ms %u died\n", get_ts(philo->time), philo->id);
			pthread_mutex_unlock(philo->print);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->lunch_time);
	return (0);

}

void	*cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(200);
	while (!(*philo->dead))
	{
		if (!take_forks(philo))
			break;
	}
	pthread_mutex_destroy(&philo->lunch_time);
	return (NULL);
}
