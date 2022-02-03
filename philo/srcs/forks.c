/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:52:25 by echerell          #+#    #+#             */
/*   Updated: 2022/02/04 00:34:53 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forkl);
	if (*philo->dead)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lu ms %u has taken a fork\n", get_ts(philo->time), philo->id);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->forkr);
	if (*philo->dead)
		return (0);
	pthread_mutex_lock(philo->print);
	printf("%lu ms %u has taken a fork\n", get_ts(philo->time), philo->id);
	pthread_mutex_unlock(philo->print);
	return (1);
}

void	make_forks(t_philo *philo, size_t index, pthread_mutex_t *forks,
					unsigned int nb_philo)
{
	if (nb_philo == 1)
	{
		philo->forkl = &forks[0];
		philo->forkr = &forks[0];
	}
	else if (!index)
	{
		philo->forkl = &forks[nb_philo - 1];
		philo->forkr = &forks[0];
	}
	else
	{
		philo->forkl = &forks[index - 1];
		philo->forkr = &forks[index];
	}
}

void	destroy_forks(pthread_mutex_t *forks, unsigned int nb_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_unlock(&forks[i]);
		i++;
	}
}
