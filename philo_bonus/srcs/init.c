/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:54:07 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 02:34:07 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

sem_t	*init_forks(unsigned int nb_philo)
{
	sem_t	*forks;

	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, S_IRWXU | S_IRWXG, nb_philo);
	return (forks);
}
