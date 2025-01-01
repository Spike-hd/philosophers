/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:01:25 by spike             #+#    #+#             */
/*   Updated: 2024/12/20 08:44:29 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sticks_lock(t_philo *philo)
{
	int left = philo->name - 1;
	int right = (philo->name % philo->table->nb_philo);

	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->chopsticks[left]);
		pthread_mutex_lock(&philo->table->chopsticks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->chopsticks[right]);
		pthread_mutex_lock(&philo->table->chopsticks[left]);
	}
}

void	sticks_unlock(t_philo *philo)
{
	int left = philo->name - 1;
	int right = (philo->name % philo->table->nb_philo);

	pthread_mutex_unlock(&philo->table->chopsticks[right]);
	pthread_mutex_unlock(&philo->table->chopsticks[left]);
}
