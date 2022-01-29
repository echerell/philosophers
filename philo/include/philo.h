/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:07:59 by echerell          #+#    #+#             */
/*   Updated: 2022/01/29 23:46:51 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>

enum arg_errs
{
	NB_ERR = -10,
	DIG_ERR,
	ZERO_PHILO
};

typedef struct s_indata
{
	unsigned int	nb_philo;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	nb_meals;
}t_indata;

int		check_args(int argc, char **argv);
void	print_err(int err_num);

int		check_numb(char *str);
int		ft_atoi(const char *nptr);

int		init_args(t_indata *indata, int argc, char **argv);

#endif
