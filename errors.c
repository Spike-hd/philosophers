/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:25:14 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/19 18:32:24 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_handle(char *error_msg) // <= il faut penser a tout free
{
	printf("%s", error_msg);
}

int	is_init_correct(t_table *table)
{
	if (table->nb_philo == -1 || table->nb_philo == 0)
		return (0);
	if (table->time_to_die == -1 || table->time_to_die == 0)
		return (0);
	if (table->time_to_eat == -1 || table->time_to_eat == 0)
		return (0);
	if (table->time_to_sleep == -1 || table->time_to_sleep == 0)
		return (0);
	if (table->stop == 1)
	{
		if (table->max_meal == -1 || table->max_meal == 0)
			return (0);
	}
	return (1);
}
