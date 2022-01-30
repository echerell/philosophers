/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:52:25 by echerell          #+#    #+#             */
/*   Updated: 2022/01/30 23:58:44 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
