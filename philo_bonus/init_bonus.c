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
	pthread_mutex_lock(&philo->mtx_waiting);
	philo->waiting = calculate_time();
	pthread_mutex_unlock(&philo->mtx_waiting);
}

int	init_table(t_table *table, int ac, char **av, unsigned long start)
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
