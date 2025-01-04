/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:01:25 by spike             #+#    #+#             */
/*   Updated: 2024/12/20 08:44:29 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_everyone_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 0)
	{
		pthread_mutex_unlock(&philo->table->mtx_alive);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->mtx_alive);
	return (1);
}

int	eating_routine(t_philo *philo, int max_dish)
{
	if (is_everyone_alive(philo) == 0)
		return (-1);
	while (philo->dish_eaten < max_dish)
	{
		// Philosophe commence à réfléchir
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_think(philo);

		// Philosophe commence à manger
		if (is_everyone_alive(philo) == 0)
			return (-1);
		if (sticks_lock(philo) == -1)
			return (-1);
		print_eat(philo);
		ft_usleep(philo->table->time_to_eat);
		sticks_unlock(philo);
		init_waiting(philo);

		// Philosophe dort
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_sleep(philo);
		ft_usleep(philo->table->time_to_sleep);

		pthread_mutex_lock(&philo->mtx_dish);
		if (philo->table->stop == 1)
			philo->dish_eaten++;
		pthread_mutex_unlock(&philo->mtx_dish);
	}
	return (0);
}

void	*eating(void *args)
{
	t_philo	*philo;
	int		max_dish;

	philo = (t_philo *)args;
	if (philo->table->stop == 0)
		max_dish = philo->dish_eaten + 1;
	else
		max_dish = philo->table->max_meal;
	eating_routine(philo, max_dish);
	return (NULL);
}
