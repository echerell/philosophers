/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:37:17 by echerell          #+#    #+#             */
/*   Updated: 2022/02/02 21:02:26 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(pthread_mutex_t **forks, unsigned int nb_philo)
{
	size_t	i;

	i = 0;
	*forks = (pthread_mutex_t *)malloc(nb_philo * sizeof(pthread_mutex_t));
	if (!(*forks))
		return (EXIT_FAILURE);
	while (i < nb_philo)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_args(t_indata *indata, int argc, char **argv)
{
	indata->nb_philo = ft_atoi(argv[1]);
	indata->ttd = ft_atoi(argv[2]);
	indata->tte = ft_atoi(argv[3]);
	indata->tts = ft_atoi(argv[4]);
	if (argc == 6)
		indata->nb_meals = ft_atoi(argv[5]);
	else
		indata->nb_meals = -1;
	if (!indata->nb_philo)
	{
		print_err(ZERO_PHILO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
