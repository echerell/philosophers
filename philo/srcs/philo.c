/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:08:35 by echerell          #+#    #+#             */
/*   Updated: 2022/01/30 00:12:35 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_indata	indata;

	if (check_args(argc, argv))
		return (EXIT_FAILURE);
	if (init_args(&indata, argc, argv))
		return (EXIT_FAILURE);
	if (!indata.nb_meals)
	{
		printf("Philosophers don't want to eat\n");
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
