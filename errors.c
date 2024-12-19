/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:25:14 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/19 12:09:59 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_handle(char *error_msg)
{
	printf("%s", error_msg);
}

int	is_init_correct(t_table *table)
{
	if (table->nb_philo == -1)
		return (0);
	if (table->time_to_die == -1)
		return (0);
	if (table->time_to_eat == -1)
		return (0);
	if (table->time_to_sleep == -1)
		return (0);
	if (table->stop = 1)
	{
		if (table->max_meal == -1)
			return (0);
	}
	return (1);
}
