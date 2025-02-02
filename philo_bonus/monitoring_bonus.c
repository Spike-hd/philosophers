/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:12:50 by spike             #+#    #+#             */
/*   Updated: 2025/01/10 11:11:00 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philo)
{
	unsigned long	time_now;
	unsigned long	last_meal;
	unsigned long	start;

	time_now = calculate_time();
	sem_wait(philo->sem_wait);
	last_meal = philo->last_meal;
	sem_post(philo->sem_wait);
	if (time_now - last_meal > (unsigned long)philo->table->time_to_die)
	{
		start = philo->table->start;
		sem_wait(philo->sem_write);
		printf("%ld Philo %d died\n", time_now - start, philo->name);
		sem_post(philo->table->sem_done);
	}
}

int	is_philo_full(t_philo *philo)
{
	if (philo->table->stop == 0)
		return (0);
	sem_wait(philo->sem_dish);
	if (philo->dish_eaten < philo->table->max_meal)
	{
		sem_post(philo->sem_dish);
		return (0);
	}
	sem_post(philo->sem_dish);
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
