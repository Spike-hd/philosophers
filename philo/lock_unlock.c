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

int	sticks_lock(t_philo *philo)
{
	int		left;
	int		right;

	left = philo->name - 1;
	right = (philo->name % philo->table->nb_philo);
	if (philo->table->nb_philo == 1)
	{
		print_fork(philo);
		return (-1);
	}
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->chopsticks[left]);
		pthread_mutex_lock(&philo->table->chopsticks[right]);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->table->chopsticks[right]);
		pthread_mutex_lock(&philo->table->chopsticks[left]);
		print_fork(philo);
	}
	return (0);
}

void	sticks_unlock(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->name - 1;
	right = (philo->name % philo->table->nb_philo);
	pthread_mutex_unlock(&philo->table->chopsticks[right]);
	pthread_mutex_unlock(&philo->table->chopsticks[left]);
}
