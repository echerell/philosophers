/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:24:12 by echerell          #+#    #+#             */
/*   Updated: 2022/02/09 02:21:13 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	make_philos(t_philo *philos, sem_t *forks, t_indata *indata,
						sem_t *print)
{
	unsigned int	i;
	char			*nb;

	i = 0;
	while (i < indata->nb_philo)
	{
		philos[i].indata = indata;
		philos[i].id = i + 1;
		philos[i].forks = forks;
		philos[i].print = print;
		philos[i].meal_count = 0;
		nb = ft_itoa(i);
		philos[i].lunch_name = ft_strjoin("lunch_", nb);
		free(nb);
		sem_unlink(philos[i].lunch_name);
		philos[i].lunch_time = sem_open(philos[i].lunch_name, O_CREAT,
							S_IRWXU | S_IRWXG, 1);
		i++;
	}
}

static void	child_exe(t_philo *philo)
{
	pthread_t	thread;
	int			dead;

	dead = 0;
	philo->dead = &dead;
	sem_wait(philo->parent_block);
	philo->last_meal = get_time();
	if (pthread_create(&thread, NULL, &cycle, philo)
			|| pthread_detach(thread))
		exit(PTH_ERR);
	while (1)
	{
		if (is_dead(philo))
			exit(DEAD);
		else if (philo->indata->nb_meals > 0
				&& philo->meal_count >= philo->indata->nb_meals)
			exit(FULL);
	}
}

static void	remove_childs(t_philo *philos, unsigned int	nb_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_philo)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		sem_close(philos[i].lunch_time);
		sem_unlink(philos[i].lunch_name);
		free(philos[i].lunch_name);
		i++;
	}
}

static int	check_childs(t_indata *indata, t_philo *philos)
{
	unsigned int	mark;
	int				status;

	mark = 0;
	while (indata->nb_meals > 0 && mark != indata->nb_philo)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) != FULL)
			break;
		mark++;
	}
	if (indata->nb_meals < 0)
		waitpid(0, &status, 0);
	remove_childs(philos, indata->nb_philo);
	if (indata->nb_meals > 0 && mark == indata->nb_philo)
		printf("All philosophers have eaten necessary number of meals\n");
	sem_close(philos->parent_block);
	sem_unlink("parent_block");
	sem_post(philos->print);
	free(philos);
	return (EXIT_SUCCESS);
}

int	start_childs(t_indata *indata, sem_t *forks, sem_t *print)
{
	t_philo			*philos;
	unsigned int	i;
	struct timeval	ts;
	sem_t			*parent_block;

	i = 0;
	philos = (t_philo *)malloc(indata->nb_philo * sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	sem_unlink("parent_block");
	parent_block = sem_open("parent_block", O_CREAT, S_IRWXU | S_IRWXG, 0);
	if (parent_block == SEM_FAILED)
		return (EXIT_FAILURE);
	make_philos(philos, forks, indata, print);
	gettimeofday(&ts, NULL);
	while (i < indata->nb_philo)
	{
		philos[i].time = ts;
		philos[i].parent_block = parent_block;
		philos[i].pid = fork();
		if (!philos[i].pid)
			child_exe(&philos[i]);
		else if (philos[i].pid < 0)
			return (EXIT_FAILURE);
		i++;
	}
	remove_block(parent_block, indata->nb_philo);
	return (check_childs(indata, philos));
}
