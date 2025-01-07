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
	int		trigger;

	i = 0;
	trigger = 0;
	pid = fork();
	while (i < nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			start_simulation(philo, i + 1);
			trigger++; // si le philo sort de la simulation cest qu'il a fini de manger il active donc un trigger avant d'exit
			if (trigger == nb_philo)
				sem_post(philo->table->sem_done);
			exit(0);
		}
		else
			philo->table->nb_pid[i] = pid;
		i++;
	}
	sem_wait(philo->table->sem_done);
	i = -1;
	while (++i < nb_philo)
		kill(philo->table->nb_pid[i], SIGKILL);

	close_all(philo);
    return 0;
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
