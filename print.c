/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:27:28 by marvin            #+#    #+#             */
/*   Updated: 2025/01/02 16:27:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_death(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	printf("%ld %d died\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_think(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	printf("%ld %d is thinking\n", time - start, philo->name);;
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_fork(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	printf("%ld %d has taken a fork\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_eat(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	printf("%ld %d is eating\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_sleep(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	printf("%ld %d is sleeping\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}
