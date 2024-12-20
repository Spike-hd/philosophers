/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:33:26 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/20 07:55:56 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_table	table;

	if (ac != 5 && ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av) == -1)
		return (error_handle("problem with one of the argument\n"));
	if (init_philo(&philo, &table) == -1)
		return (error_handle("problem with the allocation of philosophers\n"));

}
