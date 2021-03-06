/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:08:35 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 00:19:29 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_indata		indata;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (init_args(&indata, argc, argv))
		return (EXIT_FAILURE);
	if (!indata.nb_meals)
	{
		printf("Philosophers don't want to eat\n");
		return (EXIT_SUCCESS);
	}
	forks = NULL;
	if (init_forks(&forks, indata.nb_philo))
		return (EXIT_FAILURE);
	pthread_mutex_init(&print, NULL);
	if (start_threads(&indata, forks, &print))
		return (EXIT_FAILURE);
	destroy_forks(forks, indata.nb_philo);
	pthread_mutex_destroy(&print);
	return (EXIT_SUCCESS);
}
