/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:33:26 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/19 12:22:04 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_table(t_table *table, int ac, char **av)
{
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

int	main(int ac, char **av)
{
	t_table table;
	if (ac != 5 || ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av) == -1)
		return (error_handle("problem with one of the argument\n"));
}
