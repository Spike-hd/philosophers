/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:40:15 by spike             #+#    #+#             */
/*   Updated: 2024/12/20 07:56:30 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_waiting(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_waiting);
	philo->waiting = calculate_time();
	pthread_mutex_unlock(&philo->mtx_waiting);
}

int	setup_table_params(t_table *table, int ac, char **av, unsigned long start)
{
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->alive = 1;
	table->start = start;
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
	int	i;

	table->chopsticks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->chopsticks)
		return (-1);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->chopsticks[i], NULL) != 0)
			return (clear_all(NULL));
		i++;
	}
	if (pthread_mutex_init(&table->mtx_alive, NULL) != 0)
		return (clear_all(NULL));
	if (pthread_mutex_init(&table->mtx_writing, NULL) != 0)
		return (clear_all(NULL));
	return (0);
}

int	init_table(t_table *table, int ac, char **av, unsigned long start)
{
	if (setup_table_params(table, ac, av, start) != 0)
		return (-1);
	if (init_table_resources(table) != 0)
		return (-1);
	return (0);
}

int	init_philo(t_philo **philo, t_table *table)
{
	int	i;

	*philo = (t_philo *)malloc(table->nb_philo * sizeof(t_philo));
	if (!*philo)
		return (-1);
	i = 0;
	while (i < table->nb_philo)
	{
		(*philo)[i].name = i + 1;
		(*philo)[i].dish_eaten = 0;
		(*philo)[i].table = table;
		if (pthread_mutex_init(&(*philo)[i].mtx_waiting, NULL) != 0)
			return (clear_all(philo));
		if (pthread_mutex_init(&(*philo)[i].mtx_dish, NULL) != 0)
			return (clear_all(philo));
		init_waiting(&(*philo)[i]);
		i++;
	}
	return (0);
}
