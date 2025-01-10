/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:49:09 by spike             #+#    #+#             */
/*   Updated: 2025/01/10 11:12:08 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating_routine(t_philo *philo, int max_dish)
{
	while (philo->dish_eaten < max_dish)
	{
		print_think(philo);
		sem_wait(philo->table->sem_forks);
		print_fork(philo);
		sem_wait(philo->table->sem_forks);
		print_fork(philo);
		print_eat(philo);
		ft_usleep(philo->table->time_to_eat);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
		init_waiting(philo);
		print_sleep(philo);
		ft_usleep(philo->table->time_to_sleep);
		sem_wait(philo->sem_dish);
		if (philo->table->stop == 1)
			philo->dish_eaten++;
		sem_post(philo->sem_dish);
	}
	return (0);
}

int	start_simulation(t_philo *philo, int i)
{
	int		max_dish;

	philo->name = i;
	if (pthread_create(philo->thread, NULL, monitoring, philo) != 0)
		return (error_handle("Failed to create monitoring thread"));
	if (pthread_detach(*philo->thread) != 0)
		return (error_handle("Failed to detach monitoring thread"));
	if (philo->table->stop == 0)
		max_dish = philo->dish_eaten + 1;
	else
		max_dish = philo->table->max_meal;
	if (philo->name % 2 == 0)
		ft_usleep(philo->table->time_to_eat);
	eating_routine(philo, max_dish);
	return (0);
}
