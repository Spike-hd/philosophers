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

int	init_table(t_table *table, int ac, char **av)
{
	unsigned int	i;

	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 5)
		table->stop = 0;
	else
	{
		table->stop = 1;
		table->max_meal = ft_atoi(av[5]);
	}
	if (is_init_correct(table) == 0)
		return (-1);
	table->chopsticks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->chopsticks)
		return (-1);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->chopsticks[i], NULL) != 0)
			return (clear_mutex(table)); // => free et destroy les mutexs déja créés (attention double free) (possible d'utiliser la meme fonction pour tout ?)
	}
	return (0);
}


int	init_philo(t_philo **philo, t_table *table)
{
	unsigned int	i;

	*philo = (t_philo *)malloc(table->nb_philo * sizeof(t_philo));
	if (!*philo)
		return (-1); // attention a tout free en cas de pb
	i = 0;
	while (i < table->nb_philo)
	{
		(*philo)[i].name = i + 1;
		(*philo)[i].waiting = 0;
		(*philo)[i].full = 0;
		(*philo)[i].dish_eaten = 0;
		(*philo)[i].table = table;
		i++;
	}
	return (0);
}
