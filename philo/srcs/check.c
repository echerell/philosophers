/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:16:25 by echerell          #+#    #+#             */
/*   Updated: 2022/01/29 23:51:26 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_err(int err_num)
{
	if (err_num == NB_ERR)
	{
		printf("Worng argument format:\n");
		printf("./philo nop ttd tte tts [notepme]\n");
		printf("nop - number of philosophers\n");
		printf("ttd - time_to_die\n");
		printf("tte - time to eat\n");
		printf("tts - time_to_sleep\n");
		printf("notepme(opt.) - number of times each philosophers must eat\n");
	}
	else if (err_num == DIG_ERR)
		printf("Please, use only digits in arguments\n");
	else if (err_num == ZERO_PHILO)
		printf("We don't have any philosophers\n");
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		print_err(NB_ERR);
		return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		if (check_numb(argv[i]))
		{
			print_err(DIG_ERR);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
