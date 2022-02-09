/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:15:40 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 15:23:32 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_philo *philo)
{
	unsigned long	sub;

	if (*philo->dead)
		return (1);
	sem_wait(philo->lunch_time);
	sub = get_time() - philo->last_meal;
	if (sub >= philo->indata->ttd)
	{
		sem_post(philo->lunch_time);
		if (!(*philo->dead))
		{
			*philo->dead = 1;
			sem_wait(philo->print);
			printf("%lu ms %u died\n", get_ts(philo->time), philo->id);
		}
		return (1);
	}
	sem_post(philo->lunch_time);
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (*philo->dead)
		return (0);
	sem_wait(philo->forks);
	if (*philo->dead)
		return (0);
	sem_wait(philo->print);
	printf("%lu ms %u has taken a fork\n", get_ts(philo->time), philo->id);
	sem_post(philo->print);
	sem_wait(philo->forks);
	if (*philo->dead)
		return (0);
	sem_wait(philo->print);
	printf("%lu ms %u has taken a fork\n", get_ts(philo->time), philo->id);
	sem_post(philo->print);
	return (1);
}

static int	eating(t_philo *philo)
{
	sem_wait(philo->lunch_time);
	philo->last_meal = get_time();
	sem_wait(philo->print);
	printf("%lu ms %u is eating\n", get_ts(philo->time), philo->id);
	sem_post(philo->print);
	sem_post(philo->lunch_time);
	usleep(philo->indata->tte * 1000);
	philo->meal_count++;
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (*philo->dead)
		return (0);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	if (*philo->dead)
		return (0);
	sem_wait(philo->print);
	printf("%lu ms %u is sleeping\n", get_ts(philo->time), philo->id);
	sem_post(philo->print);
	usleep(philo->indata->tts * 1000);
	if (*philo->dead)
		return (0);
	sem_wait(philo->print);
	printf("%lu ms %u is thinking\n", get_ts(philo->time), philo->id);
	sem_post(philo->print);
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
	return (NULL);
}
