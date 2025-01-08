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

	i = -1;
	while (++i < nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			start_simulation(philo, i + 1);
			ft_usleep(philo->table->time_to_eat);
			sem_wait(philo->sem_write);
			printf("All the philosophers had a happy dinner !\n");
			sem_post(philo->table->sem_done);
		}
		else
			philo->table->nb_pid[i] = pid;
	}
	sem_wait(philo->table->sem_done);
	i = -1;
	while (++i < nb_philo)
		kill(philo->table->nb_pid[i], SIGKILL);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			philo;
	t_table			table;

	if (ac != 5 && ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av) == -1)
		return (error_handle("problem with one of the argument\n"));
	if (init_philo(&philo, &table) == -1)
		return (error_handle("problem with the allocation of philosophers\n"));
	if (set_simulation(&philo, table.nb_philo) == -1)
		return (error_handle("problem with the simulation\n"));
	clear_all(&philo);
	return (0);
}
