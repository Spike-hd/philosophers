/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:49:09 by spike             #+#    #+#             */
/*   Updated: 2025/01/07 10:04:09 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating_routine(t_philo *philo, int max_dish)
{
	while (philo->dish_eaten < max_dish)
	{
		// Philosophe commence à réfléchir
		print_think(philo);

		// Philosophe commence à manger
		sem_wait(&philo->table->sem_forks);
		sem_wait(&philo->table->sem_forks);
		print_fork(philo);
		init_waiting(philo);
		print_eat(philo);
		ft_usleep(philo->table->time_to_eat);
		sem_post(&philo->table->sem_forks);
		sem_post(&philo->table->sem_forks);
		init_waiting(philo);

		// Philosophe dort
		print_sleep(philo);
		ft_usleep(philo->table->time_to_sleep);

		sem_wait(&philo->sem_dish);
		if (philo->table->stop == 1)
			philo->dish_eaten++;
		sem_post(&philo->sem_dish);
	}
	return (0);
}

void	start_simulation(t_philo *philo, int i)
{
	int		max_dish;

	philo->name = i;

	// Création du thread de monitoring
	if (pthread_create(&philo->thread, NULL, monitoring, philo) != 0)
		return(handle_error("Failed to create monitoring thread"));

	// je le detache immediatement pour que le systeme gere lui meme son retrait
	if (pthread_detach(philo->thread) != 0)
		return(handle_error("Failed to detach monitoring thread"));

	if (philo->table->stop == 0)
		max_dish = philo->dish_eaten + 1;
	else
		max_dish = philo->table->max_meal;
	if (philo->name % 2 == 0)
		ft_usleep(5); // pour ne pas avoir de deadlock
	eating_routine(philo, max_dish);
	return (NULL);
}
