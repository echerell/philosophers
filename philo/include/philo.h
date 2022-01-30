/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 22:07:59 by echerell          #+#    #+#             */
/*   Updated: 2022/01/31 00:00:47 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum arg_errs
{
	NB_ERR = -10,
	DIG_ERR,
	ZERO_PHILO
};

typedef struct s_indata
{
	unsigned int	nb_philo;
	unsigned long	ttd;
	unsigned long	tte;
	unsigned long	tts;
	long			nb_meals;
}t_indata;

typedef struct s_philo
{
	t_indata		*indata;
	pthread_t		pt_id;
	unsigned int	id;
	pthread_mutex_t	*forkl;
	pthread_mutex_t	*forkr;
	pthread_mutex_t	*print;
	pthread_mutex_t	lunch_time;
	int				*dead;
	struct timeval	time;
}t_philo;

int		check_args(int argc, char **argv);
void	print_err(int err_num);

int		check_numb(char *str);
int		ft_atoi(const char *nptr);

int		init_args(t_indata *indata, int argc, char **argv);
int		init_forks(pthread_mutex_t **forks, unsigned int nb_philo);

void	make_forks(t_philo *philo, size_t index, pthread_mutex_t *forks,
					unsigned int nb_philo);
void	destroy_forks(pthread_mutex_t *forks, unsigned int nb_philo);

int	start_threads(t_indata *indata, pthread_mutex_t *forks,
					pthread_mutex_t *print);

#endif
