/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:12:50 by spike             #+#    #+#             */
/*   Updated: 2025/01/06 21:13:58 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philo)
{
	unsigned long	time_now;
	unsigned long	last_meal;

	time_now = calculate_time();
	sem_wait(&philo->sem_dish);
	last_meal = philo->last_meal;
	sem_post(&philo->sem_dish);

	if (time_now - last_meal > (unsigned long)philo->table->time_to_die)
		sem_post(&philo->table->sem_alive);
}

int	is_philo_full(t_philo *philo) // PB JE NE PEUX SAVOIR QUE SI UN PHILO EST FULL
{
	if (philo->table->stop == 0)
		return (0);
	sem_wait(&philo->sem_dish);
	if (philo->dish_eaten < philo->table->max_meal)
	{
		sem_post(&philo->sem_dish);
		return (0);
	}
	sem_post(&philo->sem_dish);
	return (1);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		check_death(philo);
		if (is_philo_full(philo) == 1)
			break ;
		ft_usleep(5);
	}
	return (NULL);
}
