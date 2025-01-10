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
	printf("%ld Philo %d died\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_think(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 1)
		printf("%ld Philo %d is thinking\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_alive);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_fork(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 1)
	{
		printf("%ld Philo %d has taken a fork\n", time - start, philo->name);
		if (philo->table->nb_philo > 1)
			printf("%ld Philo %d has taken a fork\n", time - start,
				philo->name);
	}
	pthread_mutex_unlock(&philo->table->mtx_alive);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_eat(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 1)
		printf("%ld Philo %d is eating\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_alive);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}

void	print_sleep(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	pthread_mutex_lock(&philo->table->mtx_writing);
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 1)
		printf("%ld Philo %d is sleeping\n", time - start, philo->name);
	pthread_mutex_unlock(&philo->table->mtx_alive);
	pthread_mutex_unlock(&philo->table->mtx_writing);
}
