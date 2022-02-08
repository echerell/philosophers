/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:43:05 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 01:57:08 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

enum arg_errs
{
	NB_ERR = -10,
	DIG_ERR,
	ZERO_PHILO
};

enum exit_status
{
	FULL = 0,
	DEAD,
	PTH_ERR
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
	unsigned int	id;
	int				pid;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*lunch_time;
	char			*lunch_name;
	sem_t			*parent_block;
	int				*dead;
	struct timeval	time;
	long			meal_count;
	unsigned long	last_meal;
}t_philo;

int		check_args(int argc, char **argv);
void	print_err(int err_num);

int		init_args(t_indata *indata, int argc, char **argv);
sem_t	*init_forks(unsigned int nb_philo);

int		ft_atoi(const char *nptr);
unsigned long	get_time();
unsigned long	get_ts(struct timeval tv);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	remove_block(sem_t *parent_block, unsigned int nb_philo);
size_t	ft_strlen(const char *s);

int	start_childs(t_indata *indata, sem_t *forks, sem_t *print);

void	*cycle(void *arg);
int		is_dead(t_philo *philo);

#endif
