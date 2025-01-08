/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:29:16 by marvin            #+#    #+#             */
/*   Updated: 2025/01/05 16:29:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_waiting(t_philo *philo)
{
	sem_wait(philo->sem_wait);
	philo->last_meal = calculate_time();
	sem_post(philo->sem_wait);
}

int	setup_table_params(t_table *table, int ac, char **av)
{
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
	{
		table->stop = 0;
		table->max_meal = 0;
	}
	else
	{
		table->stop = 1;
		table->max_meal = ft_atoi(av[5]);
	}
	if (is_init_correct(table) == 0)
		return (-1);
	return (0);
}

int	init_table_resources(t_table *table)
{
	table->nb_pid = (int *)malloc(table->nb_philo * sizeof(int));
	if (table->nb_pid == NULL)
		return (-1);
	table->sem_forks = sem_open("/forks", O_CREAT, 0644, table->nb_philo);
	table->sem_done = sem_open("/done", O_CREAT, 0644, 0);
	if (table->sem_done == SEM_FAILED || table->sem_forks == SEM_FAILED)
	{
		printf("semaphore pb\n");
		close_table_sem(table);
		return (-1);
	}
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	if (setup_table_params(table, ac, av) != 0)
		return (-1);
	if (init_table_resources(table) != 0)
		return (-1);
	return (0);
}

int	init_philo(t_philo *philo, t_table *table)
{
	pthread_t	thread;

	philo->thread = &thread;
	philo->name = 0;
	philo->dish_eaten = 0;
	philo->table = table;
	philo->sem_wait = sem_open("/wait", O_CREAT, 0644, 1);
	philo->sem_dish = sem_open("/dish", O_CREAT, 0644, 1);
	philo->sem_write = sem_open("/write", O_CREAT, 0644, 1);
	if (philo->sem_wait == SEM_FAILED
		|| philo->sem_dish == SEM_FAILED
		|| philo->sem_write == SEM_FAILED)
	{
		close_philo_sem(philo);
		return (-1);
	}
	table->start = calculate_time();
	init_waiting(philo);
	return (0);
}
