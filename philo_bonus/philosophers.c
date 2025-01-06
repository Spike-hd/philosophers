/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:25:53 by marvin            #+#    #+#             */
/*   Updated: 2025/01/05 16:25:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_simulation(t_philo *philo, int nb_philo)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = fork();
	while (i < nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			start_simulation(philo, i + 1);
			exit(0);
		}
		else
			philo->table->nb_pid[i] = pid;
		i++;
	}
	sem_wait(philo->table->sem_alive); // wait until one process dies
		// kill all child process
	}

}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_table			table;
	unsigned long	start;

	start = calculate_time();
	if (ac != 5 && ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av, start) == -1)
		return (error_handle("problem with one of the argument\n"));
	if (init_philo(philo, &table) == -1)
		return (error_handle("problem with the allocation of philosophers\n"));
	if (start_simulation(philo, table.nb_philo) == -1)
		return (error_handle("problem with the simulation\n"));
	clear_all(&philo);
	return (0);
}
