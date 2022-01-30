/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 23:19:16 by echerell          #+#    #+#             */
/*   Updated: 2022/01/31 00:02:08 by echerell         ###   ########.fr       */
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
		pthread_mutex_init(&philos[i].lunch_time, NULL);
		make_forks(&philos[i], i, forks, indata->nb_philo);
		i++;
	}
}

int	start_threads(t_indata *indata, pthread_mutex_t *forks,
					pthread_mutex_t *print)
{
	t_philo			*philos;
	size_t			i;
	struct timeval	tv;
	int				dead;

	i = 0;
	dead = 0;
	philos = (t_philo *)malloc(indata->nb_philo * sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	make_philos(philos, forks, indata, print);
	gettimeofday(&tv, NULL);
	while (i < indata->nb_philo)
	{
		philos[i].dead = &dead;
		philos[i].time = tv;
		//if (pthread_create(&philos[i].pt_id, NULL, &cycle, &philos[i]))
		//	return (EXIT_FAILURE);
		i++;
	}
	//if (check_threads(...))
	//	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
