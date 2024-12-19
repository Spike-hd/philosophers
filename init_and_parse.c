/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:40:15 by spike             #+#    #+#             */
/*   Updated: 2024/12/19 20:48:11 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int philo_and_sticks(t_table *table)
{
	int	i;

	table->chopsticks = (int *)malloc(table->nb_philo * sizeof(int));
	if (!table->chopsticks)
		return (-1);
	table->philo = (t_philo *)malloc(table->nb_philo * sizeof(t_philo));
	if (!table->philo)
		return (-1);
	i = 0;
	while (i < table->nb_philo)
	{
		table->chopsticks[i] = i + 1;
		table->philo[i].name = i + 1;
		i++;
	}

}

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
	return (0);
}
