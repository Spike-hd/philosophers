/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:23:03 by marvin            #+#    #+#             */
/*   Updated: 2025/01/02 14:23:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	calculate_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (error_handle("Error with Gettimeofday fct\n"));
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	init_waiting(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_waiting);
	philo->waiting = calculate_time();
	pthread_mutex_unlock(&philo->mtx_waiting);
}

int	check_death(t_philo *philo)
{
	int	current_time;
	int	last_waiting;

	current_time = calculate_time();
	pthread_mutex_lock(&philo->mtx_waiting);
	last_waiting = philo->waiting;
	pthread_mutex_unlock(&philo->mtx_waiting);

	if (current_time - last_waiting > philo->table->time_to_die)
		return (1);
	return (0);
}
