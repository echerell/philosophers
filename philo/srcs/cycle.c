/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 22:41:13 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 02:31:18 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	unsigned long	sub;

	if (*philo->dead)
		return (1);
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

static int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lunch_time);
	philo->last_meal = get_time();
	pthread_mutex_lock(philo->print);
	printf("%lu ms %u is eating\n", get_ts(philo->time), philo->id);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(&philo->lunch_time);
	usleep(philo->indata->tte * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(philo->forkl);
	pthread_mutex_unlock(philo->forkr);
	if (*philo->dead)
		return (0);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	if (*philo->dead)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lu ms %u is sleeping\n", get_ts(philo->time), philo->id);
	pthread_mutex_unlock(philo->print);
	usleep(philo->indata->tts * 1000);
	if (*philo->dead)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lu ms %u is thinking\n", get_ts(philo->time), philo->id);
	pthread_mutex_unlock(philo->print);
	return (1);
}

void	*cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(2000);
	while (!(*philo->dead))
	{
		if (!take_forks(philo))
			break ;
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
	}
	pthread_mutex_destroy(&philo->lunch_time);
	return (NULL);
}
