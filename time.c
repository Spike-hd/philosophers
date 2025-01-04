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

unsigned long	calculate_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (error_handle("Error with Gettimeofday fct\n"));
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}
void	ft_usleep(unsigned long time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = calculate_time();
	while ((calculate_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	init_waiting(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_waiting);
	philo->waiting = calculate_time();
	pthread_mutex_unlock(&philo->mtx_waiting);
}

int	check_death(t_philo *philo)
{
	unsigned long	time_now;
	unsigned long	time_last_meal;

	time_now = calculate_time();
	pthread_mutex_lock(&philo->mtx_waiting);
	time_last_meal = philo->waiting;
	pthread_mutex_unlock(&philo->mtx_waiting);
	if ((time_now - time_last_meal > (unsigned long)philo->table->time_to_die) || philo->table->alive == 0)
		return (1);
	return (0);
}

int	test_waiting(t_philo *philo)
{
	unsigned long	time_now;
	unsigned long	time_last_meal;

	time_now = calculate_time();
	pthread_mutex_lock(&philo->mtx_waiting);
	time_last_meal = philo->waiting;
	pthread_mutex_unlock(&philo->mtx_waiting);
	int result = time_now - time_last_meal;
	return (result);
}
