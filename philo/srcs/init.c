/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:37:17 by echerell          #+#    #+#             */
/*   Updated: 2022/01/29 23:47:21 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
