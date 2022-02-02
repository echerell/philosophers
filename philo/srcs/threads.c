/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 23:19:16 by echerell          #+#    #+#             */
/*   Updated: 2022/02/03 01:18:31 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	make_philos(t_philo *philos, pthread_mutex_t *forks,
						t_indata *indata, pthread_mutex_t *print)
{
	size_t	i;

	i = 0;
	while (i < indata->nb_philo)
	{
		philos[i].indata = indata;
		philos[i].id = i + 1;
		philos[i].print = print;
		philos[i].meal_count = 0;
		pthread_mutex_init(&philos[i].lunch_time, NULL);
		make_forks(&philos[i], i, forks, indata->nb_philo);
		i++;
	}
}

static int	check_philo(t_philo *philos, unsigned int nb_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (is_dead(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_threads(t_indata *indata, t_philo *philos,
							pthread_mutex_t *forks)
{
	unsigned int	i;

	while (!(*philos->dead))
	{
		check_philo(philos, indata->nb_philo);
	}
	i = 0;
	unlock_forks(forks, indata->nb_philo);
	while (i < indata->nb_philo)
	{
		if (pthread_join(philos[i].pt_id, NULL))
			return (EXIT_FAILURE);
		i++;
	}

	free(philos);
	return (EXIT_SUCCESS);
}

int	start_threads(t_indata *indata, pthread_mutex_t *forks,
					pthread_mutex_t *print)
{
	t_philo			*philos;
	size_t			i;
	struct timeval	ts;
	int				dead;

	i = 0;
	dead = 0;
	philos = (t_philo *)malloc(indata->nb_philo * sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	make_philos(philos, forks, indata, print);
	gettimeofday(&ts, NULL);
	while (i < indata->nb_philo)
	{
		philos[i].dead = &dead;
		philos[i].time = ts;
		philos[i].last_meal = get_time();
		if (pthread_create(&philos[i].pt_id, NULL, &cycle, &philos[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (check_threads(indata, philos, forks))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
