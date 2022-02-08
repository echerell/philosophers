/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:43:23 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 02:42:37 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_unlink(sem_t *print, sem_t *forks)
{
	sem_close(print);
	sem_unlink("print");
	sem_close(forks);
	sem_unlink("forks");
}

int	main(int argc, char **argv)
{
	t_indata	indata;
	sem_t		*forks;
	sem_t		*print;

	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (init_args(&indata, argc, argv))
		return (EXIT_FAILURE);
	if (!indata.nb_meals)
	{
		printf("Philosophers don't want to eat\n");
		return (EXIT_SUCCESS);
	}
	forks = init_forks(indata.nb_philo);
	if (forks == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("print");
	print = sem_open("print", O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (print == SEM_FAILED)
		return (EXIT_FAILURE);
	if (start_childs(&indata, forks, print))
		return (EXIT_FAILURE);
	close_unlink(print, forks);
	return (EXIT_SUCCESS);
}
